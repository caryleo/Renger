#include "StdAfx.h"
#include <math.h>
#include "car.h"
#include "aabb.h"
#include "windows.h"
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")
#define PI 3.1415926
const double eps=1e-6;
void CAR::turn(double deg)
{
	deg=deg/180*PI;//ת����
	double tmpx=car_point.dirx*cos(deg)-car_point.dirz*sin(deg);
	double tmpz=car_point.dirx*sin(deg)+car_point.dirz*cos(deg);
	car_point.dirx=tmpx;
	car_point.dirz=tmpz;

	double seta=acos(-car_point.dirz/sqrt(car_point.dirx*car_point.dirx+car_point.dirz*car_point.dirz));//����ģ��Ӧ��ƫת�ĽǶȣ�������Ϊģ��Ĭ�ϳ���-z
	if(car_point.dirx>0)
	{
		gothicTrans_car[6]=seta/PI*180;
		gothicTrans_car[7]=0;
		gothicTrans_car[8]=-1;
		gothicTrans_car[9]=0;
	}
	else 
	{
		gothicTrans_car[6]=seta/PI*180;
		gothicTrans_car[7]=0;
		gothicTrans_car[8]=1;
		gothicTrans_car[9]=0;
	}
}

void CAR::turnRight(double deg)//��ת,�Ƕ�
{
	if(speed<0)
		turn(-deg);
	else turn(deg);
}
void CAR::turnLeft(double deg)//��ת
{
	if(speed<0)
		turn(deg);
	else turn(-deg);
}
void CAR::update()//���������˶�״̬
{
	//�յ��߼��
	if(car_box.IsOrNotInterection(endLine))
	{
		Time = time(NULL);
	}
	//Ԫ����ײ���
	for(int i=0;i<yuanbao.size();i++)
	{
		if(yuanbaoFlag[i]) continue;//��ֹ����ж���ײ��
		if(car_box.IsOrNotInterection(yuanbao[i]))
		{
			score+=10;
			yuanbaoFlag[i]=1;
		}
	}

	int tmpIndex=-1;
	for(int i = 0; i < wall.size();i++)//ɨ��һ������ǽ
	{
		if(wall[i].IsOrNotInterection(car_box))
		{
			tmpIndex=i;
			break;
		}
	}
	if(tmpIndex!=-1)
	{
		
		double a=wall[tmpIndex].dirx*car_point.dirx+wall[tmpIndex].dirz*car_point.dirz;
		double b=wall[tmpIndex].dirx*wall[tmpIndex].dirx+wall[tmpIndex].dirz*wall[tmpIndex].dirz+car_point.dirx*car_point.dirx+car_point.dirz*car_point.dirz;
		double seta=acos(a/sqrt(b));
		seta=seta/PI*180;
		double flagSeta=fabs(seta-90);//������90�ȼн�
		if(flagSeta<60)//���մ�ֱ��ײ����,��ʱ��û�и��ķ���
		{
			//��ԭһ��λ��
			gothicTrans_car[0]-=car_point.dirx*2*speed;
			gothicTrans_car[1]-=car_point.diry*2*speed;
			gothicTrans_car[2]-=car_point.dirz*2*speed;

			car_point.x=gothicTrans_car[0];
			car_point.y=gothicTrans_car[1];
			car_point.z=gothicTrans_car[2];
			car_box=AABB(car_point);//����aabb��Χ�е�״̬
			speed=0;
			return;
		}
		else 
		{
			//���Ȼ�ԭһ��λ��
			gothicTrans_car[0]-=car_point.dirx*2*speed;
			gothicTrans_car[1]-=car_point.diry*2*speed;
			gothicTrans_car[2]-=car_point.dirz*2*speed;

			car_point.x=gothicTrans_car[0];
			car_point.y=gothicTrans_car[1];
			car_point.z=gothicTrans_car[2];

			//���㷽��ͶӰ
			double tmpx=(car_point.dirx*wall[tmpIndex].dirx+car_point.dirz*wall[tmpIndex].dirz)/(wall[tmpIndex].dirx*wall[tmpIndex].dirx+wall[tmpIndex].dirz*wall[tmpIndex].dirz)*wall[tmpIndex].dirx;
			double tmpz=(car_point.dirx*wall[tmpIndex].dirx+car_point.dirz*wall[tmpIndex].dirz)/(wall[tmpIndex].dirx*wall[tmpIndex].dirx+wall[tmpIndex].dirz*wall[tmpIndex].dirz)*wall[tmpIndex].dirz;

			
			car_point.dirx=tmpx;
			car_point.dirz=tmpz;
			//����ģ�ͷ���
			double seta=acos(-car_point.dirz/sqrt(car_point.dirx*car_point.dirx+car_point.dirz*car_point.dirz));//����ģ��Ӧ��ƫת�ĽǶȣ�������Ϊģ��Ĭ�ϳ���-z
			if(car_point.dirx>0)
			{
				gothicTrans_car[6]=seta/PI*180;
				gothicTrans_car[7]=0;
				gothicTrans_car[8]=-1;
				gothicTrans_car[9]=0;
			}
			else 
			{
				gothicTrans_car[6]=seta/PI*180;
				gothicTrans_car[7]=0;
				gothicTrans_car[8]=1;
				gothicTrans_car[9]=0;
			}
			speed=speed*0.5;//�����ٶȸ�Ϊ����һ��
			car_box=AABB(car_point);//����aabb��Χ�е�״̬
			return;
		}

	}

	//����λ��
	gothicTrans_car[0]+=car_point.dirx*speed;
	gothicTrans_car[1]+=car_point.diry*speed;
	gothicTrans_car[2]+=car_point.dirz*speed;

	car_point.x=gothicTrans_car[0];
	car_point.y=gothicTrans_car[1];
	car_point.z=gothicTrans_car[2];

	car_box=AABB(car_point);//����aabb��Χ�е�״̬
}
void CAR::init(Point_AABB tmp,double _speed)
{	
	car_point=tmp;
	speed=_speed;
	car_box=AABB(car_point);
}
void CAR::addWall(double m_Xmin,double m_Ymin,double m_Zmin,double m_Xmax,double m_Ymax,double m_Zmax)
{

	AABB tmp=AABB(min(m_Xmin,m_Xmax),min(m_Ymin,m_Ymax),min(m_Zmin,m_Zmax),max(m_Xmin,m_Xmax),max(m_Ymin,m_Ymax),max(m_Zmin,m_Zmax));
	tmp.wallInit();
	wall.push_back(tmp);
}
void CAR::speedUp()//���٣�����Ϊ���ټӼ��ٶ�
{
	PlaySound(TEXT("Data/car.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP|SND_NOSTOP );
	if(fabs(speed-5)>eps)
	{
		speed+=0.5;
	}
}
void CAR::speedDown()//����
{
	if(fabs(speed+3)>eps)
	{
		speed-=0.5;
	}
}
void CAR::speedDownNatural()
{
	if(fabs(speed-0)<eps)
		return ;
	else if(speed<0)
	{
		speed+=2;
		if(speed>0)
			speed=0;
	}
	else if(speed>0)
	{
		speed-=2;
		if(speed<0)
			speed=0;
	}
}
void CAR::addYuanbao(double x,double z)//���Ԫ��
{
	AABB tmp=AABB(Point_AABB(x,2,z,2,2,2,0,0,-1));
	yuanbao.push_back(tmp);
}