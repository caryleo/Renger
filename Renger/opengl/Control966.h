#pragma once

#include <afxver_.h>
#include <atltypes.h>



class COpenGL;
class CCamera966;
class CModal966;
class CAR;

class AFX_CLASS_EXPORT CControl966
{
public:
	CControl966(COpenGL *pGL);
	virtual ~CControl966(void);
	bool KeyProcess();//�����߼�����
	bool PreTranslateMessage(unsigned int message, unsigned int wParam, unsigned int lParam);//��������Ӧ����
	void KeyControl();
	void MouseControl(unsigned message, CPoint point, int delta = 0);
	CPoint cpMousePos, cpMousePosWindow;
private:
	void SetSpeed(float mov_speed, float rot_speed);//�ֶ������ٶ�
	bool SetKeyStatus(unsigned int nInput, bool bState);//���ü�������
	//����״̬ö�������ӽǡ�ģʽ����ʽ��Ӧ��ƽ�ơ���ת���˶��ٶȡ��л���ʾģʽ�����߲������ɴ�ģ�ͣ�
	enum KEYSTATUS{
		KS_T_GOD, KS_T_CATCH, KS_T_SYNC,\
		KS_D_EULER, KS_D_MATRIX,\
		KS_C_UFO, KS_C_ROBOT,\
		KS_M_LEFT, KS_M_RIGHT, KS_M_UP, KS_M_DOWN, KS_M_BACK, KS_M_FRONT,\
		KS_R_LEFT, KS_R_RIGHT, KS_R_UP, KS_R_DOWN, KS_R_BACK, KS_R_FRONT,\
		KS_S_N, KS_S_P,\
		KS_P, KS_SHIFT,\
		KS_M_STEP_N, KS_M_STEP_P, KS_R_STEP_N, KS_R_STEP_P,\
		KS_F_LEFT, KS_F_RIGHT, KS_F_UP, KS_F_DOWN,\
		KS_LEFT,KS_RIGHT,KS_UP,KS_DOWN,\
		KS_ALL
		}KeyVal;
	//����״̬����
	bool bKeyState[KS_ALL];
	bool bIsKeyAvail;
	//λ�ƺ���ת�ٶ�
	float fMovSpeed;
	float fRotSpeed;
	//�����ָ��
	COpenGL *pOpenGL;	
	CCamera966 *pCamera;
	CModal966 *pModal;
	CAR *pCar;
	//���״̬
	bool bMouseLeftDown;
	bool bMouseRightDown;
	bool bIsMouseAvail;
public:
	void SetAvialMode(int key, int mouse);
};