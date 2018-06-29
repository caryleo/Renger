#include "stdafx.h"
#include <cmath>
#include "Matrix966.h"
#include "Vector966.h"
#include "Euler966.h"
#include "Quaternion966.h"
#include <stdlib.h>

CMatrix966::CMatrix966(void)
{
}


CMatrix966::~CMatrix966(void)
{
}

void CMatrix966::Set(float* p)
{
	for (int i = 0; i < 16; i++)
	{
		(*this)[i] = p[i];
	}
}

void CMatrix966::One()
{
	for (int i = 0; i < 16; i++)
	{
		(*this)[i] = 0;
	}
	m00 = 1;
	m11 = 1;
	m22 = 1;
	m33 = 1;
}

CMatrix966& CMatrix966::operator=(const CMatrix966& m)
{
	float const *p = &(m.m00);
	for (int i = 0; i < 16; i++)
	{
		(*this)[i] = p[i];
	}
	return *this;
}

CMatrix966 CMatrix966::operator*(float d)
{
	CMatrix966 ans;
	for (int i = 0; i < 16; i++)
	{
		ans[i] = (*this)[i] * d;
	}
	return ans;
}

CMatrix966 CMatrix966::operator*(CMatrix966& m)
{
	CMatrix966 ans;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float tmp = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				tmp += (*this)[i + k * 4] * m[j * 4 + k];
			}
			ans[i + j * 4] = tmp;
		}
	}
	return ans;
}

CVector966 CMatrix966::MulPosition(CVector966& p)	//������Կռ�λ�õõ�һ��λ�ã�wĬ��Ϊ1���������w����*��ͬ��
{
	CVector966 vec;
	for (int i = 0; i < 3; i++)
	{
		vec[i] = (*this)[i] * p.x + (*this)[4 + i] * p.y + (*this)[8 + i] * p.z + (*this)[12 + i];
	}
	float w = (*this)[3] * p.x + (*this)[7] * p.y + (*this)[11] * p.z + (*this)[15];
	
	return vec;
}

CVector966 CMatrix966::MulPosition(CVector966& p, float& w)
{
	CVector966 vec;
	for (int i = 0; i < 3; i++)
	{
		vec[i] = (*this)[i] * p.x + (*this)[4 + i] * p.y + (*this)[8 + i] * p.z + (*this)[12 + i];
	}
	w = (*this)[3] * p.x + (*this)[7] * p.y + (*this)[11] * p.z + (*this)[15];
	return vec;
}

CVector966 CMatrix966::MulVector(CVector966& p)
{
	CVector966 vec;
	for (int i = 0; i < 3; i++)
	{
		vec[i] = float((*this)[i] * p.x + (*this)[4 + i] * p.y + (*this)[8 + i] * p.z);
	}
	return vec;
}

void CMatrix966::SetRotate(float seta, CVector966 axis)	//any axes
{
	this->One();
	axis.Normalize();
	seta = acosf(-1) * seta / 180;
	float c = cosf(seta);
	float s = sinf(seta);
	m00 = axis.x * axis.x * (1 - c) + c;
	m01 = axis.x * axis.y * (1 - c) - axis.z * s;
	m02 = axis.x * axis.z * (1 - c) + axis.y * s;
	m10 = axis.x * axis.y * (1 - c) + axis.z * s;
	m11 = axis.y * axis.y * (1 - c) + c;
	m12 = axis.y * axis.z * (1 - c) - axis.x * s;
	m20 = axis.x * axis.z * (1 - c) - axis.y * s;
	m21 = axis.y * axis.z * (1 - c) + axis.x * s;
	m22 = axis.z * axis.z * (1 - c) + c;
}

void CMatrix966::SetTrans(CVector966 trans)
{
	this->One();
	m03 = trans.x;
	m13 = trans.y;
	m23 = trans.z;
}

void CMatrix966::SetScale(CVector966 scale)
{
	this->One();
	m00 = 1 * scale.x;
	m11 = 1 * scale.y;
	m22 = 1 * scale.z;
}

float CMatrix966::det(int n, float* a)
{
	if (n == 1)	//һ�׼���ֵ
	{
		return a[0];
	}
	float *b = new float[(n - 1) * (n - 1)];	//����n-1�׵Ĵ�������ʽ��b     
	int mov = 0;//�ж����Ƿ��ƶ�     
	float sum = 0.0;//sumΪ����ʽ��ֵ    
	for (int arow = 0; arow < n; arow++) // a�������Ѿ���a(nn)��ֵ��b(n-1)    
	{
		for (int brow = 0; brow < n - 1; brow++)//��a���һ�и�Ԫ�صĴ�������ʽ�浽bb    
		{
			mov = arow > brow ? 0 : 1; //b��С��arow���У�ͬ�и�ֵ�����ڵĴ�������ڵļ�һ    
			for (int j = 0; j < n - 1; j++)  //��a�ĵڶ��и�ֵ����n��    
			{
				b[brow + j * (n - 1)] = a[(j + 1) * n + brow + mov];
			}
		}
		int flag = arow % 2 == 0 ? 1 : -1;//��Ϊ����Ϊ0������������ż��ʱ�򣬴�������ʽΪ1.    
		sum += flag * a[arow] * det(n - 1, b);//a��һ�и�Ԫ�������������ʽ���ĺͼ�Ϊ����ʽ  
	}
	delete[]b;
	return sum;
}

void CMatrix966::Transpose()
{
	CMatrix966 tmp;
	tmp.Set(*this);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			(*this)[4 * i + j] = tmp[4 * j + i];

		}
	}
}

float CMatrix966::Inverse()
{
	CMatrix966 inv;
	inv.One();
	inv.m00 = 0;
	inv.m11 = 0;
	inv.m22 = 0;
	inv.m33 = 0;
	float detSelf = det(4, *this);
	if (detSelf == 0)	//����ʽֵΪ0�����󲻿���
	{
		Set(inv);
		return detSelf;
	}
	CMatrix966 adj;				//��׼�������
	float *b = new float[3 * 3];//��������ʽ
	for (int arow = 0; arow < 4; arow++)
	{
		for (int acol = 0; acol < 4; acol++)
		{
			for (int brow = 0; brow < 3; brow++)
			{
				for (int bcol = 0; bcol < 3; bcol++)
				{
					//ȷ����һ��Ԫ�صĶ�Ӧλ��
					int offrow = arow > brow ? 0 : 1;
					int offcol = acol > bcol ? 0 : 1;
					b[brow + bcol * 3] = (*this)[brow + offrow + (offcol + bcol) * 4];
				}
			}
			int q = (arow + acol) % 2 == 0 ? 1 : -1;	//��������ʽϵ��
			adj[acol + arow * 4] = q * det(3, b);	//ֱ�Ӿ�ת����
		}
	}

	//��׼��
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			inv[i + j * 4] = adj[i + j * 4] / detSelf;
		}
	}
	Set(inv);
	delete[] b;
	return det(4, inv);
}

CMatrix966 CMatrix966::GetInverse()
{
	CMatrix966 ans;
	ans.Set(*this);
	ans.Inverse();
	return ans;
}

CEuler966 CMatrix966::ToEuler()
{
	CEuler966 ans;
	ans.p = asin(-1 * (*this)[9]);
	if (cos(ans.p) == 0)
	{
		ans.h = atan2(-1 * (*this)[2], (*this)[0]);
		ans.b = 0;
	}
	else
	{
		ans.h = atan2((*this)[8], (*this)[10]);
		ans.b = atan2((*this)[1], (*this)[5]);
	}
	ans.h = ans.h * 180 / acosf(-1);
	ans.p = ans.p * 180 / acosf(-1);
	ans.b = ans.b * 180 / acosf(-1);
	return ans;
}

void CMatrix966::Translate(CVector966 trans)
{
	(*this)[12] = trans.x;
	(*this)[13] = trans.y;
	(*this)[14] = trans.z;
}

CQuaternion966 CMatrix966::ToQuaternion()
{
	CQuaternion966 ans;
	float tmpw = sqrtf((*this)[0] + (*this)[5] + (*this)[10] + 1) / 2;
	float tmpx = sqrtf((*this)[0] - (*this)[5] - (*this)[10] + 1) / 2;
	float tmpy = sqrtf(-1 * (*this)[0] + (*this)[5] - (*this)[10] + 1) / 2;
	float tmpz = sqrtf(-1 * (*this)[0] - (*this)[5] + (*this)[10] + 1) / 2;
	if (tmpw > tmpx)
	{
		if (tmpy > tmpw)
		{
			if (tmpz > tmpy)
			{
				//z���
				ans.z = tmpz;
				ans.w = ((*this)[1] - (*this)[4]) / (4 * ans.z);
				ans.x = ((*this)[8] + (*this)[2]) / (4 * ans.z);
				ans.y = ((*this)[6] + (*this)[9]) / (4 * ans.z);
			}
			else
			{
				//y���
				ans.y = tmpy;
				ans.w = ((*this)[8] - (*this)[2]) / (4 * ans.y);
				ans.x = ((*this)[1] + (*this)[4]) / (4 * ans.y);
				ans.z = ((*this)[6] + (*this)[9]) / (4 * ans.y);
			}
		}
		else
		{
			if (tmpz > tmpw)
			{
				//z���
				ans.z = tmpz;
				ans.w = ((*this)[1] - (*this)[4]) / (4 * ans.z);
				ans.x = ((*this)[8] + (*this)[2]) / (4 * ans.z);
				ans.y = ((*this)[6] + (*this)[9]) / (4 * ans.z);
			}
			else
			{
				//w���
				ans.w = tmpw;
				ans.x = ((*this)[6] - (*this)[9]) / (4 * ans.w);
				ans.y = ((*this)[8] - (*this)[2]) / (4 * ans.w);
				ans.z = ((*this)[1] - (*this)[4]) / (4 * ans.w);
			}
		}
	}
	else
	{
		if (tmpy > tmpx)
		{
			if (tmpz > tmpy)
			{
				//z���
				ans.z = tmpz;
				ans.w = ((*this)[1] - (*this)[4]) / (4 * ans.z);
				ans.x = ((*this)[8] + (*this)[2]) / (4 * ans.z);
				ans.y = ((*this)[6] + (*this)[9]) / (4 * ans.z);
			}
			else
			{
				//y���
				ans.y = tmpy;
				ans.w = ((*this)[8] - (*this)[2]) / (4 * ans.y);
				ans.x = ((*this)[1] + (*this)[4]) / (4 * ans.y);
				ans.z = ((*this)[6] + (*this)[9]) / (4 * ans.y);
			}
		}
		else
		{
			if (tmpz > tmpx)
			{
				//z���
				ans.z = tmpz;
				ans.w = ((*this)[1] - (*this)[4]) / (4 * ans.z);
				ans.x = ((*this)[8] + (*this)[2]) / (4 * ans.z);
				ans.y = ((*this)[6] + (*this)[9]) / (4 * ans.z);
			}
			else
			{
				//x���
				ans.x = tmpx;
				ans.w = ((*this)[6] - (*this)[9]) / (4 * ans.x);
				ans.y = ((*this)[1] + (*this)[4]) / (4 * ans.x);
				ans.z = ((*this)[8] + (*this)[2]) / (4 * ans.x);
			}
		}
	}
	return ans;
}
