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
	bool KeyProcess();//键盘逻辑主控
	bool PreTranslateMessage(unsigned int message, unsigned int wParam, unsigned int lParam);//控制类响应主控
	void KeyControl();
	void MouseControl(unsigned message, CPoint point, int delta = 0);
	CPoint cpMousePos, cpMousePosWindow;
private:
	void SetSpeed(float mov_speed, float rot_speed);//手动设置速度
	bool SetKeyStatus(unsigned int nInput, bool bState);//设置键盘数组
	//键盘状态枚举量（视角、模式、形式响应、平移、旋转、运动速度、切换显示模式、二者步长，飞船模型）
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
	//键盘状态数组
	bool bKeyState[KS_ALL];
	bool bIsKeyAvail;
	//位移和旋转速度
	float fMovSpeed;
	float fRotSpeed;
	//相关类指针
	COpenGL *pOpenGL;	
	CCamera966 *pCamera;
	CModal966 *pModal;
	CAR *pCar;
	//鼠标状态
	bool bMouseLeftDown;
	bool bMouseRightDown;
	bool bIsMouseAvail;
public:
	void SetAvialMode(int key, int mouse);
};