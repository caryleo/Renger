#include "StdAfx.h"
#include "MyOpenGL.h"
#include <cmath>
#include <iostream>
#include "ModelLoader.h"
#define POINTNUM 200
#define CIRCLENUM 20
#define PI 3.1415926

CVector966 tracePointPos[POINTNUM];//�����켣��
CVector966 refCircle[CIRCLENUM];//�ο�Բ�켣��
CVector966 allPointPos[POINTNUM*CIRCLENUM];//����켣��λ�ý��
int iCurIndex;//�˶�С�˵�ǰ�ο��켣���±�
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
* \brief ��ʼ��
*/
void CMyOpenGL::PostInit(void)
{

}


/**
* \brief ��������
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
* \brief ��������
*/
void CMyOpenGL::Update()
{
	
}

/**
 * \brief ����������
 */
void CMyOpenGL::DrawAxes()
{
	
}

/**
 * \brief ��һ����
 * \param radius �뾶
 * \param lon ����ָ�
 * \param lat γ��ָ�
 */
void CMyOpenGL::DrawBall(GLfloat radius,int lon,int lat)
{
	
}

/**
 * \brief ���㷨����
 * \param v1 ��һ����
 * \param v2 �ڶ�����
 * \param v3 ��������
 * \param normal ������
 */
void CMyOpenGL::CalculateNormal(GLfloat v1[],GLfloat v2[],GLfloat v3[],GLfloat normal[])
{

}

/**
 * \brief �������淶��
 * \param v ������
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
* \brief ����С������
*/
void CMyOpenGL::DrawRobot()
{

}

/**
* \brief ����С�ɴ�
*/
void CMyOpenGL::DrawUfo()
{

}
