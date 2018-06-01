#pragma once
#include <afxver_.h>

class CEuler966;
class CMatrix966;

class AFX_CLASS_EXPORT CVector966
{
public:
	CVector966(void);
	CVector966(float fx, float fy, float fz);
	CVector966(float *pos);
	~CVector966(void);
	float x, y, z;

	operator float*() {return &x;}				//自动类型转换
	void Set(float fx, float fy, float fz);		//置值
	void Set(float *pos);
	CVector966& operator=(CVector966& p);		//赋值
	CVector966 operator+(CVector966& p) const;	//向量加
	CVector966 operator-(CVector966& p) const;	//向量减
	void Normalize();							//向量规范化
	float len() const;							//向量求模
	CVector966 operator*(float data) const;		//向量数乘
	friend CVector966 operator*(float data, const CVector966& p);
	CVector966 operator*(float *mat) const;
	friend CVector966 operator*(float *mat, const CVector966& p);
	CVector966 operator/(float data) const;
	float dotMul(CVector966& n) const;			//向量点乘
	CVector966 crossMul(CVector966 &n) const;	//向量叉乘
	CVector966 project(CVector966 &n);			//向量投影
	bool operator==(CVector966& p) const;		//相等比较
	bool operator!=(CVector966& p) const;		//不等比较

	//取单位向量
	void X(int n)
	{
		x = n * 1.0f;
		y = 0.0;
		z = 0.0;
	}

	void Y(int n)
	{
		x = 0.0;
		y = n * 1.0f;
		z = 0.0;
	}

	void Z(int n)
	{
		x = 0.0;
		y = 0.0;
		z = n * 1.0f;
	}

	CEuler966 ToEuler();						//向量转欧拉角
	CMatrix966 ToMatrix();						//向量转矩阵
};

