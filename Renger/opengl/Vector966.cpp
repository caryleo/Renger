#include "stdafx.h"
#include "Vector966.h"
#include "Euler966.h"
#include <cmath>

CVector966::CVector966(void)
{
	x = 0;
	y = 0;
	z = 0;
}

CVector966::CVector966(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

CVector966::CVector966(float* pos)
{
	x=pos[0];
	y=pos[1];
	z=pos[2];
}

CVector966::~CVector966(void)
{

}

void CVector966::Set(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

void CVector966::Set(float* pos)
{
	x=pos[0];
	y=pos[1];
	z=pos[2];
}

CVector966& CVector966::operator=(CVector966& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
}

CVector966 CVector966::operator+(CVector966& p) const
{
	CVector966 vec;
	vec.x = x + p.x;
	vec.y = y + p.y;
	vec.z = z + p.z;
	return vec;
}

CVector966 CVector966::operator-(CVector966& p) const
{
	CVector966 vec;
	vec.x = x - p.x;
	vec.y = y - p.y;
	vec.z = z - p.z;
	return vec;
}

float CVector966::len() const
{
	return float(sqrtf(x * x + y * y + z * z));
}

void CVector966::Normalize()
{
	const float l = len();
	x /= l;
	y /= l;
	z /= l;
}

CVector966 CVector966::operator*(float data) const
{
	CVector966 vec;
	vec.x = x * data;
	vec.y = y * data;
	vec.z = z * data;
	return vec;
}

CVector966 operator*(float data, const CVector966& p)
{
	CVector966 vec;
	vec.x = p.x*data;
	vec.y = p.y*data;
	vec.z = p.z*data;
	return vec;
}

CVector966 operator*(float* mat, const CVector966& p)
{
	float v[4];
	for(int i=0;i<4;i++)
	{
		v[i] = mat[i]*p.x +mat[4+i]*p.y +mat[8+i]*p.z +mat[12+i];
	}
	CVector966 vec;
	vec.x = v[0]/v[3];
	vec.y = v[1]/v[3];
	vec.z = v[2]/v[3];
	return vec;
}


CVector966 CVector966::operator*(float* mat) const
{
	float v[4];
	int i;
	for(i=0;i<4;i++)
	{
		v[i] = mat[i*4]*x +mat[1+i*4]*y +mat[2+i*4]*z +mat[3+i*4];
	}
	CVector966 vec;
	for(i=0;i<3;i++)
		vec[i] = v[0]/v[3];
	return vec;
}

CVector966 CVector966::operator/(float data) const
{
	CVector966 vec;
	vec.x = x/data;
	vec.y = y/data;
	vec.z = z/data;
	return vec;
}

float CVector966::dotMul(CVector966& n) const
{
	float ans = 0.0;
	ans += x * n.x;
	ans += y * n.y;
	ans += z * n.z;
	return ans;
}

CVector966 CVector966::crossMul(CVector966 &n) const
{
	CVector966 vec;
	vec.x = y * n.z - z * n.y;
	vec.y = z * n.x - x * n.z;
	vec.z = x * n.y - y * n.x;
	return vec;
}

CVector966 CVector966::project(CVector966 &n)
{
	n.Normalize();
	CVector966 vec;
	const float ans = this->dotMul(n);
	vec.x = ans * n.x;
	vec.y = ans * n.y;
	vec.z = ans * n.z;
	return vec;
}

bool CVector966::operator==(CVector966& p) const
{
	return (x == p.x) && (y == p.y) && (z == p.z);
}

bool CVector966::operator!=(CVector966& p) const
{
	return (x != p.x) || (y == p.y) || (z == p.z);
}

CEuler966 CVector966::ToEuler()
{
	CEuler966 ans;
	//向量只能得到物体的模型运动方向，而滚转方向则未知
	ans.b = 0;
	CVector966 h, nz;
	//求heading角
	h.x = x;
	h.y = 0;
	h.z = z;
	if (h.x == 0 && h.z == 0)
	{
		ans.h = 0;
		if (this->y > 0)
		{
			ans.p = 90;
		}
		else if (this->y < 0)
		{
			ans.p = -90;
		}
		else
		{
			ans.p = 0;
		}
		return ans;
	}
	nz.Z(-1);
	float tmp;
	tmp = nz.dotMul(h) / (h.len() * nz.len());
	tmp = (tmp > 1) ? 1 : ((tmp < -1) ? -1 : tmp);
	float radianH = acosf(tmp);
	float angleH = radianH * 180 / acosf(-1);
	if (x > 0)
	{
		ans.h = -1 * angleH;
	}
	else
	{
		ans.h = angleH;
	}
	//求pitch角
	tmp = this->dotMul(h) / (this->len() * h.len());
	tmp = (tmp > 1) ? 1 : ((tmp < -1) ? -1 : tmp);
	float radianP = fabs(acosf(tmp));
	float angleP = radianP * 180 / acosf(-1);
	if (x > 0)
	{
		if (y > 0)
		{
			ans.p = angleP;
		}
		else
		{
			ans.p = -angleP;
		}
	}
	else if (x < 0)
	{
		if (y > 0)
		{
			ans.p = angleP;
		}
		else
		{
			ans.p = -angleP;
		}
	}
	else
	{
		if (y > 0)
		{
			ans.p = angleP;
		}
		else
		{
			ans.p = -angleP;
		}
	}
	return ans;
}

CMatrix966 CVector966::ToMatrix()
{
	return (this->ToEuler()).ToMatrix();
}
