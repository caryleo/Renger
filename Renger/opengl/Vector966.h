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

	operator float*() {return &x;}				//�Զ�����ת��
	void Set(float fx, float fy, float fz);		//��ֵ
	void Set(float *pos);
	CVector966& operator=(CVector966& p);		//��ֵ
	CVector966 operator+(CVector966& p) const;	//������
	CVector966 operator-(CVector966& p) const;	//������
	void Normalize();							//�����淶��
	float len() const;							//������ģ
	CVector966 operator*(float data) const;		//��������
	friend CVector966 operator*(float data, const CVector966& p);
	CVector966 operator*(float *mat) const;
	friend CVector966 operator*(float *mat, const CVector966& p);
	CVector966 operator/(float data) const;
	float dotMul(CVector966& n) const;			//�������
	CVector966 crossMul(CVector966 &n) const;	//�������
	CVector966 project(CVector966 &n);			//����ͶӰ
	bool operator==(CVector966& p) const;		//��ȱȽ�
	bool operator!=(CVector966& p) const;		//���ȱȽ�

	//ȡ��λ����
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

	CEuler966 ToEuler();						//����תŷ����
	CMatrix966 ToMatrix();						//����ת����
};

