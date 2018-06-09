#include "StdAfx.h"
#include "MyOpenGL.h"
#include <cmath>
#include <iostream>
#include "ModelLoader.h"
#define POINTNUM 200
#define CIRCLENUM 20
#define PI 3.1415926

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

}


/**
* \brief 绘制主控
*/
void CMyOpenGL::InDraw(void)
{
	scene.Render();


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
