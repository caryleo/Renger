#pragma once

class CModal966
{
public:
	CModal966(void);
	~CModal966(void);
	void Init();
	void RotateUfo(int dir, float ang);
	void SetModelMode(int input);
	CVector966 cvModPrevPos;//模型前一位置
	CVector966 cvModCurPos;//模型当前位置
	CVector966 cvModPrevDir;//模型前一方向
	CVector966 cvModCurDir;//模型当前方向
	CVector966 cvUfoDir;//飞船方向
	CMatrix966 cmModPrev;
	CMatrix966 cmModCur;
	int iTraceMode;//轨迹显示模式，0为管道，1为面片
	int iModelMode;//模型模式，0为机器人，1为飞船
	bool bModelChange;
	float fSpeed;
	bool bSpeed;
};

