#pragma once
typedef struct My3DPoint//�����Լ�����ά��ṹ��
{
	double X;//X����
	double Y;//Y����
	double Z;//Z����
	My3DPoint(){};
	My3DPoint(double x_,double y_,double z_):X(x_),Y(y_),Z(z_){};
};
typedef struct Triangle//�����εĽṹ��
{
	My3DPoint Verters[3];//�����ε���������
	BOOL IsShow;//��ά���Ƿ���Ҫ��ʾ
	My3DPoint TriangleFaceNormal;//������Ƭ�ķ�����
};
typedef struct Point_AABB//ͨ������ģ�͵���Ϣ�������Χ��
{
	double x,y,z;//����������
	double dtx,dty,dtz;//��x,y,z�����ϵ�����
	double dirx,diry,dirz;//��������Ĭ��ʱ�������еķ���
	Point_AABB(){};
	Point_AABB(double _x,double _y,double _z,double _dtx,double _dty,double _dtz,double _dirx,double _diry,double _dirz):x(_x),y(_y),z(_z),dtx(_dtx),dty(_dty),dtz(_dtz),dirx(_dirx),diry(_diry),dirz(_dirz){};
};
class AABB
{
public:
	bool isWall;
	AABB(void);//Ĭ�ϵ��޲ι��캯��
	~AABB(void);//Ĭ�ϵ���������
AABB(My3DPoint pointMin,My3DPoint pointMax);//�Զ�����вι��캯��������Ϊ����My3DPoint�ṹ��AABB��Χ����С��������
AABB(double m_Xmin,double m_Xmax,double m_Ymin,double m_Ymax,double m_Zmin,double m_Zmax);//�Զ�����вεĹ��캯��������ΪAABB��Χ����С���������
AABB(Triangle a);//����һ�������νṹ��
AABB(Point_AABB a);
BOOL IsOrNotInterection(AABB a);//�ж�����AABB��Χ���Ƿ��ཻ������ཻ����TRUE��������ཻ������FALSE
BOOL PointIsOrNotInAABBBoundingBox(My3DPoint pt);//�ж�һ��ά���Ƿ�����ĳ��AABB��Χ����
My3DPoint GetAABBBoxCeter();//��AABB��Χ�е����Ļ�������
BOOL IsOrNotEmpty();//�ж�AABB��Χ���Ƿ�Ϊ��
double GetXLength();//�õ�X�����ϵĳ���
double GetYLength();//�õ�Y�����ϵĳ���
double GetZLength();//�õ�Z�����ϵĳ���
double GetVolume();//�õ�AABB��Χ�е����
void DrawAABBBoundingBox();//����AABB��Χ��
void Translatef(double x,double y,double z);//�ı��Χ�е�λ��


double dirx,diry,dirz;//�����ǽ�ڵĻ���ǽ�ڵİڷŷ���
void wallInit();//�����ǽ�ڣ����������ʼ��ǽ�ڵ�ֵ,

	double Xmin;//X����Сֵ
	double Xmax;//X�����ֵ
	double Ymin;//Y����Сֵ
	double Ymax;//Y�����ֵ
	double Zmin;//Z����Сֵ
	double Zmax;//Z�����ֵ
};
