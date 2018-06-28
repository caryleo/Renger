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
 * \brief 光栅位图2D字体
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
	hFont3DChn = MakeFont("等线", 1);	//构造一个中文字体。
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
		font = MakeFont("等线", isize);
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
	float xoff = -(format & 3) * sizeStr.cx / float(rect.right) / 2;		
	float yoff = -(2 - (format >> 2 & 3)) * sizeStr.cy / float(rect.bottom) / 2;
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
