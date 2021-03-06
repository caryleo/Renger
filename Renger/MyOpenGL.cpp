#include "StdAfx.h"
#include "MyOpenGL.h"

#include <cmath>
#include <iostream>
#include "Button966.h"
#define POINTNUM 200
#define CIRCLENUM 20
#define PI 3.1415926
#define BMP_Header_Length 54  //图像数据在内存块中的偏移量  
CModelLoader m_loader_car;
CModelLoader m_loader_lupai;
CModelLoader m_loader_yuaubao;
CModelLoader m_loader_hulan;
CModelLoader m_loader_fangwu;
CModelLoader m_loader_fangwu2;
CModelLoader m_loader_luren;
CModelLoader m_loader_lupai4;
CModelLoader m_loader_shu;
CModelLoader m_loader_jiantou;
GLuint texLine;//终点线
GLuint texRoad;//公路材质


struct Hulan
{
	double x, z, rotate;
} hulan[100];

int hulanCnt = 0;

CMyOpenGL::CMyOpenGL(void)
{
}


CMyOpenGL::~CMyOpenGL(void)
{
}


/**
* \brief 初始化
*/
void CMyOpenGL::PostInit(void)
{
	texRoad = load_texture("Data/road.bmp");
	texLine = load_texture("Data/endline.bmp");
	Launcher = load_texture("Data/carr.bmp");
	START = load_texture("Data/003.bmp");
	STARTDOWN = load_texture("Data/004.bmp");
	END = load_texture("Data/001.bmp");
	ENDDOWN = load_texture("Data/002.bmp");
	RESTART = load_texture("Data/005.bmp");
	RESTARTDOWN = load_texture("Data/006.bmp");
	m_loader_lupai.Init(3);//路牌
	m_loader_car.Init(2);//汽车
	m_loader_lupai4.Init(4);//路牌4
	m_loader_luren.Init(5);//路人
	m_loader_yuaubao.Init(11);//元宝
	m_loader_hulan.Init(10);//护栏
	m_loader_fangwu.Init(9);//房屋
	m_loader_fangwu2.Init(8);//房屋2
	m_loader_shu.Init(1);//树
	m_loader_jiantou.Init(12);//箭头
	pCar->init(Point_AABB(0,0,400,4,4,8,0,0,-1),0);//初始化汽车类
	pCar->setGothicTrans_car(
		0, 0 , 400,   
		0.00003 , 0.00003 , 0.00003 ,      
		0 , 0 , 0 , 0);

	pCar->addWall(50,-20,450,50,380,350);
	pCar->addWall(50,-20,350,450,380,350);
	pCar->addWall(450,-20,350,450,380,-200);
	pCar->addWall(450,-20,-200,250,380,-200);
	pCar->addWall(250,-20,-200,250,380,-450);
	pCar->addWall(250,-20,-450,-350,380,-450);
	pCar->addWall(-350,-20,-450,-350,380,100);
	pCar->addWall(-350,-20,100,-250,380,100);
	pCar->addWall(-250,-20,100,-250,380,450);
	pCar->addWall(-250,-20,450,50,380,450);

	pCar->addWall(-50,-20,350,-50,380,250);
	pCar->addWall(-50,-20,250,350,380,250);
	pCar->addWall(350,-20,250,350,380,-100);
	pCar->addWall(350,-20,-100,150,380,-100);
	pCar->addWall(150,-20,-100,150,380,-350);
	pCar->addWall(150,-20,-350,-250,380,-350);
	pCar->addWall(-250,-20,-350,-250,380,0);
	pCar->addWall(-250,-20,0,-150,380,0);
	pCar->addWall(-150,-20,0,-150,380,350);
	pCar->addWall(-150,-20,350,-50,380,350);

	pCar->addYuanbao(0,300);
	pCar->addYuanbao(150,300);
	pCar->addYuanbao(400,300);
	pCar->addYuanbao(400,50);
	pCar->addYuanbao(300,-150);
	pCar->addYuanbao(-300,-250);
	pCar->addYuanbao(-200,50);
	pCar->addYuanbao(-200,400);

	pCamera->SetGameMode(0);

	/** 用户自定义的初始化过程 */
	///定义光源GL_LIGHT0
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 }; /**< 环境光 */
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; /**< 漫射光 */
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };/**< 镜面光 */
	GLfloat position[] = { 250.0, 80.0, 250.0, 0.0 };/**< 光源位置 */
    GLfloat position4[] = { 300.0, 100.0, -100.0, 0.0 };/**< 光源位置 */


	///设置光源属性
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	///设置光源属性
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, position4);

	/////初始化
	//glClearColor(0.0f, 0.2f, 0.2f, 0.0f);						
	glClearDepth(1.0f);	
	glDepthFunc(GL_LEQUAL);	
	glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING); /**< 启用光源 */
	glEnable(GL_LIGHT0);  /**< 启用0号光源 */   
	glEnable(GL_LIGHT3);  /**< 启用0号光源 */ 
}


/**
* \brief 绘制主控
*/
void CMyOpenGL::changeGothicTrans(float trans[], double x, double y, double z, double a, double b, double c, double r,
                                  double _x, double _y, double _z)
{
	trans[0] = x;
	trans[1] = y;
	trans[2] = z;
	trans[3] = a;
	trans[4] = b;
	trans[5] = c;
	trans[6] = r;
	trans[7] = _x;
	trans[8] = _y;
	trans[9] = _z;
}

void CMyOpenGL::hulanInit()
{
	hulanCnt = 0;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 50;
	hulan[hulanCnt++].z = 400;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 100;
	hulan[hulanCnt++].z = 350;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 200;
	hulan[hulanCnt++].z = 350;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 300;
	hulan[hulanCnt++].z = 350;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 400;
	hulan[hulanCnt++].z = 350;

	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 450;
	hulan[hulanCnt++].z = 300;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 450;
	hulan[hulanCnt++].z = 200;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 450;
	hulan[hulanCnt++].z = 100;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 450;
	hulan[hulanCnt++].z = 0;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 450;
	hulan[hulanCnt++].z = -100;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 450;
	hulan[hulanCnt++].z = -200;

	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 400;
	hulan[hulanCnt++].z = -200;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 300;
	hulan[hulanCnt++].z = -200;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 250;
	hulan[hulanCnt++].z = -250;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 250;
	hulan[hulanCnt++].z = -350;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 250;
	hulan[hulanCnt++].z = -450;

	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 200;
	hulan[hulanCnt++].z = -450;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 100;
	hulan[hulanCnt++].z = -450;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 0;
	hulan[hulanCnt++].z = -450;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -100;
	hulan[hulanCnt++].z = -450;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -200;
	hulan[hulanCnt++].z = -450;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -300;
	hulan[hulanCnt++].z = -450;

	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -350;
	hulan[hulanCnt++].z = -400;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -350;
	hulan[hulanCnt++].z = -300;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -350;
	hulan[hulanCnt++].z = -200;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -350;
	hulan[hulanCnt++].z = -100;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -350;
	hulan[hulanCnt++].z = 0;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -350;
	hulan[hulanCnt++].z = 50;

	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -300;
	hulan[hulanCnt++].z = 100;

	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -250;
	hulan[hulanCnt++].z = 150;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -250;
	hulan[hulanCnt++].z = 250;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -250;
	hulan[hulanCnt++].z = 350;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -250;
	hulan[hulanCnt++].z = 450;

	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -200;
	hulan[hulanCnt++].z = 450;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -100;
	hulan[hulanCnt++].z = 450;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 0;
	hulan[hulanCnt++].z = 450;

	/*********************************************************/
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -50;
	hulan[hulanCnt++].z = 300;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 0;
	hulan[hulanCnt++].z = 250;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 100;
	hulan[hulanCnt++].z = 250;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 200;
	hulan[hulanCnt++].z = 250;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 300;
	hulan[hulanCnt++].z = 250;

	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 350;
	hulan[hulanCnt++].z = 200;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 350;
	hulan[hulanCnt++].z = 100;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 350;
	hulan[hulanCnt++].z = 0;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 350;
	hulan[hulanCnt++].z = -50;


	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 300;
	hulan[hulanCnt++].z = -100;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 200;
	hulan[hulanCnt++].z = -100;

	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 150;
	hulan[hulanCnt++].z = -150;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 150;
	hulan[hulanCnt++].z = -250;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = 150;
	hulan[hulanCnt++].z = -300;

	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 100;
	hulan[hulanCnt++].z = -350;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = 0;
	hulan[hulanCnt++].z = -350;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -100;
	hulan[hulanCnt++].z = -350;
	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -200;
	hulan[hulanCnt++].z = -350;


	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -250;
	hulan[hulanCnt++].z = -300;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -250;
	hulan[hulanCnt++].z = -200;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -250;
	hulan[hulanCnt++].z = -100;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -250;
	hulan[hulanCnt++].z = -100;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -250;
	hulan[hulanCnt++].z = -50;


	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -200;
	hulan[hulanCnt++].z = 0;

	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -150;
	hulan[hulanCnt++].z = 50;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -150;
	hulan[hulanCnt++].z = 150;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -150;
	hulan[hulanCnt++].z = 250;
	hulan[hulanCnt].rotate = 90;
	hulan[hulanCnt].x = -150;
	hulan[hulanCnt++].z = 300;

	hulan[hulanCnt].rotate = 0;
	hulan[hulanCnt].x = -100;
	hulan[hulanCnt++].z = 350;
}

void CMyOpenGL::drawHulan()
{
	hulanInit();
	float gothicTrans_hulan[10];
	for (int i = 0; i < hulanCnt; i++)
	{
		changeGothicTrans(gothicTrans_hulan,
		                  hulan[i].x, -20, hulan[i].z, //表示在世界矩阵的位置  
		                  1, 2.2, 1, //表示xyz放大倍数  
		                  90 - hulan[i].rotate, 0, 1, 0 //表示旋转  
		);
		m_loader_hulan.DrawModel(gothicTrans_hulan);
	}
}

void CMyOpenGL::InDraw(void)
{
	/** 用户自定义的绘制过程 */
	///定义材质属性值
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 }; /** < 无材质颜色 */
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; /** < 环境颜色 */
	GLfloat mat_diffuse[] = { 0.2, 0.5, 0.8, 1.0 };/** < 散射颜色 */
	GLfloat no_shininess[] = { 0.0 };              /** < 镜面反射指数为0 */
	if (pCamera->iGameMode == 0)
	{
		glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		{
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glClearColor(255, 255, 255, 0);
			glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, Launcher);
			glColor3b(1, 1, 1);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 1.0);
			glVertex2d(-1.0, 1.0);
			glTexCoord2f(0.0, 0.0);
			glVertex2d(-1.0, -1.0);
			glTexCoord2f(1.0, 0.0);
			glVertex2d(1.0, -1.0);
			glTexCoord2f(1.0, 1.0);
			glVertex2d(1.0, 1.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopAttrib();
			RECT rect;
			GetClientRect(m_hWnd, &rect);
			int cenx = (rect.right - rect.left) / 2;
			int ceny = (rect.bottom - rect.top) / 2;
			csb->Set(cenx, ceny - 100, 512, 128);
			csb->render(rect);
			CString startStr;
			startStr.Format("RENGER");
			pFont->Font2D(startStr, CVector966(0, 0.3, 0), 96, RGB(200, 100, 44), DT_CENTER | DT_BOTTOM, 0);
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
		glPopAttrib();
	}
	else if (pCamera->iGameMode == 1)
	{
		glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_TEXTURE_BIT);
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		pScene->Render();
		glPopMatrix();
		//DrawAxes(1000);

		glPushAttrib(GL_TEXTURE_BIT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		float gothicTrans_fangwu[10] = {
			100, -10, 200, //表示在世界矩阵的位置  
			0.2, 0.2, 0.2, //表示xyz放大倍数  
			180, 0, 1, 0 //表示旋转  
		};
		m_loader_fangwu.DrawModel(gothicTrans_fangwu);
		changeGothicTrans(gothicTrans_fangwu,
		                  150, -10, 400, //表示在世界矩阵的位置  
		                  0.2, 0.2, 0.2, //表示xyz放大倍数  
		                  90, 0, 1, 0 //表示旋转  
		);
		m_loader_fangwu2.DrawModel(gothicTrans_fangwu);
		changeGothicTrans(gothicTrans_fangwu,
		                  -300, -10, 250, //表示在世界矩阵的位置  
		                  0.2, 0.2, 0.2, //表示xyz放大倍数  
		                  -90, 0, 1, 0 //表示旋转  
		);
		m_loader_fangwu.DrawModel(gothicTrans_fangwu);
		changeGothicTrans(gothicTrans_fangwu,
		                  -150, -10, -250, //表示在世界矩阵的位置  
		                  0.2, 0.2, 0.2, //表示xyz放大倍数  
		                  0, 0, 1, 0 //表示旋转  
		);
		m_loader_fangwu.DrawModel(gothicTrans_fangwu);
		changeGothicTrans(gothicTrans_fangwu,
		                  100, -10, -250, //表示在世界矩阵的位置  
		                  0.2, 0.2, 0.2, //表示xyz放大倍数  
		                  90, 0, 1, 0 //表示旋转  
		);

		m_loader_fangwu2.DrawModel(gothicTrans_fangwu);

		float gothicTransLupai4[10] = {
			450, 0, -50, //表示在世界矩阵的位置  
			0.2, 0.1, 0.1, //表示xyz放大倍数  
			0, 0, 1, 0 //表示旋转  
		};
		m_loader_lupai4.DrawModel(gothicTransLupai4);

		float gothicTransLuren[10] = {
			-100, 0, 200, //表示在世界矩阵的位置  
			0.2, 0.2, 0.2, //表示xyz放大倍数  
			0, 0, 1, 0 //表示旋转  
		};
		m_loader_luren.DrawModel(gothicTransLuren);

		float gothicTrans_shu[10] = {
			-120, 0, 200,
			0.2, 0.2, 0.2,
			0, 0, 1, 0
		};
		m_loader_shu.DrawModel(gothicTrans_shu);

		float gothicTrans_Lupai[10] = {
			0, -5, -50, //表示在世界矩阵的位置  
			0.08, 0.08, 0.8, //表示xyz放大倍数  
			0, 0, 1, 0 //表示旋转  
		};
		m_loader_lupai.DrawModel(gothicTrans_Lupai);
		glPopMatrix();
		//glPopAttrib();

		glPushMatrix();
		//pCar->car_box.DrawAABBBoundingBox();//画出车的包围盒

		glPushMatrix();
		CString tmp;
		tmp.Format("李东的小保时捷");
		CVector966 tmpPos(float(pCar->car_point.x), float(pCar->car_point.y) + 2, float(pCar->car_point.z));
		CString Score;
		Score.Format("当前分数：%d", pCar->score);
		pFont->Font2D(Score, CVector966(-0.9, 0.8, 0), 24, RGB(255, 255, 255), 0 | 8, 0);

		CString nowTime;
		nowTime.Format("当前时间：%.2lf s", static_cast<double>(pCar->now - pCar->start) / CLOCKS_PER_SEC);
		pFont->Font2D(nowTime, CVector966(-0.9, 0.7, 0), 24, RGB(255, 255, 255), 0 | 8, 0);
		if (pCar->endFlag == 1)
		{
			CString isEnd, _time;
			isEnd.Format("游戏结束");
			_time.Format("用时：%.2lf s", static_cast<double>(pCar->end - pCar->start) / CLOCKS_PER_SEC);
			pFont->Font2D(_time, CVector966(-0.9, 0.4, 0), 24, RGB(255, 255, 255), 0 | 8, 0);
			pFont->Font2D(isEnd, CVector966(-0.9, 0.5, 0), 24, RGB(255, 255, 255), 0 | 8, 0);
		}
		/*CString pos;
		pos.Format("当前车位置：（%.2lf，%.2lf，%.2lf）", pCar->car_point.x, pCar->car_point.y, pCar->car_point.z);
		pFont->Font2D(pos, CVector966(-0.9, 0.8, 0), 24, RGB(255, 255, 255), 0|8 , 0);*/
		/*CString dir;
		dir.Format("当前车头朝向：（%.2lf，%.2lf，%.2lf）", pCar->car_point.dirx, pCar->car_point.diry, pCar->car_point.dirz);
		pFont->Font2D(dir, CVector966(-0.9, 0.6, 0), 24, RGB(255, 255, 255), 0|8 , 0);*/
		pFont->Font2D(tmp, tmpPos, 24, RGB(255,255,255), DT_CENTER | DT_BOTTOM, 1);
		
		glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

		m_loader_car.DrawModel(pCar->gothicTrans_car);
		glPopMatrix();

		for (int i = 0; i < pCar->wall.size(); i++)
		{
			//pCar->wall[i].DrawAABBBoundingBox();
		}

		//画元宝
		float gothicTrans_yuanbao[10];
		for (int i = 0; i < pCar->yuanbao.size(); i++)
		{
			if (pCar->yuanbaoFlag[i] != 1)
			{
				//pCar->yuanbao[i].DrawAABBBoundingBox();
				changeGothicTrans(gothicTrans_yuanbao,
				                  (pCar->yuanbao[i].Xmax + pCar->yuanbao[i].Xmin) / 2, 0,
				                  (pCar->yuanbao[i].Zmax + pCar->yuanbao[i].Zmin) / 2,
				                  0.2, 0.2, 0.2, //表示xyz放大倍数  
				                  0, 0, 1, 0 //表示旋转  
				);
				m_loader_yuaubao.DrawModel(gothicTrans_yuanbao);
			}
		}

		drawArrow();
		drawHulan();//画护栏
		glPushMatrix();
		drawAllRoad();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texLine);
		// 画终点线
		glBegin(GL_QUADS);    
		glTexCoord2f(0.0f, 1); glVertex3f(-70,  -1.9, 350);  // 纹理和四边形的左上  
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-70,  -1.9,  450);  // 纹理和四边形的左下  
		glTexCoord2f(1, 0.0f); glVertex3f( -50,  -1.9,  450);  // 纹理和四边形的右下  
		glTexCoord2f(1, 1); glVertex3f( -50,  -1.9, 350);  // 纹理和四边形的右上  
		glEnd();  
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		CString str;
		str.Format("fps：%.2f 帧每秒", fps);
		pFont->Font2D(str, CVector966(-0.9f, 0.9f, 0), 24, RGB(255, 255, 255), 0 | 8, 0);
		CString sp;
		sp.Format("当前速度：%.2lf m/s", pCar->speed);
		pFont->Font2D(sp, CVector966(-0.9f, 0.6f, 0), 24, RGB(255, 255, 255), 0 | 8, 0);
		glPopMatrix();
		glPopAttrib();
		glPopAttrib();
	}
	else if (pCamera->iGameMode == 2)
	{
		glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		{
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glClearColor(255, 255, 255, 0);
			glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, Launcher);
			glColor3b(1, 1, 1);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 1.0);
			glVertex2d(-1.0, 1.0);
			glTexCoord2f(0.0, 0.0);
			glVertex2d(-1.0, -1.0);
			glTexCoord2f(1.0, 0.0);
			glVertex2d(1.0, -1.0);
			glTexCoord2f(1.0, 1.0);
			glVertex2d(1.0, 1.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopAttrib();
			RECT rect;
			GetClientRect(m_hWnd, &rect);
			int cenx = (rect.right - rect.left) / 2;
			int ceny = (rect.bottom - rect.top) / 2;
			int e = glGetError();
			ceb->Set(cenx, ceny - 50, 512, 128);
			ceb->render(rect);
			crb->Set(cenx, ceny - 200, 512, 128);
			crb->render(rect);
			int f = glGetError();
			CString endStr;
			endStr.Format("游戏结束");
			pFont->Font2D(endStr, CVector966(0, 0.4, 0), 96, RGB(55, 205, 84), DT_CENTER | DT_BOTTOM, 0);
			CString scoreStr;
			scoreStr.Format("得分：%d", pCar->score);
			pFont->Font2D(scoreStr, CVector966(0, 0.3, 0), 24, RGB(0, 255, 0), DT_CENTER | DT_BOTTOM, 0);
			CString timeStr;
			timeStr.Format("用时：%.2f s", static_cast<double>(pCar->end - pCar->start) / CLOCKS_PER_SEC);
			pFont->Font2D(timeStr, CVector966(0, 0.2, 0), 24, RGB(0, 255, 0), DT_CENTER | DT_BOTTOM, 0);
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
		glPopAttrib();
	}


}

bool CMyOpenGL::OnKey(unsigned char nChar, bool bDown)
{
	return false;
}

/**
* \brief 更新主控
*/
void CMyOpenGL::Update()
{
	pCar->update();
	if (pCar->endFlag == 1)
	{
		pCamera->SetGameMode(2);
	}
}

/**
 * \brief 绘制坐标轴
 */
void CMyOpenGL::DrawAxes(int size)
{
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}


//纹理相关
// 函数power_of_two用于判断一个整数是不是2的整数次幂  
int CMyOpenGL::power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/* 函数load_texture 
* 读取一个BMP文件作为纹理 
* 如果失败，返回0，如果成功，返回纹理编号 
*/
GLuint CMyOpenGL::load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	// 打开文件，如果失败，返回  
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// 读取文件中图象的宽度和高度  
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数  
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存  
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据  
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放  
	// 若图像宽高超过了OpenGL规定的最大值，也缩放  
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形  
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数  
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存  
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放  
			gluScaleImage(GL_RGB,
			              width, height, GL_UNSIGNED_BYTE, pixels,
			              new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height  
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号  
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数  
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复  
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
	             GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID); //恢复之前的纹理绑定  
	free(pixels);
	return texture_ID;
}

void CMyOpenGL::drawRoad(double x, double z)
{
	glBegin(GL_QUADS);
	// 顶面  
	glTexCoord2f(0.0f, 1);
	glVertex3f(x, -2, z - 100); // 纹理和四边形的左上  
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, -2, z); // 纹理和四边形的左下  
	glTexCoord2f(1, 0.0f);
	glVertex3f(x + 100, -2, z); // 纹理和四边形的右下  
	glTexCoord2f(1, 1);
	glVertex3f(x + 100, -2, z - 100); // 纹理和四边形的右上  
	glEnd();
}

void CMyOpenGL::drawAllRoad()
{
	glPushAttrib(GL_TEXTURE_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	int xx[100] = {0};
	int zz[100] = {0};
	int tmpcnt = 0;
	xx[tmpcnt] = -50;
	zz[tmpcnt++] = 450;
	xx[tmpcnt] = -50;
	zz[tmpcnt++] = 350;
	xx[tmpcnt] = 50;
	zz[tmpcnt++] = 350;
	xx[tmpcnt] = 150;
	zz[tmpcnt++] = 350;
	xx[tmpcnt] = 250;
	zz[tmpcnt++] = 350;
	xx[tmpcnt] = 350;
	zz[tmpcnt++] = 350;
	xx[tmpcnt] = 350;
	zz[tmpcnt++] = 250;
	xx[tmpcnt] = 350;
	zz[tmpcnt++] = 150;
	xx[tmpcnt] = 350;
	zz[tmpcnt++] = 50;
	xx[tmpcnt] = 350;
	zz[tmpcnt++] = -50;
	xx[tmpcnt] = 350;
	zz[tmpcnt++] = -150;
	xx[tmpcnt] = 250;
	zz[tmpcnt++] = -100;
	xx[tmpcnt] = 150;
	zz[tmpcnt++] = -100;
	xx[tmpcnt] = 150;
	zz[tmpcnt++] = -200;
	xx[tmpcnt] = 150;
	zz[tmpcnt++] = -300;
	xx[tmpcnt] = 150;
	zz[tmpcnt++] = -400;
	xx[tmpcnt] = 50;
	zz[tmpcnt++] = -350;
	xx[tmpcnt] = -50;
	zz[tmpcnt++] = -350;
	xx[tmpcnt] = -150;
	zz[tmpcnt++] = -350;
	xx[tmpcnt] = -250;
	zz[tmpcnt++] = -350;
	xx[tmpcnt] = -350;
	zz[tmpcnt++] = -350;
	xx[tmpcnt] = -350;
	zz[tmpcnt++] = -250;
	xx[tmpcnt] = -350;
	zz[tmpcnt++] = -150;
	xx[tmpcnt] = -350;
	zz[tmpcnt++] = -50;
	xx[tmpcnt] = -350;
	zz[tmpcnt++] = 50;
	xx[tmpcnt] = -350;
	zz[tmpcnt++] = 100;
	xx[tmpcnt] = -250;
	zz[tmpcnt++] = 100;
	xx[tmpcnt] = -250;
	zz[tmpcnt++] = 100;
	xx[tmpcnt] = -250;
	zz[tmpcnt++] = 200;
	xx[tmpcnt] = -250;
	zz[tmpcnt++] = 300;
	xx[tmpcnt] = -250;
	zz[tmpcnt++] = 400;
	xx[tmpcnt] = -250;
	zz[tmpcnt++] = 450;
	xx[tmpcnt] = -150;
	zz[tmpcnt++] = 450;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texRoad);
	for (int i = 0; i < tmpcnt; i++)
	{
		drawRoad(xx[i], zz[i]);
	}
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
}

void CMyOpenGL::drawArrow()
{
	double tmprotate = 0;
	double cx = pCar->car_point.x, cz = pCar->car_point.z;
	if (cx >= -250 && cx <= -50 && cz >= 350 && cz <= 450)
	{
		tmprotate = 270;
	}
	else if (cx >= -50 && cx <= 350 && cz >= 250 && cz <= 350)
	{
		tmprotate = 270;
	}
	else if (cx >= 250 && cx <= 450 && cz >= -200 && cz <= -100)
	{
		tmprotate = 90;
	}
	else if (cx >= -250 && cx <= 250 && cz >= -450 && cz <= -350)
	{
		tmprotate = 90;
	}
	else if (cx >= -350 && cx <= -250 && cz >= -450 && cz <= 0)
	{
		tmprotate = 180;
	}
	else if (cx >= -350 && cx <= -250 && cz >= 0 && cz <= 100)
	{
		tmprotate = 270;
	}
	else if (cx >= -250 && cx <= -150 && cz >= 0 && cz <= 350)
	{
		tmprotate = 180;
	}

	float gothicTrans_arrow[10] = {
		cx + 1, 4, cz, //表示在世界矩阵的位置  
		0.2, 0.2, 0.2, //表示xyz放大倍数  
		tmprotate, 0, 1, 0 //表示旋转  
	};
	m_loader_jiantou.DrawModel(gothicTrans_arrow);
}