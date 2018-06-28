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
* \brief 初始化
*/
void CMyOpenGL::PostInit(void)
{
	m_loader_lupai.Init(3);
	m_loader_car.Init(2);
	car->init(Point_AABB(0,0,-50,15,5,25,0,0,-1),0);//初始化汽车类
	car->setGothicTrans_car(
		0, 0 , -50 ,   
		0.0001 , 0.0001 , 0.0001 ,      
		0 , 0 , 0 , 0);
	car->addWall(0,-20,400,0,380,100);

}


/**
* \brief 绘制主控
*/
void CMyOpenGL::InDraw(void)
{
	glPushMatrix();
	scene.Render();


	glPopMatrix();
	glPushMatrix();
	float gothicTrans[10] = { 
		50,0 , -50 , //表示在世界矩阵的位置  
		0.1, 0.1, 0.1 ,      //表示xyz放大倍数  
		180 , 0 , 1 , 0  //表示旋转  
	};
	m_loader_lupai.DrawModel(gothicTrans);
    glPopMatrix();
	glPushMatrix();
	car->car_box.DrawAABBBoundingBox();
	m_loader_car.DrawModel(car->gothicTrans_car);
	for (int i=0;i<car->wall.size();i++)
	{
		car->wall[i].DrawAABBBoundingBox();
	}
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
