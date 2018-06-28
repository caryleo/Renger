#pragma once
#include "aabb.h"
#include <vector>
using namespace std;

class CAR
{
public:
	Point_AABB car_point;//用来确定aabb包围盒的画法
	float gothicTrans_car[10];//记录汽车模型导入的时候的各项参数

	AABB car_box;//包围盒
	double speed;//速度

	vector<AABB>wall;
	vector<AABB>yuanbao;
	int yuanbaoFlag[100];

	CAR()
	{
		memset(yuanbaoFlag,0,sizeof(yuanbaoFlag));
	};
	void setGothicTrans_car(double x,double y,double z,double fx,double fy,double fz,double a,double b,double c,double d)
	{
		gothicTrans_car[0]=x;gothicTrans_car[1]=y;gothicTrans_car[2]=z;
		gothicTrans_car[3]=fx;gothicTrans_car[4]=fy;gothicTrans_car[5]=fz;
		gothicTrans_car[6]=a;gothicTrans_car[7]=b;gothicTrans_car[8]=c;gothicTrans_car[9]=d;
	}

	void init(Point_AABB tmp,double _speed);//初始化
	void update();//更新汽车运动状态
	void turnLeft(double deg);//左转
	void turnRight(double deg);//右转
	void speedUp();//加速
	void speedDown();//减速
	void speedDownNatural();//汽车的自然减速
	void addWall(double m_Xmin,double m_Ymin,double m_Zmin,double m_Xmax,double m_Ymax,double m_Zmax);//添加墙壁
	void addYuanbao(double x,double z);//添加元宝
};