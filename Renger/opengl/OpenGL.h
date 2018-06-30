// OpenGL.h: interface for the COpenGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL_H__E5995580_D8B1_4938_ADFE_4A915C808FF2__INCLUDED_)
#define AFX_OPENGL_H__E5995580_D8B1_4938_ADFE_4A915C808FF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "gl\glut.h"
#include "Modal966.h"
#include "Camera966.h"
#include "Control966.h"
#include "Vector966.h"
#include "Matrix966.h"
#include "Euler966.h"
#include "car.h"
#include "Scene.h"
#include "Quaternion966.h"


#include <afxver_.h>
#include "CFont966.h"
#include "aabb.h"
#include "car.h"
#include "CLoad3DS.h"
#include "../Button966.h"


class AFX_CLASS_EXPORT COpenGL  
{
public:
	virtual void InDraw();
	void OnView();
	bool PreTranslateMessage(unsigned int message,unsigned int wParam,unsigned int lParam);
	void OnSize(int w,int h);
	void OnPaint();
	virtual void Update();
	virtual void PostInit();
	bool Init(HWND hWnd);
	COpenGL();
	virtual ~COpenGL();
	virtual bool OnKey(unsigned int nChar,bool bDown);
	virtual bool OnMouse(int message,CPoint pt);
	friend class CControl966;
	friend class CCamera966;
	friend class CFont966;
	friend class CScene;
	friend class CStartButton966;
	friend class CEndButton966;
	friend class CRestartButton966;
	CAR *pCar;//����
	GLuint Launcher;
	GLuint START;
	GLuint STARTDOWN;
	GLuint ENDDOWN;
	GLuint RESTARTDOWN;
	GLuint END;
	GLuint RESTART;
protected:
	HDC hDC;
	HWND m_hmyWnd;			//���ƴ��ھ��,һ����View�ľ��
	HGLRC hglrc;
	float PerspectiveParam[4];
	CControl966 *pControl;
	HWND m_hWnd;
	CRect m_rect,m_windowrect;	//���ڴ�С
	CCamera966 *pCamera;
	CModal966 *pModal;
	CFont966 *pFont;
	CStartButton966 *csb;
	CEndButton966 *ceb;
	CRestartButton966 *crb;
	CScene *pScene;
	float fps;
};

#endif // !defined(AFX_OPENGL_H__E5995580_D8B1_4938_ADFE_4A915C808FF2__INCLUDED_)
