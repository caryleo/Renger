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
	m_loader_lupai.Init(3);
	m_loader_car.Init(2);
	car->init(Point_AABB(0,0,-50,15,5,25,0,0,-1),0);//��ʼ��������
	car->setGothicTrans_car(
		0, 0 , -50 ,   
		0.0001 , 0.0001 , 0.0001 ,      
		0 , 0 , 0 , 0);
	car->addWall(0,-20,400,0,380,100);

}


/**
* \brief ��������
*/
void CMyOpenGL::InDraw(void)
{
	glPushMatrix();
	scene.Render();


	glPopMatrix();
	glPushMatrix();
	float gothicTrans[10] = { 
		50,0 , -50 , //��ʾ����������λ��  
		0.1, 0.1, 0.1 ,      //��ʾxyz�Ŵ���  
		180 , 0 , 1 , 0  //��ʾ��ת  
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
* \brief ��������
*/
void CMyOpenGL::Update()
{
	car->update();
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
