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
	deg=deg/180*PI;//转弧度
	double tmpx=car_point.dirx*cos(deg)-car_point.dirz*sin(deg);
	double tmpz=car_point.dirx*sin(deg)+car_point.dirz*cos(deg);
	car_point.dirx=tmpx;
	car_point.dirz=tmpz;

	double seta=acos(-car_point.dirz/sqrt(car_point.dirx*car_point.dirx+car_point.dirz*car_point.dirz));//计算模型应该偏转的角度，这里认为模型默认朝向-z
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

void CAR::turnRight(double deg)//左转,角度
{
	if(speed<0)
		turn(-deg);
	else turn(deg);
}
void CAR::turnLeft(double deg)//右转
{
	if(speed<0)
		turn(deg);
	else turn(-deg);
}
void CAR::update()//更新汽车运动状态
{
	//终点线检测
	if(car_box.IsOrNotInterection(endLine))
	{
		Time = time(NULL);
	}
	//元宝碰撞检测
	for(int i=0;i<yuanbao.size();i++)
	{
		if(yuanbaoFlag[i]) continue;//防止多次判断碰撞盒
		if(car_box.IsOrNotInterection(yuanbao[i]))
		{
			score+=10;
			yuanbaoFlag[i]=1;
		}
	}

	int tmpIndex=-1;
	for(int i = 0; i < wall.size();i++)//扫描一遍所有墙
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
		double flagSeta=fabs(seta-90);//计算与90度夹角
		if(flagSeta<60)//按照垂直碰撞计算,此时并没有更改方向
		{
			//还原一步位置
			gothicTrans_car[0]-=car_point.dirx*2*speed;
			gothicTrans_car[1]-=car_point.diry*2*speed;
			gothicTrans_car[2]-=car_point.dirz*2*speed;

			car_point.x=gothicTrans_car[0];
			car_point.y=gothicTrans_car[1];
			car_point.z=gothicTrans_car[2];
			car_box=AABB(car_point);//更新aabb包围盒的状态
			speed=0;
			return;
		}
		else 
		{
			//首先还原一步位置
			gothicTrans_car[0]-=car_point.dirx*2*speed;
			gothicTrans_car[1]-=car_point.diry*2*speed;
			gothicTrans_car[2]-=car_point.dirz*2*speed;

			car_point.x=gothicTrans_car[0];
			car_point.y=gothicTrans_car[1];
			car_point.z=gothicTrans_car[2];

			//计算方向投影
			double tmpx=(car_point.dirx*wall[tmpIndex].dirx+car_point.dirz*wall[tmpIndex].dirz)/(wall[tmpIndex].dirx*wall[tmpIndex].dirx+wall[tmpIndex].dirz*wall[tmpIndex].dirz)*wall[tmpIndex].dirx;
			double tmpz=(car_point.dirx*wall[tmpIndex].dirx+car_point.dirz*wall[tmpIndex].dirz)/(wall[tmpIndex].dirx*wall[tmpIndex].dirx+wall[tmpIndex].dirz*wall[tmpIndex].dirz)*wall[tmpIndex].dirz;

			
			car_point.dirx=tmpx;
			car_point.dirz=tmpz;
			//调整模型方向
			double seta=acos(-car_point.dirz/sqrt(car_point.dirx*car_point.dirx+car_point.dirz*car_point.dirz));//计算模型应该偏转的角度，这里认为模型默认朝向-z
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
			speed=speed*0.5;//这里速度改为减少一半
			car_box=AABB(car_point);//更新aabb包围盒的状态
			return;
		}

	}

	//更新位置
	gothicTrans_car[0]+=car_point.dirx*speed;
	gothicTrans_car[1]+=car_point.diry*speed;
	gothicTrans_car[2]+=car_point.dirz*speed;

	car_point.x=gothicTrans_car[0];
	car_point.y=gothicTrans_car[1];
	car_point.z=gothicTrans_car[2];

	car_box=AABB(car_point);//更新aabb包围盒的状态
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
void CAR::speedUp()//加速，这里为匀速加减速度
{
	PlaySound(TEXT("Data/car.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP|SND_NOSTOP );
	if(fabs(speed-5)>eps)
	{
		speed+=0.5;
	}
}
void CAR::speedDown()//减速
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
void CAR::addYuanbao(double x,double z)//添加元宝
{
	AABB tmp=AABB(Point_AABB(x,2,z,2,2,2,0,0,-1));
	yuanbao.push_back(tmp);
}