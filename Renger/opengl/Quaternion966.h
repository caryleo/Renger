#pragma once
#include <afxver_.h>

class CVector966;
class CEuler966;
class CMatrix966;

class AFX_CLASS_EXPORT CQuaternion966
{
public:
	CQuaternion966(void);
	~CQuaternion966(void);

	float x, y, z, w;
	void Set(float x, float y, float z, float w);
	operator float*() {return &x;}

	void SetAngle(float angle,CVector966 axis);					//设置四元数
	CQuaternion966 Conjugate();									//求共轭，不改变自身

	CQuaternion966& operator=(const CQuaternion966 &p);			//重载赋值
	CQuaternion966 operator+(const CQuaternion966 &p);			//重载加号
	CQuaternion966 operator*(float data);						//重载数乘
	CQuaternion966 operator*(const CQuaternion966 &p);			//四元数乘法
	CQuaternion966 operator/(float data);						//重载除法

	float dotMul(const CQuaternion966 &p);						//点乘
	float len();												//求模
	bool Normalize();											//标准化

	CEuler966 ToEuler();										//转欧拉角
	CMatrix966 ToMatrix();										//转矩阵

	CQuaternion966& Inverse();									//求逆四元数，会改变自身
	CQuaternion966 GetInverse();								//求逆四元数，不改变自身生成新的四元数
	CQuaternion966 Div(const CQuaternion966 &b);				//求差，b为减数
	CQuaternion966 Exp(float times);								//求t次幂
	
	void GetAngle(float &angle,CVector966 &axis);				//求旋转轴和角度
	CQuaternion966 Slerp(const CQuaternion966 &vend, float t);	//插值，从当前插值到vend，t是[0，1]
	void Slerp(const CQuaternion966& vend, int n, float *t, CQuaternion966* result);	//一次插值出n个数据，插值参数保存在数组t中，结果返回到result中
};

