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
	
	m_loader_lupai.Init(3);//·��
	m_loader_car.Init(2);//����
	m_loader_lupai4.Init(4);//·��4
	m_loader_luren.Init(5);//·��
	m_loader_yuaubao.Init(11);//Ԫ��
	m_loader_hulan.Init(10);//����
	m_loader_fangwu.Init(9);//����
	m_loader_fangwu2.Init(8);//����2
	pCar->init(Point_AABB(0,0,500,4,4,8,0,0,-1),0);//��ʼ��������
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
}


/**
* \brief ��������
*/
void CMyOpenGL::changeGothicTrans(float trans[],double x,double y,double z,double a,double b,double c,double r,double _x,double _y,double _z)
{
	trans[0]=x;trans[1]=y;trans[2]=z;
	trans[3]=a;trans[4]=b;trans[5]=c;
	trans[6]=r;trans[7]=_x;trans[8]=_y;trans[9]=_z;
}
void CMyOpenGL::hulanInit()
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
void CMyOpenGL::drawHulan()
{
	hulanInit();
	float gothicTrans_hulan[10];
	for(int i=0;i<hulanCnt;i++)
	{
		changeGothicTrans(gothicTrans_hulan,
			hulan[i].x,-20, hulan[i].z , //��ʾ����������λ��  
			0.18, 0.18, 0.18 ,      //��ʾxyz�Ŵ���  
			hulan[i].rotate, 0 , 1 , 0  //��ʾ��ת  
			);
		m_loader_hulan.DrawModel(gothicTrans_hulan);
	}
}

void CMyOpenGL::InDraw(void)
{
	glPushMatrix();
	scene.Render();
	glPopMatrix();
	DrawAxes(1000);

	glPushMatrix();
	float gothicTrans_fangwu[10] = { 
		100,-10, 200 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		180 , 0 , 1 , 0  //��ʾ��ת  
	};
	m_loader_fangwu.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		150,-10, 400 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		90 , 0 , 1 , 0  //��ʾ��ת  
		);
	m_loader_fangwu2.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		-300,-10, 250 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		-90 , 0 , 1 , 0  //��ʾ��ת  
		);
	m_loader_fangwu.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		-150,-10, -250 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		0 , 0 , 1 , 0  //��ʾ��ת  
		);
	m_loader_fangwu.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		100,-10, -250 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		90 , 0 , 1 , 0  //��ʾ��ת  
		);

	m_loader_fangwu2.DrawModel(gothicTrans_fangwu);

	float gothicTransLupai4[10] = { 
		450,0 , -50, //��ʾ����������λ��  
		0.2, 0.1, 0.1 ,      //��ʾxyz�Ŵ���  
		0 , 0 , 1 , 0  //��ʾ��ת  
	};
	m_loader_lupai4.DrawModel(gothicTransLupai4);

	float gothicTransLuren[10] = { 
		-100,0 , 200, //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		0 , 0 , 1 , 0  //��ʾ��ת  
	};
	m_loader_luren.DrawModel(gothicTransLuren);

    glPopMatrix();

	glPushMatrix();
	pCar->car_box.DrawAABBBoundingBox();//�������İ�Χ��
	glPushMatrix();
	CString tmp;
	tmp.Format("��ĳ�");
	CVector966 tmpPos(float(pCar->car_point.x), float(pCar->car_point.y), float(pCar->car_point.z));
	CString pos;
	pos.Format("��ǰ��λ�ã���%.2lf��%.2lf��%.2lf��", pCar->car_point.x, pCar->car_point.y, pCar->car_point.z);
	pFont->Font2D(pos, CVector966(-0.9, 0.8, 0), 24, RGB(255, 255, 255), 0|8 , 0);
	//CVector966 tmpPos(0, 0, 0);
	pFont->Font2D(tmp, tmpPos, 50, RGB(255,255,255), DT_CENTER | DT_VCENTER, 1);
	m_loader_car.DrawModel(pCar->gothicTrans_car);
	glPopMatrix();

	for (int i=0;i<pCar->wall.size();i++)
	{
		pCar->wall[i].DrawAABBBoundingBox();
	}

	/*��Ԫ��*/
	
	float gothicTrans_yuanbao[10];
	for (int i=0;i<pCar->yuanbao.size();i++)
	{
		if(pCar->yuanbaoFlag[i]!=1)
		{
			pCar->yuanbao[i].DrawAABBBoundingBox();
			changeGothicTrans(gothicTrans_yuanbao,
				(pCar->yuanbao[i].Xmax+pCar->yuanbao[i].Xmin)/2,0 ,(pCar->yuanbao[i].Zmax+pCar->yuanbao[i].Zmin)/2, 
				0.2,0.2, 0.2 ,      //��ʾxyz�Ŵ���  
				0 , 0 , 1 , 0  //��ʾ��ת  
				);
			m_loader_yuaubao.DrawModel(gothicTrans_yuanbao);
		}
	}
	
	/********************************************/

	//drawHulan();//������
	CString str;
	str.Format("fps: %.2f ֡ÿ��", fps);
	pFont->Font2D(str, CVector966(-0.9f, 0.9f, 0), 24, RGB(255, 255, 255), 0|8 , 0);
	CString sp;
	sp.Format("��ǰ�ٶȣ�%.2lf m/s", pCar->speed);
	pFont->Font2D(sp, CVector966(-0.9f, 0.7f, 0), 24, RGB(255, 255, 255), 0|8 , 0);
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
	pCar->update();
}

/**
 * \brief ����������
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

