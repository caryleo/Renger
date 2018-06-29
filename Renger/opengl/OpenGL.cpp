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

bool COpenGL::Init(HWND hWnd)	//初始化OpenGL环境
{
	m_hWnd = hWnd;
	m_hmyWnd = hWnd;
	hDC = GetDC(hWnd);
	PIXELFORMATDESCRIPTOR pfd = //描述像素格式
	{
		sizeof(PIXELFORMATDESCRIPTOR),		// size of this pfd	结构大小
		1,                              // version number	结构版本，必须为1
		PFD_DRAW_TO_WINDOW |            // support window	像素格式选项标志（附表）
		PFD_SUPPORT_OPENGL |		    // support OpenGL
		//			PFD_GENERIC_ACCELERATED|		// 加速
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,                  // RGBA type		PFD_RGBA|PFD_INDEX RGB窗口或索引窗口
		24,                             // 24-bit color depth	所需颜色索引位数
		0,								// color bits ignored	所需红色位数
		0,								// color bits ignored	使用调色板转换为红色时，颜色位变化的数目
		0,								// color bits ignored   所需绿色位数
		0,								// color bits ignored   使用调色板转换为绿色时，颜色位变化的数目
		0,								// color bits ignored   所需蓝色位数
		0,								// color bits ignored   使用调色板转换为蓝色时，颜色位变化的数目            
		0,                              // no alpha buffer		所需的alpha颜色位数；对于一般的OpenGL安装而言，其值始终未0
		0,                              // shift bit ignored	转换为alpha颜色位数变化的数目；对于一般的OpenGL安装而言，其值始终未0
		0,                              // no accumulation buffer	实现累计所需要的颜色索引位数
		0, 0, 0, 0,                     // accum bits ignored	实现累计所需要的红色、绿色、蓝色、alpha色位数
		24,                             // 16-bit z-buffer		所需要的深度缓冲区位数
		0,                              // no stencil buffer	所需要的模版缓冲区位数
		0,                              // no auxiliary buffer	所需要的辅助缓冲区位数；对于一般的OpenGL安装而言，其值始终未0
		PFD_MAIN_PLANE,                 // main layer			WIN32API不使用和支持本变量
		0,                              // reserved				为将来的使用而准备的保留变量
		0,								// layer masks ignored	WIN32API不使用和支持本变量
		0,								// 指定RGBA或透明的索引色；本变量适应于覆盖图的像素格式 
		0								// WIN32API不使用和支持本变量
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

void COpenGL::PostInit()//负责继承类中的OpenGL初始化操作
{
}

void COpenGL::OnPaint()//每帧刷新函数
{
	Update();
	int begintime = GetTickCount();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glPushMatrix();
	::GetWindowRect(m_hmyWnd,m_windowrect);
	//glLoadIdentity();	//主绘制场景
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
//	 * 判断是否插值
//	 */
//}

void COpenGL::OnSize(int w, int h)	//调整视锥体参数
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
	//所有鼠标键盘消息发送到控制类中，由控制类定义对外设的响应，
	//并由控制类控制对视点的变换
	pControl->PreTranslateMessage(message,wParam,lParam);
	return false;
}

void COpenGL::OnView()
{
	//从相机类获得视点参数，此处设置视点信息
	pCamera->ShowView();
	pControl->KeyProcess();
}

void COpenGL::InDraw()
{
	//演示在(0,0,-5)位置绘制一个茶壶
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