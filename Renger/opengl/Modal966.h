#pragma once

class CModal966
{
public:
	CModal966(void);
	~CModal966(void);
	void Init();
	void RotateUfo(int dir, float ang);
	void SetModelMode(int input);
	CVector966 cvModPrevPos;//ģ��ǰһλ��
	CVector966 cvModCurPos;//ģ�͵�ǰλ��
	CVector966 cvModPrevDir;//ģ��ǰһ����
	CVector966 cvModCurDir;//ģ�͵�ǰ����
	CVector966 cvUfoDir;//�ɴ�����
	CMatrix966 cmModPrev;
	CMatrix966 cmModCur;
	int iTraceMode;//�켣��ʾģʽ��0Ϊ�ܵ���1Ϊ��Ƭ
	int iModelMode;//ģ��ģʽ��0Ϊ�����ˣ�1Ϊ�ɴ�
	bool bModelChange;
	float fSpeed;
	bool bSpeed;
};

