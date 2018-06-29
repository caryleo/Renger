#include "StdAfx.h"
#include "AABB.h"
#include <math.h>
//默认的构造函数
AABB::AABB(void)
{
}
//以AABB包围盒最小最大坐标点的My3DPoint结构体作为参数的构造函数
AABB::AABB(My3DPoint pointMin,My3DPoint pointMax)
{
	isWall=false;
	Xmin=pointMin.X;
	Ymin=pointMin.Y;
	Zmin=pointMin.Z;
	Xmax=pointMax.X;
	Ymax=pointMax.Y;
	Zmax=pointMax.Z;
}
//以AABB包围盒最小最大坐标点的六个坐标作为参数的构造函数
AABB::AABB(double m_Xmin,double m_Ymin,double m_Zmin,double m_Xmax,double m_Ymax,double m_Zmax)
{
	isWall=false;
	Xmin=m_Xmin;
	Xmax=m_Xmax;
	Ymin=m_Ymin;
	Ymax=m_Ymax;
	Zmin=m_Zmin;
	Zmax=m_Zmax;
}

void AABB::Translatef(double x,double y,double z)
{

	Xmin+=x;
	Xmax+=x;
	Ymin+=y;
	Ymax+=y;
	Zmin+=z;
	Zmax+=z;
}
//以Triangle三角形结构体作为参数的构造函数
AABB::AABB(Triangle a)
{
	isWall=false;
	//用三元运算符来求出最大最小值
	//求X的最小值
	Xmin=a.Verters[0].X<a.Verters[1].X?a.Verters[0].X:a.Verters[1].X;
	Xmin=Xmin<a.Verters[2].X?Xmin:a.Verters[3].X;
	//求Y的最小值
	Ymin=a.Verters[0].Y<a.Verters[1].Y?a.Verters[0].Y:a.Verters[1].Y;
	Ymin=Ymin<a.Verters[2].Y?Ymin:a.Verters[3].Y;
	//求Z的最小值
	Zmin=a.Verters[0].Z<a.Verters[1].Z?a.Verters[0].Z:a.Verters[1].Z;
	Zmin=Zmin<a.Verters[2].Z?Zmin:a.Verters[3].Z;
	//求X的最大值
	Xmax=a.Verters[0].X>a.Verters[1].X?a.Verters[0].X:a.Verters[1].X;
	Xmax=Xmax>a.Verters[2].X?Xmax:a.Verters[2].X;
	//求Y的最大值
	Ymax=a.Verters[0].Y>a.Verters[1].Y?a.Verters[0].Y:a.Verters[1].Y;
	Ymax=Ymax>a.Verters[2].Y?Ymax:a.Verters[2].Y;
	//求Z的最大值
	Zmax=a.Verters[0].Z>a.Verters[1].Z?a.Verters[0].Z:a.Verters[1].Z;
	Zmax=Zmax>a.Verters[2].Z?Zmax:a.Verters[2].Z;
}
AABB::AABB(Point_AABB a)
{
	isWall=false;
	double seta =fabs(asin(a.dirx/sqrt(a.dirx*a.dirx+a.dirz*a.dirz)));
	double dtz_=a.dtz*cos(seta)+a.dtx*sin(seta);
	double dtx_=a.dtx*cos(seta)+a.dtz*sin(seta);

	Xmin=min(a.x-dtx_,a.x+dtx_);
	Xmax=max(a.x-dtx_,a.x+dtx_);
	
	Zmin=min(a.z-dtz_,a.z+dtz_);
	Zmax=max(a.z-dtz_,a.z+dtz_);


	Ymin=a.y-a.dty;
	Ymax=a.y+a.dty;
}


/*-----IsOrNotInterection(AABB *a,AABB *b)---------
函数功能：判断两个AABB包围盒是否相交
函数参数：a为AABB对象指针,本身对象为b包围盒
--------------------------------------------------*/
//判断两个AABB包围盒是否相交
BOOL AABB::IsOrNotInterection(AABB a)
{
	if (a.Xmin>Xmax)//如果a包围盒最小的X坐标大于b包围盒的最大X坐标,a包围盒在X方向上在b的右边
	{
		return FALSE;
	}
	else if (a.Xmax<Xmin)//如果a包围盒最大的X坐标小于b包围盒的最小的X坐标，a包围盒在X方向上在b的左边
	{
		return FALSE;
	}
	else if (a.Ymin>Ymax)//如果a包围盒最小的Y坐标大于b包围盒的最大Y坐标，a包围盒在Y方向上在b的右边
	{
		return FALSE;
	}
	else if (a.Ymax<Ymin)//如果a包围盒最大的Y坐标小于b包围盒的最小的Y坐标,a包围盒在Y方向上在b的左边
	{
		return FALSE;
	}
	else if (a.Zmin>Zmax)//如果a包围盒最小的Z坐标大于b包围盒的最大Z坐标，a包围盒在Z方向上在b的上方
	{
		return FALSE;
	}
	else if (a.Zmax<Zmin)//如果a包围盒最大的Z坐标小于b包围盒的最小的Z坐标,a包围盒在Z方向上在b的下方
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}
/*-----PointIsOrNotInAABBBoundingBox(My3DPoint pt,AABB *box)判断点是否落在AABB包围盒之内------
函数功能：判断三维点是否落在AABB包围盒之内
函数参数：pt为My3DPoint结构体，box为AABB包围盒对象指针
---------------------------------------------------------------------------------------------*/

BOOL AABB::PointIsOrNotInAABBBoundingBox(My3DPoint pt)
{
	return (pt.X>=Xmin)&&(pt.X<=Xmax)&&
		(pt.Y>=Ymin)&&(pt.Y<=Ymax)&&
		(pt.Z>=Zmin)&&(pt.Z<=Zmax);
}

/*-----GetAABBBoxCeter()-------------------------------------------
函数功能：得到此AABB包围盒对象的质心，中心，返回一个My3DPoint结构体
-------------------------------------------------------------------*/
My3DPoint AABB::GetAABBBoxCeter()
{
	My3DPoint m_point;
	m_point.X=(Xmin+Xmax)*0.5;
	m_point.Y=(Ymin+Ymax)*0.5;
	m_point.Z=(Zmin+Zmax)*0.5;
	return m_point;
}

/*-----IsOrNotEmpty()---------------------------------------------
函数功能：判断AABB包围盒是否为空，为空返回TRUE，不为空返回FALSE
------------------------------------------------------------------*/
BOOL AABB::IsOrNotEmpty()
{
	return(Xmin>Xmax)||(Ymin>Ymax)||(Zmin>Zmax);
}
/*-----GetXLength()---------
函数功能：得到X方向上的长度
--------------------------*/
double AABB::GetXLength()
{
	return Xmax-Xmin;
}
/*-----GetYLength()---------
函数功能：得到Y方向上的长度
--------------------------*/
double AABB::GetYLength()
{
	return Ymax-Ymin;
}
/*-----GetZLength()---------
函数功能：得到Z方向上的长度
--------------------------*/
double AABB::GetZLength()
{
	return Zmax-Zmin;
}
/*-----GetVolume()-------------
函数功能：得到AABB包围盒的体积
------------------------------*/
double AABB::GetVolume()
{
	return (Xmax-Xmin)*(Ymax-Ymin)*(Zmax-Zmin);
}

/*-----DrawAABBBoundingBox()-------------------
函数功能：绘制AABB包围盒
-----------------------------------------------*/
void AABB::DrawAABBBoundingBox()
{
	glLineWidth(2);
	//第一根线
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmin);
	glVertex3f(Xmax,Ymin,Zmin);
	glEnd();
	//第二根线
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmin);
	glVertex3f(Xmin,Ymin,Zmax);
	glEnd();
	//第三根线
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmin);
	glVertex3f(Xmin,Ymax,Zmin);
	glEnd();
	//第四根线
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmax);
	glVertex3f(Xmax,Ymin,Zmax);
	glEnd();
	//第五根线
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymin,Zmin);
	glVertex3f(Xmax,Ymin,Zmax);
	glEnd();
	//第六根线
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymin,Zmin);
	glVertex3f(Xmax,Ymax,Zmin);
	glEnd();
	//第七根线
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymax,Zmin);
	glVertex3f(Xmin,Ymax,Zmin);
	glEnd();
	//第八根线
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymax,Zmin);
	glVertex3f(Xmin,Ymax,Zmax);
	glEnd();
	//第九根线
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymax,Zmin);
	glVertex3f(Xmax,Ymax,Zmax);
	glEnd();
	//第十根线
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmax);
	glVertex3f(Xmin,Ymax,Zmax);
	glEnd();
	//第十一根线
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymin,Zmax);
	glVertex3f(Xmax,Ymax,Zmax);
	glEnd();
	//第十二根线
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymax,Zmax);
	glVertex3f(Xmax,Ymax,Zmax);
	glEnd();

}
AABB::~AABB(void)
{
}

void AABB::wallInit()//如果是墙壁，调用这个初始化墙壁的值
{
	My3DPoint center=this->GetAABBBoxCeter();
	dirx=Xmax-Xmin;
	diry=Ymax-Ymin;
	dirz=Zmax-Zmin;
	isWall=true;
}