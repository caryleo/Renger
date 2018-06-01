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

	void SetAngle(float angle,CVector966 axis);					//������Ԫ��
	CQuaternion966 Conjugate();									//������ı�����

	CQuaternion966& operator=(const CQuaternion966 &p);			//���ظ�ֵ
	CQuaternion966 operator+(const CQuaternion966 &p);			//���ؼӺ�
	CQuaternion966 operator*(float data);						//��������
	CQuaternion966 operator*(const CQuaternion966 &p);			//��Ԫ���˷�
	CQuaternion966 operator/(float data);						//���س���

	float dotMul(const CQuaternion966 &p);						//���
	float len();												//��ģ
	bool Normalize();											//��׼��

	CEuler966 ToEuler();										//תŷ����
	CMatrix966 ToMatrix();										//ת����

	CQuaternion966& Inverse();									//������Ԫ������ı�����
	CQuaternion966 GetInverse();								//������Ԫ�������ı����������µ���Ԫ��
	CQuaternion966 Div(const CQuaternion966 &b);				//��bΪ����
	CQuaternion966 Exp(float times);								//��t����
	
	void GetAngle(float &angle,CVector966 &axis);				//����ת��ͽǶ�
	CQuaternion966 Slerp(const CQuaternion966 &vend, float t);	//��ֵ���ӵ�ǰ��ֵ��vend��t��[0��1]
	void Slerp(const CQuaternion966& vend, int n, float *t, CQuaternion966* result);	//һ�β�ֵ��n�����ݣ���ֵ��������������t�У�������ص�result��
};

