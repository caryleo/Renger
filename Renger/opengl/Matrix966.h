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
	void Set(float *p);							//�����󸳳�ֵ
	void One();								//��������

	CMatrix966& operator=(const CMatrix966& m);	//������������ֵ
	CMatrix966 operator*(float d);				//���������
	CMatrix966 operator*(CMatrix966& m);		//��������

	CVector966 MulPosition(CVector966& p);		//������Կռ�λ�õõ�һ��λ�ã�wĬ��Ϊ1���������w����*��ͬ��
	CVector966 MulVector(CVector966& p);		//������Կռ�һ��������wΪ0	

	void SetRotate(float seta, CVector966 axis);//0��ʾx����ת��1��ʾy��,2��ʾz��
	void SetTrans(CVector966 trans);			//����ƽ��
	void SetScale(CVector966 scale);			//��������

	float det(int n, float *a);					//��n������ʽ��ֵ 
	void Transpose();							//����ת��
	float Inverse();							//�������棬�ɹ��򷵻�����ʽ��ֵ�����򷵻�0
	CMatrix966 GetInverse();					//���������

	CEuler966 ToEuler();						//����תŷ����
	void Translate(CVector966 trans);			//����ƽ������
	CQuaternion966 ToQuaternion();				//����ת��Ԫ��
};

