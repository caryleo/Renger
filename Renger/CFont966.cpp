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

void CFont966::Font2DBmp(CString str, double x, double y, int size, int color, int format)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
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
	if (hOldFont) pdc->SelectObject(hOldFont) ;
	caFont3D.Add(Font3D);
	hFont3DChn=MakeFont("等线", 1);	//构造一个中文字体。
	return TRUE;
}

double CFont966::Create2DFont(char* lpszText, double x, double y, double z, int isize, int color, int format)
{
	return 0;
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
