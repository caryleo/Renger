#include "stdafx.h"
#include "Euler966.h"
#include "Vector966.h"
#include "Matrix966.h"
#include "Quaternion966.h"

CEuler966::CEuler966()
{
}

CEuler966::~CEuler966()
{
}

void CEuler966::Set(float h, float p, float b)
{
	this->h = h;
	this->p = p;
	this->b = b;
}

CEuler966& CEuler966::operator=(const CEuler966& s)
{
	h = s.h;
	p = s.p;
	b = s.b;
	return *this;
}

CVector966 CEuler966::ToVector3(CVector966* updir)
{
	//初始向量为0，0，-1
	CVector966 ansn;
	ansn.Z(-1);
	//上方向量为0，1，0
	CVector966 ansup;
	ansup.Y(1);
	CMatrix966 final = this->ToMatrix();
	CVector966 ansz = final.MulVector(ansn);
	CVector966 ansy = final.MulVector(ansup);
	if (updir != 0)
	{
		updir->x = ansy.x;
		updir->y = ansy.y;
		updir->z = ansy.z;
	}
	return ansz;
}

CMatrix966 CEuler966::ToMatrix()
{
	CMatrix966 rx, ry, rz;
	CVector966 vx, vy, vz;
	vx.X(1);
	vy.Y(1);
	vz.Z(1);
	ry.SetRotate(this->h, vy);
	rx.SetRotate(this->p, vx);
	rz.SetRotate(this->b, vz);
	CMatrix966 ans = ry * rx * rz;
	return ans;
}

CQuaternion966 CEuler966::ToQuanternion()
{
	/*CQuaternion966 ans;
	float angleH = this->h;
	angleH = angleH * acosf(-1) / 180;
	angleH /= 2;
	float angleP = this->p;
	angleP = angleP * acosf(-1) / 180;
	angleP /= 2;
	float angleB = this->b;
	angleB = angleB * acosf(-1) / 180;
	angleB /= 2;
	ans.x = cos(angleH) * sin(angleP) * cos(angleB) + sin(angleH) * cos(angleP) * sin(angleH);
	ans.y = sin(angleH) * cos(angleP) * cos(angleB) - cos(angleH) * sin(angleP) * sin(angleB);
	ans.z = cos(angleH) * cos(angleP) * sin(angleB) - sin(angleH) * sin(angleP) * cos(angleB);
	ans.w = cos(angleH) * cos(angleP) * cos(angleB) + sin(angleH) * sin(angleP) * sin(angleB);*/
	CMatrix966 tmpMat = this->ToMatrix();
	CQuaternion966 ans = tmpMat.ToQuaternion();
	return ans;
}

void CEuler966::Normal()
{
	while (p < -90)
	{
		p += 360;
	}
	while (p > 90)
	{
		p -= 360;
	}
	//万向锁
	if (p == -90 || p == 90)
	{
		h = h + b;
		b = 0;
	}
	while (h < -180)
	{
		h += 360;
	}
	while (h > 180)
	{
		h -= 360;
	}
	while (b < -180)
	{
		b += 360;
	}
	while (b > 180)
	{
		b -= 360;
	}
}
