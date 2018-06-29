#include "StdAfx.h"
#include "CFont966.h"

CFont966::CFont966(CCamera966* pCamera, HWND hWnd)
{
	this->pCamera = pCamera;
	this->hWnd = hWnd;
	minCor = -1.0f;
	maxCor = 1.0f;
	Create3DFont();
}

CFont966::~CFont966()
{
	DeleteObject(hFont3DChn);
	DeleteObject(hFont3DEng);
	int n = caFont3D.GetSize();
	for(int i = 0; i < n; i++)
	{
		glDeleteLists(caFont3D[i].listStart, caFont3D[i].listLen);
	}
	caFont3D.RemoveAll();
	n = caFont2D.GetSize();
	for(int i = 0; i < n; i++)
	{
		DeleteObject(caFont2D[i].font);
	}
	caFont2D.RemoveAll();
}

/**
 * \brief 设置平行投影边界
 * \param minVar 相对最小值
 * \param maxVar 相对最大值
 */
void CFont966::SetOrthoRange(float minVar, float maxVar)
{
	minCor = minVar;
	maxCor = minVar;
}

/**
 * \brief 保存当前平行投影边界
 */
void CFont966::PushOrthoRange()
{
	caRangeCor.Add(minCor);
	caRangeCor.Add(maxCor);
}

/**
 * \brief 取出平行投影边界
 */
void CFont966::PopOrthoRange()
{
	int n = caRangeCor.GetSize();
	if(n > 1)
	{
		minCor = caRangeCor[n - 2];
		maxCor = caRangeCor[n - 1];
		caRangeCor.RemoveAt(n - 2, 2);
	}
}

/**
 * \brief 全2D字体
 * \param lpszText 字符串内容
 * \param pos 起始显示位置，三位坐标
 * \param size 大小
 * \param color 颜色，最好灰度
 * \param format 对齐方式，默认LEFT | BOTTOM
 * \param type 类型，0为投影空间，1为世界空间，2为模型空间
 */
void CFont966::Font2D(CString lpszText, CVector966 pos, int size, int color, int format, int type)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	float w = 0;
	CVector966 ans = pos;
	if (type == 0)
	{
		pos[2] = -100;//
	}
	else
	{
		CMatrix966 tmpProj;
		
		glGetFloatv(GL_PROJECTION_MATRIX, tmpProj);
		if (type == 1)
		{
			CMatrix966 tmpView = pCamera->cmEyeMat;
			CMatrix966 tmp = tmpProj * tmpView;
			
			ans = tmp.MulPosition(pos, w);
		}
		else
		{
			CMatrix966 tmpMV;
			glGetFloatv(GL_MODELVIEW_MATRIX, tmpMV);
			CMatrix966 tmp = tmpProj * tmpMV;
			ans = tmp.MulPosition(pos, w);
		}
		if (fabs(w) > 1e-6)
		{
			for (int i = 0; i < 3; i++)
			{
				ans[i] /= w;
			}
		}
	}
	if (w < 0 && type != 0)
	{
		return;
	}
	int tag = 0;
	while ((tag = lpszText.Find("\n", 0)) >= 0)
	{
		double height = Create2DFont(lpszText.Left(tag).GetBuffer(0), ans[0], ans[1], ans[2], size, color, format);
		lpszText = lpszText.Right(lpszText.GetLength() - tag - 1);
		pos[1] -= 1.5 * height;
	}
	Create2DFont(lpszText.GetBuffer(0), ans[0], ans[1], ans[2], size, color, format);

	glPopAttrib();
}

/**
 * \brief 光栅位图2D字体（只支持单行显示）
 * \param str 字符串内容
 * \param x 列位置（-1~1）
 * \param y 行位置（-1~1）
 * \param type 字体类型，1为8号点阵，2为9号点阵，3为10号Times Roman，4为24号Times Roman，5为10号Helvetica，6为12号Helvetica，7为18号Helvetica
 * \param color 颜色，最好灰度
 */
void CFont966::Font2DBmp(CString str, double x, double y, int type, int color)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(minCor, maxCor, minCor, maxCor, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
	glRasterPos2f(x, y);
	for(int i = 0; i < str.GetLength(); i++)
	{
		switch (type)
		{
		case 1:
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str.GetAt(i));
			break;
		case 2:
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str.GetAt(i));
			break;
		case 3:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, str.GetAt(i));
			break;
		case 4:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str.GetAt(i));
			break;
		case 5:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str.GetAt(i));
			break;
		case 6:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str.GetAt(i));
			break;
		case 7:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str.GetAt(i));
			break;
		default:break;
		}
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}

/**
 * \brief 快速英文字体，只能在中心设置字体（左底对齐）
 * \param str 输出字串
 */
void CFont966::Font3DEnglish(CString str)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	int front;
	glGetIntegerv(GL_FRONT_FACE, &front);
	glPushMatrix();
	glListBase(iFont3DListbase);
	glCallLists(str.GetLength(), GL_UNSIGNED_BYTE, static_cast<LPCTSTR>(str) ) ;	
	glPopMatrix();
	glFrontFace(front);

	glPopAttrib();
}

/**
 * \brief 英文字体
 * \param str 输出字串
 * \param pos 位置
 * \param size 大小
 * \param format 对齐格式
 * \param normal 朝向，未指定就是+z
 */
void CFont966::Font3DEnglish(CString str, CVector966 pos, double size, int format, CVector966* normal)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	int front;
	glGetIntegerv(GL_FRONT_FACE, &front);
	float len = 0;
	if(format & DT_CENTER || format & DT_RIGHT)		//需要知道写入的字符串有多宽。
	{
		glPushMatrix();
		glLoadIdentity();
		glListBase(iFont3DListbase) ;
		glCallLists(str.GetLength(), GL_UNSIGNED_BYTE, static_cast<LPCTSTR>(str) ) ;	//先写一遍。写到眼前看不到。
		CMatrix966 mat;
		glGetFloatv(GL_MODELVIEW_MATRIX, mat);
		glPopMatrix();
		len = mat[12];
	}
	double fs = size;
	double my = 0.640625;
	double mx = len;

	glPushMatrix();
	glTranslated(pos.x, pos.y, pos.z);
	glScaled(fs, fs, fs);
	if(normal)
	{
		CVector966 dir = *normal;
		CEuler966 hpr;
		hpr = dir.ToEuler();
		glRotated(hpr.h, 0, 1, 0);
		glRotated(hpr.p, 1, 0, 0);
	}
	if(format & DT_BOTTOM)//垂直底部对齐
	{
		glTranslated(0, 0, 0);
	}	
	else if(format & DT_VCENTER)//垂直中心对齐
	{
		glTranslated(0, -my / 2, 0);
	}	
	else if (format & DT_TOP)//垂直顶部对齐
	{
		glTranslated(0, -my, 0);
	}
	if(format & DT_CENTER)//水平中心对齐
	{
		glTranslated(-mx / 2, 0, 0);
	}
	else if(format & DT_RIGHT)//水平右对齐
	{
		glTranslated(-mx, 0, 0);
	}
	else if (format & DT_LEFT)
	{
		glTranslated(0, 0, 0);
	}
	glListBase(iFont3DListbase) ;
	glCallLists(str.GetLength(), GL_UNSIGNED_BYTE, static_cast<LPCTSTR>(str) ) ;	
	glPopMatrix();
	glFrontFace(front);
	
	glPopAttrib();
}

/**
 * \brief 快速中文字体，只能在中心设置字体（左底对齐）
 * \param str 输出字串
 * \param bStatic 是否为静态字体（可直接调用，不必重绘）
 */
void CFont966::Font3DChinese(CString str, BOOL bStatic)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	int front;
	glGetIntegerv(GL_FRONT_FACE, &front);
	if(bStatic)//是静态文本
	{
		int n=caFont3D.GetSize();
		int tag = n + 5;
		for(int i = 1; i < n; i++)//查找是否已经存在了这个字符串
		{
			if(str.Compare(caFont3D[i].string)==0)
			{
				tag = i;
				break;
			}		
		}
		if(tag < n)//找到了
		{

			for(int i = 0; i < caFont3D[tag].listLen; i++)
			{
				glCallList(caFont3D[tag].listStart + i);
			}
			glFrontFace(front);
			return;
		}
	}
	//没找到或者是变动的字符串
	HDC hDC = wglGetCurrentDC();
	//设置当前字体
	SelectObject(wglGetCurrentDC(), hFont3DChn);
	DWORD dwChar;
	CArray<DWORD,DWORD> dwCharArray;
	int n = str.GetLength();
	for(int i = 0; i < n; i++)
	{
		unsigned char a = static_cast<unsigned char>(str[i]);
		unsigned char b = 0;
		if(i < n - 1)
		{
			b = static_cast<unsigned char>(str[i + 1]);
		}
		if(IsDBCSLeadByte(a))
		{
			dwChar=static_cast<DWORD>(a << 8 | b);
			i++;
		}
		else
		{
			dwChar=a;
		}
		dwCharArray.Add(dwChar);
	}
	int ListBase = glGenLists(dwCharArray.GetSize());
	GLYPHMETRICSFLOAT pgmf[1];
	for(int i = 0; i < dwCharArray.GetSize(); i++)
	{
		wglUseFontOutlines(hDC, dwCharArray[i], 1, ListBase + i, 0.0, 0.1f, WGL_FONT_POLYGONS, pgmf);
	}
	//立即调用，调用结束后销毁。
	int len = dwCharArray.GetSize();
	for(int i = 0; i < len; i++)
	{
		glCallList(ListBase + i);
	}
	if(bStatic)//是静态文本
	{
		//保存下来
		FontList3D Font3D;
		Font3D.listLen = dwCharArray.GetSize();
		Font3D.listStart = ListBase;
		Font3D.string = str;
		caFont3D.Add(Font3D);
	}
	else//直接删除
	{
		glDeleteLists(ListBase,len);
	}
	glFrontFace(front);

	glPopAttrib();
}

void CFont966::Font3DChinese(CString str, CVector966 pos, double size, int format, BOOL bStatic)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslated(pos.x, pos.y, pos.z);
	glScalef(size, size, size);
	glScalef(2, 2, 2);
	float xoff = -(format & 3) * str.GetLength() * 0.25;
	float yoff = -(2 - (format >> 2 & 3)) * 0.455297 + 0.102;				//	 DT_TOP 0  DT_VCENTER 100 DT_BOTTOM 1000
	glTranslated(xoff,yoff,0);
	Font3DChinese(str,bStatic);
	glPopMatrix();

	glPopAttrib();
}

UCHAR* CFont966::CreateTextBmp(HDC hdc, HFONT font, char* str, SIZE sizeStr, SIZE& sizeImage)
{
	BITMAP bm;
	HBITMAP hbitmap = CreateBitmap(sizeStr.cx, sizeStr.cy, 1, 1, nullptr);
    HDC hMemDC = ::CreateCompatibleDC(hdc);
	HBITMAP hPrevBmp = static_cast<HBITMAP>(SelectObject(hMemDC, hbitmap));
	HFONT hPrevFont = static_cast<HFONT>(SelectObject(hMemDC, font));
	SetBkColor(hMemDC, RGB(0, 0, 0));
	::SetTextColor(hMemDC, RGB(255, 255, 255));
	SetBkMode(hMemDC, OPAQUE);
	TextOut(hMemDC, 0, 0, str, strlen(str));
	//把GDI位图复制到DIB
	GetObject(hbitmap, sizeof bm, &bm);
	sizeImage.cx = 31 + bm.bmWidth & ~31;
	sizeImage.cy = bm.bmHeight;
	int bufsize = sizeImage.cy * ((bm.bmWidth + 31 & ~31) /8);
	UCHAR * pBmpBits = new UCHAR[bufsize];
	memset(pBmpBits, 0, bufsize * sizeof(UCHAR));
	struct
	{
		BITMAPINFOHEADER bih;
		RGBQUAD col[2];
	}
	bic;
	BITMAPINFO *binf = (BITMAPINFO *)&bic;
	binf->bmiHeader.biSize = sizeof binf->bmiHeader;
	binf->bmiHeader.biWidth = bm.bmWidth;
	binf->bmiHeader.biHeight = bm.bmHeight;
	binf->bmiHeader.biPlanes = 1;
	binf->bmiHeader.biBitCount = 1;
	binf->bmiHeader.biCompression = BI_RGB;
	binf->bmiHeader.biSizeImage = bufsize;
	binf->bmiHeader.biXPelsPerMeter = 1;
	binf->bmiHeader.biYPelsPerMeter = 1;
	binf->bmiHeader.biClrUsed = 0;
	binf->bmiHeader.biClrImportant = 0;
	HBITMAP hPrevBmp2 = static_cast<HBITMAP>(SelectObject(hdc, hbitmap));
	::GetDIBits(hdc, hbitmap, 0, bm.bmHeight, pBmpBits, binf, DIB_RGB_COLORS);
	SelectObject(hdc, hPrevBmp2);
	SelectObject(hMemDC, hPrevBmp);
	::DeleteDC(hMemDC);
	DeleteObject(hbitmap);
	return pBmpBits;
}

BOOL CFont966::Create3DFont()
{
	int iFirstChar = 32 ;
	int iLastChar = 126 ;
	hFont3DEng = MakeFont("Segoe UI", 1);
	FontList3D Font3D;
	Font3D.listLen = iLastChar - iFirstChar ;
	Font3D.listStart = glGenLists(Font3D.listLen) ;
	iFont3DListbase = Font3D.listStart - iFirstChar ;
	// Get the DC for the current rendering context.	
	HDC hdc = wglGetCurrentDC();
	CDC* pdc = CDC::FromHandle(hdc) ;
	HFONT hOldFont = static_cast<HFONT>(pdc->SelectObject(hFont3DEng)) ;
	GLYPHMETRICSFLOAT agmf[128];
	wglUseFontOutlines(	hdc,
		iFirstChar,				// First character
		Font3D.listLen,			// Number
		Font3D.listStart,		// Starting Display list number
		0.0f,					// Deviation
		0.1f,					// Extrusion
		WGL_FONT_POLYGONS,		// Format or WGL_FONT_LINES
		agmf) ;					// Information pointer
	if (hOldFont)
	{
		pdc->SelectObject(hOldFont) ;
	}
	
	caFont3D.Add(Font3D);
	hFont3DChn = MakeFont("微软雅黑", 1);	//构造一个中文字体。
	return TRUE;
}

double CFont966::Create2DFont(char* lpszText, float x, float y, float z, int isize, int color, int format)
{
	if(isize == 0)
	{
		return 0.0;
	}
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(minCor, maxCor, minCor, maxCor, -100, 100);
	// 保存原模型变换矩阵，平移至( x, y )
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	int n = caFont2D.GetSize();
	HFONT font = 0;
	for(int i = 0; i < n; i++)
	{
		if(isize == caFont2D[i].size)
		{
			font = caFont2D[i].font;
			break;
		}
	}
	if(!font)//没找到
	{
		font = MakeFont("微软雅黑", isize);
		FontList2D font2D;
		font2D.font = font;
		font2D.size = isize;
		caFont2D.Add(font2D);
	}
	HDC hdc = wglGetCurrentDC();
	HFONT hOldFont = static_cast<HFONT>(SelectObject(hdc, font));
	SIZE sizeStr, sizeImage;
	::GetTextExtentPoint32(hdc, lpszText, strlen(lpszText), &sizeStr);
	//由于只能把一块内存的内容贴到当前hdc中，所以要构造内存数据给hdc
	UCHAR* pBmpBits=CreateTextBmp(hdc, font, lpszText, sizeStr, sizeImage);
	RECT rect;
    GetClientRect(hWnd,&rect);
	float xoff = -(format & 3) * sizeStr.cx / float(rect.right);		
	float yoff = -(2 - (format >> 2 & 3)) * sizeStr.cy / float(rect.bottom);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	int a = LOBYTE((color)>>24);
	if(a == 0 || a == 255)
	{
		glColor3ub(GetRValue(color), GetGValue(color), GetBValue(color));
	}
	else
	{
		glColor4ub(GetRValue(color), GetGValue(color), GetBValue(color), a);
	}	
	glRasterPos3d(x + xoff, y + yoff, -z);
    glBitmap(sizeImage.cx, sizeImage.cy, 0, 2.0, sizeImage.cx + 2.0f, 0.0, pBmpBits);
	delete []pBmpBits;
	SelectObject(hdc, hOldFont);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
	return double(sizeStr.cy) / rect.bottom;
}

HFONT CFont966::MakeFont(char* faceName, int height)
{
	LOGFONT lf;
	lf.lfHeight			= -height;
	lf.lfWidth			= 0;
	lf.lfEscapement		= 0;
	lf.lfOrientation	= 0;
	lf.lfWeight			= FW_NORMAL;
	lf.lfItalic			= FALSE;
	lf.lfUnderline		= FALSE;
	lf.lfStrikeOut		= FALSE;
	lf.lfCharSet		= DEFAULT_CHARSET;
	lf.lfOutPrecision	= OUT_TT_PRECIS;
	lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfQuality		= PROOF_QUALITY;
	lf.lfPitchAndFamily = VARIABLE_PITCH | TMPF_TRUETYPE | FF_MODERN;
	strcpy(lf.lfFaceName, faceName);
   // 创建字体
    return static_cast<HFONT>(CreateFontIndirect(&lf));
}
