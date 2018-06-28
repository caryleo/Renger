#pragma once
#include "aabb.h"
#include <vector>
using namespace std;

class CAR
{
public:
	Point_AABB car_point;//����ȷ��aabb��Χ�еĻ���
	float gothicTrans_car[10];//��¼����ģ�͵����ʱ��ĸ������

	AABB car_box;//��Χ��
	double speed;//�ٶ�

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

	void init(Point_AABB tmp,double _speed);//��ʼ��
	void update();//���������˶�״̬
	void turnLeft(double deg);//��ת
	void turnRight(double deg);//��ת
	void speedUp();//����
	void speedDown();//����
	void speedDownNatural();//��������Ȼ����
	void addWall(double m_Xmin,double m_Ymin,double m_Zmin,double m_Xmax,double m_Ymax,double m_Zmax);//���ǽ��
	void addYuanbao(double x,double z);//���Ԫ��
};