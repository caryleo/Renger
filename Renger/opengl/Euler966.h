#pragma once
#include <afxver_.h>

class CVector966;
class CMatrix966;
class CQuaternion966;

class AFX_CLASS_EXPORT CEuler966
{
public:
	CEuler966(void);
	~CEuler966(void);

	float h, p, b;

	void Set(float h, float p, float b);
	operator float*(){return &h;}

	CEuler966& operator=(const CEuler966& p);

	CVector966 ToVector3(CVector966 *updir = 0);//欧拉角转向量

	CMatrix966 ToMatrix();						//欧拉角转矩阵

	CQuaternion966 ToQuanternion();				//欧拉角转四元数

	//void eulerNormal();						//欧拉角规范化
	void Normal();								//欧拉角规范化	
};
