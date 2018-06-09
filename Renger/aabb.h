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
class AABB
{
public:
	AABB(void);//Ĭ�ϵ��޲ι��캯��
	~AABB(void);//Ĭ�ϵ���������
AABB(My3DPoint pointMin,My3DPoint pointMax);//�Զ�����вι��캯��������Ϊ����My3DPoint�ṹ��AABB��Χ����С��������
AABB(double m_Xmin,double m_Xmax,double m_Ymin,double m_Ymax,double m_Zmin,double m_Zmax);//�Զ�����вεĹ��캯��������ΪAABB��Χ����С���������
AABB(Triangle a);//����һ�������νṹ��
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
private:
	double Xmin;//X����Сֵ
	double Xmax;//X�����ֵ
	double Ymin;//Y����Сֵ
	double Ymax;//Y�����ֵ
	double Zmin;//Z����Сֵ
	double Zmax;//Z�����ֵ
};
