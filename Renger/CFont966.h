#pragma once

#include "opengl\Vector966.h"
#include "afxtempl.h"

class AFX_CLASS_EXPORT CFont966
{
public:
	struct FontList3D		
	{
		int listStart;
		int listLen;
		CString string;
	};
	struct FontList2D
	{
		int size;	//字体大小
		HFONT font;	//字体
	};
	CFont966(CCamera966 *pCamera, HWND hWnd);
	~CFont966();
	void SetOrthoRange(float minVar, float maxVar);
	void PushOrthoRange();
	void PopOrthoRange();
	void Font2D(CString lpszText, CVector966 pos, int size = 24, int color = RGB(255, 255, 255),
	            int format = DT_LEFT | DT_BOTTOM, int type = 1);
	void Font2DBmp(CString str, double x, double y, int size, int color = RGB(255, 255, 255),
	               int format = DT_LEFT | DT_BOTTOM);
	void Font3DEnglish(CString str);					//英文3d字，快
	void Font3DEnglish(CString str, CVector966 pos, double size, int format, CVector966 *normal = 0);	//带格式，大小(以A字符的米为大小)
	void Font3DChinese(CString str, BOOL bStatic = false);	//中文3d字,是否是静态文字。如果是静态文字则不需要每次重新构造字体，速度更快。
	void Font3DChinese(CString str, CVector966 pos,double size,int format,BOOL bStatic=false);
private:
	UCHAR*	CreateTextBmp(HDC hdc,HFONT font,char * str,SIZE sizeStr,SIZE &sizeImage);
	BOOL	Create3DFont();	//构造英文全字体，启动时候就构造，以后不需要重复构造。包括了构造显示列表。中文只构造字体不构造显示列表
	double	Create2DFont(char *lpszText, double x, double y, double z, int isize, int color, int format);
	HFONT	MakeFont(char *faceName, int height);
	HFONT hFont3DEng, hFont3DChn;	//对应3的的中英文字体。
	int iFont3DListbase;			//3D字体的listbase
	CArray<FontList3D, FontList3D&> caFont3D;//3D 字的列表。
	CArray<FontList2D, FontList2D&> caFont2D;//2D 字的列表。
	CArray<HFONT, HFONT> caHFont2D;	//保存了已经生成的字体。
	CArray<int, int> caHFontSSize;	//保存了已经生成的字体的大小。
	HFONT hFont;
	int iFontSize;//2维字体大小
	CCamera966 *pCamera;
	HWND hWnd;
	float maxCor, minCor;
	CArray<float, float> caRangeCor;
};
