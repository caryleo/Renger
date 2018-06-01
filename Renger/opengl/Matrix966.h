#pragma once
#include <afxver_.h>


class CQuaternion966;
class CVector966;
class CEuler966;

class AFX_CLASS_EXPORT CMatrix966
{
public:
	CMatrix966(void);
	~CMatrix966(void);

	float m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33;

	operator float*(){return &m00;};
	void Set(float *p);							//给矩阵赋初值
	void One();								//矩阵清零

	CMatrix966& operator=(const CMatrix966& m);	//矩阵的运算符赋值
	CMatrix966 operator*(float d);				//矩阵的数乘
	CMatrix966 operator*(CMatrix966& m);		//矩阵的相乘

	CVector966 MulPosition(CVector966& p);		//矩阵乘以空间位置得到一个位置，w默认为1，结果不除w，与*不同。
	CVector966 MulVector(CVector966& p);		//矩阵乘以空间一个向量，w为0	

	void SetRotate(float seta, CVector966 axis);//0表示x轴旋转，1表示y轴,2表示z轴
	void SetTrans(CVector966 trans);			//矩阵平移
	void SetScale(CVector966 scale);			//矩阵缩放

	float det(int n, float *a);					//求n阶行列式的值 
	void Transpose();							//矩阵转置
	float Inverse();							//矩阵求逆，成功则返回行列式的值，否则返回0
	CMatrix966 GetInverse();					//返回逆矩阵

	CEuler966 ToEuler();						//矩阵转欧拉角
	void Translate(CVector966 trans);			//插入平移数据
	CQuaternion966 ToQuaternion();				//矩阵转四元数
};

