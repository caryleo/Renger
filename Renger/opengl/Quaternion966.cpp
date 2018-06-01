#include "stdafx.h"
#include "Quaternion966.h"
#include "Vector966.h"
#include <cmath>
#include "Euler966.h"
#include "Matrix966.h"

CQuaternion966::CQuaternion966()
{
}

CQuaternion966::~CQuaternion966()
{
}

void CQuaternion966::Set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void CQuaternion966::SetAngle(float angle, CVector966 axis)
{
	w = angle;
	x = axis.x;
	y = axis.y;
	z = axis.z;
}

CQuaternion966 CQuaternion966::Conjugate()
{
	CQuaternion966 ans;
	ans.w = w;
	ans.x = -1 * x;
	ans.y = -1 * y;
	ans.z = -1 * z;
	return ans;
}

CQuaternion966& CQuaternion966::operator=(const CQuaternion966& p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
	this->w = p.w;
	return *this;
}

CQuaternion966 CQuaternion966::operator+(const CQuaternion966& p)
{
	CQuaternion966 ans;

	if ((w * p.w) < 0)
	{
		ans.x = x + p.x * -1;
		ans.y = y + p.y * -1;
		ans.z = z + p.z * -1;
		ans.w = w + p.w * -1;
	}
	else
	{
		ans.x = x + p.x;
		ans.y = y + p.y;
		ans.z = z + p.z;
		ans.w = w + p.w;
	}
	return ans;
}

CQuaternion966 CQuaternion966::operator*(float data)
{
	CQuaternion966 ans;
	ans.x = x * data;
	ans.y = y * data;
	ans.z = z * data;
	ans.w = w * data;
	return ans;
}

CQuaternion966 CQuaternion966::operator*(const CQuaternion966& p)
{
	CQuaternion966 ans;
	CVector966 tmp1, tmp2;
	tmp1.Set(x, y, z);
	tmp2.Set(p.x, p.y, p.z);
	ans.w = w * p.w - tmp1.dotMul(tmp2);
	//CVector966 ansVec = tmp1.crossMul(tmp2) + (tmp2 * w + tmp1 * p.w);
	CVector966 ansVec = tmp2.crossMul(tmp1) + (tmp2 * w + tmp1 * p.w);
	ans.x = ansVec.x;
	ans.y = ansVec.y;
	ans.z = ansVec.z;
	return ans;
}

CQuaternion966 CQuaternion966::operator/(float data)
{
	x /= data;
	y /= data;
	z /= data;
	w /= data;
	return *this;
}

float CQuaternion966::dotMul(const CQuaternion966& p)
{
	float ans = x * p.x + y * p.y + z * p.z + w * p.w;
	return ans;
}

float CQuaternion966::len()
{
	float ans = sqrtf(w * w + x * x + y * y + z * z);
	return ans;
}

bool CQuaternion966::Normalize()
{
	float len = this->len();
	if (len == 0)
	{
		return false;
	}
	w /= len;
	x /= len;
	y /= len;
	z /= len;
	return true;
}

CEuler966 CQuaternion966::ToEuler()
{
	CEuler966 ans;
	ans.p = asin(2 * w * x - 2 * y * z);
	if (cos(ans.p) == 0)
	{
		ans.h = atan2(2 * w * y - 2 * z * x, 1 - 2 * y * y - 2 * z * z);
		ans.b = 0;
	}
	else
	{
		ans.h = atan2(2 * z * x + 2 * w * y, 1 - 2 * x * x - 2 * y * y);
		ans.b = atan2(2 * x * y + 2 * w * z, 1 - 2 * z * z - 2 * x * x);
	}
	ans.h = ans.h * 180 / acosf(-1);
	ans.p = ans.p * 180 / acosf(-1);
	ans.b = ans.b * 180 / acosf(-1);
	return ans;
}

CMatrix966 CQuaternion966::ToMatrix()
{
	CMatrix966 ans;
	ans.One();
	ans[0] = 1 - 2 * y * y - 2 * z * z;
	ans[1] = 2 * x * y + 2 * w * z;
	ans[2] = 2 * x * z - 2 * w * y;
	ans[4] = 2 * x * y - 2 * w * z;
	ans[5] = 1 - 2 * x * x - 2 * z * z;
	ans[6] = 2 * y * z + 2 * w * x;
	ans[8] = 2 * x * z + 2 * w * y;
	ans[9] = 2 * y * z - 2 * w * x;
	ans[10] = 1 - 2 * x * x - 2 * y * y;
	return ans;
}

CQuaternion966& CQuaternion966::Inverse()
{
	CQuaternion966 conju = this->Conjugate();
	float len = this->len();
	CQuaternion966 ans = conju / (len * len);
	*this = ans;
	return *this;
}

CQuaternion966 CQuaternion966::GetInverse()
{
	CQuaternion966 conju = this->Conjugate();
	float len = this->len();
	CQuaternion966 ans = conju / (len * len);
	return ans;
}

CQuaternion966 CQuaternion966::Div(const CQuaternion966& b)
{
	CQuaternion966 ans;
	ans = this->GetInverse() * b;
	return ans;
}

CQuaternion966 CQuaternion966::Exp(float times)
{
	float angle = acos(w);
	float ang = angle * times;
	while (ang >= 360)
	{
		ang -= 360;
	}
	while (ang <= -360)
	{
		ang += 360;
	}
	CQuaternion966 ans;
	ans.w = cos(ang);
	ans.x = sin(ang) * (x / sin(angle));
	ans.y = sin(ang) * (y / sin(angle));
	ans.z = sin(ang) * (z / sin(angle));
	return ans;
}

void CQuaternion966::GetAngle(float& angle, CVector966& axis)
{
	Normalize();
	angle = acos(w) * 2;
	axis.x = x / sin(angle / 2);
	axis.y = y / sin(angle / 2);
	axis.z = z / sin(angle / 2);
	angle = angle * 180 / acosf(-1);
}

CQuaternion966 CQuaternion966::Slerp(const CQuaternion966& vend, float t)
{
	this->Normalize();
	CQuaternion966 tmp = vend;
	tmp.Normalize();
	CQuaternion966 ans;
	ans = (this->Div(tmp)).Exp(t);
	ans = (*this) * ans;
	return ans;
}

void CQuaternion966::Slerp(const CQuaternion966& vend, int n, float* t, CQuaternion966* result)
{
	for (int i = 0; i < n; i++)
	{
		float times = t[i];
		result[i] = Slerp(vend, times);
	}
}
