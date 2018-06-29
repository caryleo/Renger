#include "StdAfx.h"
#include "MyOpenGL.h"
#include "aabb.h"
#include "car.h"
#include "CLoad3DS.h"
#include <cmath>
#include <iostream>
#define POINTNUM 200
#define CIRCLENUM 20
#define PI 3.1415926
CModelLoader m_loader_car;
CModelLoader m_loader_lupai;
CModelLoader m_loader_yuaubao;
CModelLoader m_loader_hulan;
CModelLoader m_loader_fangwu;
CModelLoader m_loader_fangwu2;
CModelLoader m_loader_luren;
CModelLoader m_loader_lupai4;
struct Hulan
{
	double x,z,rotate;
}hulan[100];
int hulanCnt=0;

CVector966 tracePointPos[POINTNUM];//姓名轨迹点
CVector966 refCircle[CIRCLENUM];//参考圆轨迹点
CVector966 allPointPos[POINTNUM*CIRCLENUM];//计算轨迹点位置结果
int iCurIndex;//运动小人当前参考轨迹点下标
GLfloat (*vert)[3] = 0, (*norm)[3] = 0;
int nVert=0;
GLuint texture1[1]={0};
GLuint texture2[1]={0};

CMyOpenGL::CMyOpenGL(void)
{
} 


CMyOpenGL::~CMyOpenGL(void)
{
}

/**
* \brief 绘制主控
*/
void changeGothicTrans(float trans[],double x,double y,double z,double a,double b,double c,double r,double _x,double _y,double _z)
{
	trans[0]=x;trans[1]=y;trans[2]=z;
	trans[3]=a;trans[4]=b;trans[5]=c;
	trans[6]=r;trans[7]=_x;trans[8]=_y;trans[9]=_z;
}

void hulanInit()
{
	hulanCnt=0;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=50;hulan[hulanCnt++].z=400;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=100;hulan[hulanCnt++].z=350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=200;hulan[hulanCnt++].z=350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=300;hulan[hulanCnt++].z=350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=400;hulan[hulanCnt++].z=350;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=300;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=0;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=-200;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=400;hulan[hulanCnt++].z=-200;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=300;hulan[hulanCnt++].z=-200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=250;hulan[hulanCnt++].z=-250;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=250;hulan[hulanCnt++].z=-350;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=250;hulan[hulanCnt++].z=-450;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=200;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=100;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=0;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-100;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-200;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-300;hulan[hulanCnt++].z=-450;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=-400;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=-300;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=-200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=0;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=50;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-300;hulan[hulanCnt++].z=100;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=150;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=350;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=450;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-200;hulan[hulanCnt++].z=450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-100;hulan[hulanCnt++].z=450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=0;hulan[hulanCnt++].z=450;

	/*********************************************************/
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-50;hulan[hulanCnt++].z=300;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=0;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=100;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=200;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=300;hulan[hulanCnt++].z=250;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=350;hulan[hulanCnt++].z=200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=350;hulan[hulanCnt++].z=100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=350;hulan[hulanCnt++].z=0;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=350;hulan[hulanCnt++].z=-50;


	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=300;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=200;hulan[hulanCnt++].z=-100;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=150;hulan[hulanCnt++].z=-150;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=150;hulan[hulanCnt++].z=-250;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=150;hulan[hulanCnt++].z=-300;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=100;hulan[hulanCnt++].z=-350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=0;hulan[hulanCnt++].z=-350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-100;hulan[hulanCnt++].z=-350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-200;hulan[hulanCnt++].z=-350;


	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-300;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-50;


	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-200;hulan[hulanCnt++].z=0;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-150;hulan[hulanCnt++].z=50;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-150;hulan[hulanCnt++].z=150;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-150;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-150;hulan[hulanCnt++].z=300;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-100;hulan[hulanCnt++].z=350;

}

void drawHulan()
{
	hulanInit();
	float gothicTrans_hulan[10];
	for(int i=0;i<hulanCnt;i++)
	{
		changeGothicTrans(gothicTrans_hulan,
			hulan[i].x,-20, hulan[i].z , //表示在世界矩阵的位置  
			0.18, 0.18, 0.18 ,      //表示xyz放大倍数  
			hulan[i].rotate, 0 , 1 , 0  //表示旋转  
			);
		m_loader_hulan.DrawModel(gothicTrans_hulan);
	}
}

/**
* \brief 初始化
*/
void CMyOpenGL::PostInit(void)
{
	
	m_loader_lupai.Init(3);//路牌
	m_loader_car.Init(2);//汽车
	m_loader_lupai4.Init(4);//路牌4
	m_loader_luren.Init(5);//路人
	m_loader_yuaubao.Init(11);//元宝
	m_loader_hulan.Init(10);//护栏
	m_loader_fangwu.Init(9);//房屋
	m_loader_fangwu2.Init(8);//房屋2
	car->init(Point_AABB(0,0,500,4,4,8,0,0,-1),0);//初始化汽车类
	car->setGothicTrans_car(
		0, 0 , 400,   
		0.00003 , 0.00003 , 0.00003 ,      
		0 , 0 , 0 , 0);

	if (!glIsList((GLuint)1))
	{
		glNewList(1,GL_COMPILE);
		drawHulan();//画护栏
		glEndList();
	}
	car->addWall(50,-20,450,50,380,350);
	car->addWall(50,-20,350,450,380,350);
	car->addWall(450,-20,350,450,380,-200);
	car->addWall(450,-20,-200,250,380,-200);
	car->addWall(250,-20,-200,250,380,-450);
	car->addWall(250,-20,-450,-350,380,-450);
	car->addWall(-350,-20,-450,-350,380,100);
	car->addWall(-350,-20,100,-250,380,100);
	car->addWall(-250,-20,100,-250,380,450);
	car->addWall(-250,-20,450,50,380,450);

	car->addWall(-50,-20,350,-50,380,250);
	car->addWall(-50,-20,250,350,380,250);
	car->addWall(350,-20,250,350,380,-100);
	car->addWall(350,-20,-100,150,380,-100);
	car->addWall(150,-20,-100,150,380,-350);
	car->addWall(150,-20,-350,-250,380,-350);
	car->addWall(-250,-20,-350,-250,380,0);
	car->addWall(-250,-20,0,-150,380,0);
	car->addWall(-150,-20,0,-150,380,350);
	car->addWall(-150,-20,350,-50,380,350);


	car->addYuanbao(0,300);
	car->addYuanbao(150,300);
	car->addYuanbao(400,300);
	car->addYuanbao(400,50);
	car->addYuanbao(300,-150);
	car->addYuanbao(-300,-250);
	car->addYuanbao(-200,50);
	car->addYuanbao(-200,400);
}





void CMyOpenGL::InDraw(void)
{
	gluLookAt(0,300,400,0,-1, 0,  0, 0, -1);
	glPushMatrix();
	scene.Render();
	glPopMatrix();


	glPushMatrix();
	float gothicTrans_fangwu[10] = { 
		100,-10, 200 , //表示在世界矩阵的位置  
		0.2, 0.2, 0.2 ,      //表示xyz放大倍数  
		180 , 0 , 1 , 0  //表示旋转  
	};
	m_loader_fangwu.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		150,-10, 400 , //表示在世界矩阵的位置  
		0.2, 0.2, 0.2 ,      //表示xyz放大倍数  
		90 , 0 , 1 , 0  //表示旋转  
		);
	m_loader_fangwu2.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		-300,-10, 250 , //表示在世界矩阵的位置  
		0.2, 0.2, 0.2 ,      //表示xyz放大倍数  
		-90 , 0 , 1 , 0  //表示旋转  
		);
	m_loader_fangwu.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		-150,-10, -250 , //表示在世界矩阵的位置  
		0.2, 0.2, 0.2 ,      //表示xyz放大倍数  
		0 , 0 , 1 , 0  //表示旋转  
		);
	m_loader_fangwu.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		100,-10, -250 , //表示在世界矩阵的位置  
		0.2, 0.2, 0.2 ,      //表示xyz放大倍数  
		90 , 0 , 1 , 0  //表示旋转  
		);


	m_loader_fangwu2.DrawModel(gothicTrans_fangwu);

	float gothicTransLupai4[10] = { 
		450,0 , -50, //表示在世界矩阵的位置  
		0.2, 0.1, 0.1 ,      //表示xyz放大倍数  
		0 , 0 , 1 , 0  //表示旋转  
	};
	m_loader_lupai4.DrawModel(gothicTransLupai4);

	float gothicTransLuren[10] = { 
		-100,0 , 200, //表示在世界矩阵的位置  
		0.2, 0.2, 0.2 ,      //表示xyz放大倍数  
		0 , 0 , 1 , 0  //表示旋转  
	};
	m_loader_luren.DrawModel(gothicTransLuren);



    glPopMatrix();

	glPushMatrix();
	car->car_box.DrawAABBBoundingBox();//画出车的包围盒
	m_loader_car.DrawModel(car->gothicTrans_car);

	for (int i=0;i<car->wall.size();i++)
	{
		car->wall[i].DrawAABBBoundingBox();
	}

	/*画元宝*/
	
	float gothicTrans_yuanbao[10];
	for (int i=0;i<car->yuanbao.size();i++)
	{
		if(car->yuanbaoFlag[i]!=1)
		{
			car->yuanbao[i].DrawAABBBoundingBox();
			changeGothicTrans(gothicTrans_yuanbao,
				(car->yuanbao[i].Xmax+car->yuanbao[i].Xmin)/2,0 ,(car->yuanbao[i].Zmax+car->yuanbao[i].Zmin)/2, 
				0.2,0.2, 0.2 ,      //表示xyz放大倍数  
				0 , 0 , 1 , 0  //表示旋转  
				);
			m_loader_yuaubao.DrawModel(gothicTrans_yuanbao);
		}
	}
	
	/********************************************/

	//drawHulan();//画护栏
	glCallList(1);
	glPopMatrix();
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
	car->update();
}

/**
 * \brief 绘制坐标轴
 */
void CMyOpenGL::DrawAxes()
{

}

/**
 * \brief 画一个球
 * \param radius 半径
 * \param lon 经向分割
 * \param lat 纬向分割
 */
void CMyOpenGL::DrawBall(GLfloat radius,int lon,int lat)
{

}

/**
 * \brief 计算法向量
 * \param v1 第一个点
 * \param v2 第二个点
 * \param v3 第三个点
 * \param normal 法向量
 */
void CMyOpenGL::CalculateNormal(GLfloat v1[],GLfloat v2[],GLfloat v3[],GLfloat normal[])
{

}

/**
 * \brief 法向量规范化
 * \param v 法向量
 */
void CMyOpenGL::Normalize(GLfloat *v)
{

}

bool CMyOpenGL::GetTexture()
{
	return true;
}

void CMyOpenGL::DrawBox(float size)
{

}

/**
* \brief 绘制小机器人
*/
void CMyOpenGL::DrawRobot()
{

}

/**
* \brief 绘制小飞船
*/
void CMyOpenGL::DrawUfo()
{

}
