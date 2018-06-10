# AABB包围盒接口文档
---
## 自定义结构体
自定义点
```cpp
typedef struct My3DPoint//定义自己的三维点结构体
{
	double X;//X坐标
	double Y;//Y坐标
	double Z;//Z坐标
	My3DPoint(){};
	My3DPoint(double x_,double y_,double z_):X(x_),Y(y_),Z(z_){};
};
```
自定义三角形
```cpp
typedef struct Triangle//三角形的结构体
{
	My3DPoint Verters[3];//三角形的三个顶点
	BOOL IsShow;//三维面是否需要显示
	My3DPoint TriangleFaceNormal;//三角面片的法向量
};
```
## 接口
- 有参构造函数，参数为两个My3DPoint结构的AABB包围盒最小最大坐标点
```cpp
AABB(My3DPoint pointMin,My3DPoint pointMax);
```
- 有参的构造函数，参数为AABB包围盒最小最大点的坐标
```cpp
AABB(double m_Xmin,double m_Xmax,double m_Ymin,double m_Ymax,double m_Zmin,double m_Zmax);
```
- 判断两个AABB包围盒是否相交，如果相交返回TRUE，如果不相交，返回FALSE
```cpp
BOOL IsOrNotInterection(AABB a);
```
- 判断一三维点是否落在某个AABB包围盒内
```cpp
BOOL PointIsOrNotInAABBBoundingBox(My3DPoint pt)
```
- 求AABB包围盒的中心或者质心
```cpp
My3DPoint GetAABBBoxCeter();
```
- 判断AABB包围盒是否为空
```cpp
BOOL IsOrNotEmpty();
```
- 得到X方向上的长度
```cpp
double GetXLength();
```
- 得到Y方向上的长度
```cpp
double GetYLength();
```
- 得到Z方向上的长度
```cpp
double GetZLength();
```
- 得到AABB包围盒的体积
```cpp
double GetVolume();
```
- 绘制AABB包围盒
```cpp
void DrawAABBBoundingBox();
```
- 改变包围盒的位置,移动给定的向量
```cpp
void Translatef(double x,double y,double z);
```