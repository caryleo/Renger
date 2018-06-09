#include "StdAfx.h"
#include "AABB.h"

//Ĭ�ϵĹ��캯��
AABB::AABB(void)
{
}
//��AABB��Χ����С���������My3DPoint�ṹ����Ϊ�����Ĺ��캯��
AABB::AABB(My3DPoint pointMin,My3DPoint pointMax)
{
	Xmin=pointMin.X;
	Ymin=pointMin.Y;
	Zmin=pointMin.Z;
	Xmax=pointMax.X;
	Ymax=pointMax.Y;
	Zmax=pointMax.Z;
}
//��AABB��Χ����С�������������������Ϊ�����Ĺ��캯��
AABB::AABB(double m_Xmin,double m_Ymin,double m_Zmin,double m_Xmax,double m_Ymax,double m_Zmax)
{
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
//��Triangle�����νṹ����Ϊ�����Ĺ��캯��
AABB::AABB(Triangle a)
{
	//����Ԫ���������������Сֵ
	//��X����Сֵ
	Xmin=a.Verters[0].X<a.Verters[1].X?a.Verters[0].X:a.Verters[1].X;
	Xmin=Xmin<a.Verters[2].X?Xmin:a.Verters[3].X;
	//��Y����Сֵ
	Ymin=a.Verters[0].Y<a.Verters[1].Y?a.Verters[0].Y:a.Verters[1].Y;
	Ymin=Ymin<a.Verters[2].Y?Ymin:a.Verters[3].Y;
	//��Z����Сֵ
	Zmin=a.Verters[0].Z<a.Verters[1].Z?a.Verters[0].Z:a.Verters[1].Z;
	Zmin=Zmin<a.Verters[2].Z?Zmin:a.Verters[3].Z;
	//��X�����ֵ
	Xmax=a.Verters[0].X>a.Verters[1].X?a.Verters[0].X:a.Verters[1].X;
	Xmax=Xmax>a.Verters[2].X?Xmax:a.Verters[2].X;
	//��Y�����ֵ
	Ymax=a.Verters[0].Y>a.Verters[1].Y?a.Verters[0].Y:a.Verters[1].Y;
	Ymax=Ymax>a.Verters[2].Y?Ymax:a.Verters[2].Y;
	//��Z�����ֵ
	Zmax=a.Verters[0].Z>a.Verters[1].Z?a.Verters[0].Z:a.Verters[1].Z;
	Zmax=Zmax>a.Verters[2].Z?Zmax:a.Verters[2].Z;
}

/*-----IsOrNotInterection(AABB *a,AABB *b)---------
�������ܣ��ж�����AABB��Χ���Ƿ��ཻ
����������aΪAABB����ָ��,�������Ϊb��Χ��
--------------------------------------------------*/
//�ж�����AABB��Χ���Ƿ��ཻ
BOOL AABB::IsOrNotInterection(AABB a)
{
	if (a.Xmin>Xmax)//���a��Χ����С��X�������b��Χ�е����X����,a��Χ����X��������b���ұ�
	{
		return FALSE;
	}
	else if (a.Xmax<Xmin)//���a��Χ������X����С��b��Χ�е���С��X���꣬a��Χ����X��������b�����
	{
		return FALSE;
	}
	else if (a.Ymin>Ymax)//���a��Χ����С��Y�������b��Χ�е����Y���꣬a��Χ����Y��������b���ұ�
	{
		return FALSE;
	}
	else if (a.Ymax<Ymin)//���a��Χ������Y����С��b��Χ�е���С��Y����,a��Χ����Y��������b�����
	{
		return FALSE;
	}
	else if (a.Zmin>Zmax)//���a��Χ����С��Z�������b��Χ�е����Z���꣬a��Χ����Z��������b���Ϸ�
	{
		return FALSE;
	}
	else if (a.Zmax<Zmin)//���a��Χ������Z����С��b��Χ�е���С��Z����,a��Χ����Z��������b���·�
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}
/*-----PointIsOrNotInAABBBoundingBox(My3DPoint pt,AABB *box)�жϵ��Ƿ�����AABB��Χ��֮��------
�������ܣ��ж���ά���Ƿ�����AABB��Χ��֮��
����������ptΪMy3DPoint�ṹ�壬boxΪAABB��Χ�ж���ָ��
---------------------------------------------------------------------------------------------*/

BOOL AABB::PointIsOrNotInAABBBoundingBox(My3DPoint pt)
{
	return (pt.X>=Xmin)&&(pt.X<=Xmax)&&
		(pt.Y>=Ymin)&&(pt.Y<=Ymax)&&
		(pt.Z>=Zmin)&&(pt.Z<=Zmax);
}

/*-----GetAABBBoxCeter()-------------------------------------------
�������ܣ��õ���AABB��Χ�ж�������ģ����ģ�����һ��My3DPoint�ṹ��
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
�������ܣ��ж�AABB��Χ���Ƿ�Ϊ�գ�Ϊ�շ���TRUE����Ϊ�շ���FALSE
------------------------------------------------------------------*/
BOOL AABB::IsOrNotEmpty()
{
	return(Xmin>Xmax)||(Ymin>Ymax)||(Zmin>Zmax);
}
/*-----GetXLength()---------
�������ܣ��õ�X�����ϵĳ���
--------------------------*/
double AABB::GetXLength()
{
	return Xmax-Xmin;
}
/*-----GetYLength()---------
�������ܣ��õ�Y�����ϵĳ���
--------------------------*/
double AABB::GetYLength()
{
	return Ymax-Ymin;
}
/*-----GetZLength()---------
�������ܣ��õ�Z�����ϵĳ���
--------------------------*/
double AABB::GetZLength()
{
	return Zmax-Zmin;
}
/*-----GetVolume()-------------
�������ܣ��õ�AABB��Χ�е����
------------------------------*/
double AABB::GetVolume()
{
	return (Xmax-Xmin)*(Ymax-Ymin)*(Zmax-Zmin);
}

/*-----DrawAABBBoundingBox()-------------------
�������ܣ�����AABB��Χ��
-----------------------------------------------*/
void AABB::DrawAABBBoundingBox()
{
	glLineWidth(2);
	//��һ����
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmin);
	glVertex3f(Xmax,Ymin,Zmin);
	glEnd();
	//�ڶ�����
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmin);
	glVertex3f(Xmin,Ymin,Zmax);
	glEnd();
	//��������
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmin);
	glVertex3f(Xmin,Ymax,Zmin);
	glEnd();
	//���ĸ���
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmax);
	glVertex3f(Xmax,Ymin,Zmax);
	glEnd();
	//�������
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymin,Zmin);
	glVertex3f(Xmax,Ymin,Zmax);
	glEnd();
	//��������
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymin,Zmin);
	glVertex3f(Xmax,Ymax,Zmin);
	glEnd();
	//���߸���
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymax,Zmin);
	glVertex3f(Xmin,Ymax,Zmin);
	glEnd();
	//�ڰ˸���
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymax,Zmin);
	glVertex3f(Xmin,Ymax,Zmax);
	glEnd();
	//�ھŸ���
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymax,Zmin);
	glVertex3f(Xmax,Ymax,Zmax);
	glEnd();
	//��ʮ����
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymin,Zmax);
	glVertex3f(Xmin,Ymax,Zmax);
	glEnd();
	//��ʮһ����
	glBegin(GL_LINES);
	glVertex3f(Xmax,Ymin,Zmax);
	glVertex3f(Xmax,Ymax,Zmax);
	glEnd();
	//��ʮ������
	glBegin(GL_LINES);
	glVertex3f(Xmin,Ymax,Zmax);
	glVertex3f(Xmax,Ymax,Zmax);
	glEnd();

}
AABB::~AABB(void)
{
}
