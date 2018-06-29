// OpenGL.cpp: implementation of the COpenGL class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "OpenGL.h"
#include <atltypes.h>
#include "Mmsystem.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpenGL::COpenGL()
{
	m_hWnd=0;
	hDC=0;
	hglrc=0;
	m_hmyWnd = 0;
	pCamera=NULL;
	pControl=NULL;
	pCar=NULL;
}

COpenGL::~COpenGL()
{
	delete pCamera;
	delete pControl;
	delete pCar;
}

bool COpenGL::Init(HWND hWnd)	//��ʼ��OpenGL����
{
	m_hWnd = hWnd;
	m_hmyWnd = hWnd;
	hDC = GetDC(hWnd);
	PIXELFORMATDESCRIPTOR pfd = //�������ظ�ʽ
	{
		sizeof(PIXELFORMATDESCRIPTOR),		// size of this pfd	�ṹ��С
		1,                              // version number	�ṹ�汾������Ϊ1
		PFD_DRAW_TO_WINDOW |            // support window	���ظ�ʽѡ���־������
		PFD_SUPPORT_OPENGL |		    // support OpenGL
		//			PFD_GENERIC_ACCELERATED|		// ����
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,                  // RGBA type		PFD_RGBA|PFD_INDEX RGB���ڻ���������
		24,                             // 24-bit color depth	������ɫ����λ��
		0,								// color bits ignored	�����ɫλ��
		0,								// color bits ignored	ʹ�õ�ɫ��ת��Ϊ��ɫʱ����ɫλ�仯����Ŀ
		0,								// color bits ignored   ������ɫλ��
		0,								// color bits ignored   ʹ�õ�ɫ��ת��Ϊ��ɫʱ����ɫλ�仯����Ŀ
		0,								// color bits ignored   ������ɫλ��
		0,								// color bits ignored   ʹ�õ�ɫ��ת��Ϊ��ɫʱ����ɫλ�仯����Ŀ            
		0,                              // no alpha buffer		�����alpha��ɫλ��������һ���OpenGL��װ���ԣ���ֵʼ��δ0
		0,                              // shift bit ignored	ת��Ϊalpha��ɫλ���仯����Ŀ������һ���OpenGL��װ���ԣ���ֵʼ��δ0
		0,                              // no accumulation buffer	ʵ���ۼ�����Ҫ����ɫ����λ��
		0, 0, 0, 0,                     // accum bits ignored	ʵ���ۼ�����Ҫ�ĺ�ɫ����ɫ����ɫ��alphaɫλ��
		24,                             // 16-bit z-buffer		����Ҫ����Ȼ�����λ��
		0,                              // no stencil buffer	����Ҫ��ģ�滺����λ��
		0,                              // no auxiliary buffer	����Ҫ�ĸ���������λ��������һ���OpenGL��װ���ԣ���ֵʼ��δ0
		PFD_MAIN_PLANE,                 // main layer			WIN32API��ʹ�ú�֧�ֱ�����
		0,                              // reserved				Ϊ������ʹ�ö�׼���ı�������
		0,								// layer masks ignored	WIN32API��ʹ�ú�֧�ֱ�����
		0,								// ָ��RGBA��͸��������ɫ����������Ӧ�ڸ���ͼ�����ظ�ʽ 
		0								// WIN32API��ʹ�ú�֧�ֱ�����
	};	
	int pf = ChoosePixelFormat(hDC, &pfd);
	if(!pf)	return FALSE;
	if (!SetPixelFormat(hDC, pf, &pfd))
		return FALSE;
	hglrc = wglCreateContext(hDC);
	wglMakeCurrent(hDC,hglrc);

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	PerspectiveParam[0]=60;
	PerspectiveParam[2]=0.1;
	PerspectiveParam[3]=10000;

	pModal = new CModal966;
	pCar=new CAR();
	
	pCamera = new CCamera966(this);
	pControl = new CControl966(this);
	pFont = new CFont966(this->pCamera, this->m_hmyWnd);

	pControl->cpMousePos.x = m_rect.right / 2;
	pControl->cpMousePos.y = m_rect.bottom / 2;
	PostInit();
	return true;
}

void COpenGL::PostInit()//����̳����е�OpenGL��ʼ������
{
}

void COpenGL::OnPaint()//ÿ֡ˢ�º���
{
	Update();
	int begintime = GetTickCount();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glPushMatrix();
	::GetWindowRect(m_hmyWnd,m_windowrect);
	//glLoadIdentity();	//�����Ƴ���
	OnView();
	InDraw();
	glPopMatrix();
	SwapBuffers(hDC);
	int usetime = GetTickCount()-begintime;
	if(usetime>1)
		fps = 1000.0/usetime;
}

void COpenGL::Update()
{
}

//void COpenGL::Update()
//{
//	/**
//	 * �ж��Ƿ��ֵ
//	 */
//}

void COpenGL::OnSize(int w, int h)	//������׶�����
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	m_rect.SetRect(0, 0, w, h);
	PerspectiveParam[1]=(GLfloat)w / h;
	gluPerspective(PerspectiveParam[0],PerspectiveParam[1],PerspectiveParam[2],PerspectiveParam[3]);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	::GetWindowRect(m_hmyWnd,m_windowrect);
}

bool COpenGL::PreTranslateMessage(unsigned int message, unsigned int wParam, unsigned int lParam)
{
	//������������Ϣ���͵��������У��ɿ����ඨ����������Ӧ��
	//���ɿ�������ƶ��ӵ�ı任
	pControl->PreTranslateMessage(message,wParam,lParam);
	return false;
}

void COpenGL::OnView()
{
	//����������ӵ�������˴������ӵ���Ϣ
	pCamera->ShowView();
	pControl->KeyProcess();
}

void COpenGL::InDraw()
{
	//��ʾ��(0,0,-5)λ�û���һ�����
	/*glPushMatrix();
	glTranslatef(0,0,-5);
	glutSolidTeapot(2);
	glPopMatrix();*/
}
bool COpenGL::OnKey(unsigned int nChar,bool bDown)
{
	return false;
}
bool COpenGL::OnMouse(int button,CPoint pt)
{
	return false;
}