#pragma once
typedef struct My3DPoint//定义自己的三维点结构体
{
	double X;//X坐标
	double Y;//Y坐标
	double Z;//Z坐标
	My3DPoint(){};
	My3DPoint(double x_,double y_,double z_):X(x_),Y(y_),Z(z_){};
};
typedef struct Triangle//三角形的结构体
{
	My3DPoint Verters[3];//三角形的三个顶点
	BOOL IsShow;//三维面是否需要显示
	My3DPoint TriangleFaceNormal;//三角面片的法向量
};
class AABB
{
public:
	AABB(void);//默认的无参构造函数
	~AABB(void);//默认的析构函数
AABB(My3DPoint pointMin,My3DPoint pointMax);//自定义的有参构造函数，参数为两个My3DPoint结构的AABB包围盒最小最大坐标点
AABB(double m_Xmin,double m_Xmax,double m_Ymin,double m_Ymax,double m_Zmin,double m_Zmax);//自定义的有参的构造函数，参数为AABB包围盒最小最大点的坐标
AABB(Triangle a);//传进一个三角形结构体
BOOL IsOrNotInterection(AABB a);//判断两个AABB包围盒是否相交，如果相交返回TRUE，如果不相交，返回FALSE
BOOL PointIsOrNotInAABBBoundingBox(My3DPoint pt);//判断一三维点是否落在某个AABB包围盒内
My3DPoint GetAABBBoxCeter();//求AABB包围盒的中心或者质心
BOOL IsOrNotEmpty();//判断AABB包围盒是否为空
double GetXLength();//得到X方向上的长度
double GetYLength();//得到Y方向上的长度
double GetZLength();//得到Z方向上的长度
double GetVolume();//得到AABB包围盒的体积
void DrawAABBBoundingBox();//绘制AABB包围盒
void Translatef(double x,double y,double z);//改变包围盒的位置
private:
	double Xmin;//X的最小值
	double Xmax;//X的最大值
	double Ymin;//Y的最小值
	double Ymax;//Y的最大值
	double Zmin;//Z的最小值
	double Zmax;//Z的最大值
};
