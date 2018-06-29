#pragma once

#include <afxver_.h>
#include "gl\glut.h"
#include "Vector966.h"
#include "Euler966.h"
#include "Matrix966.h"
#include "Quaternion966.h"

class COpenGL;
class CModal966;

class AFX_CLASS_EXPORT CCamera966
{
public:
	CCamera966(COpenGL* pGL);
	virtual ~CCamera966(void);

	void SetViewMode(int view);
	void SetCtrlMode(int mode);
	void SetGameMode(int game);
	void SetSlerp(bool state);
	bool GetSlerp() const;
	void CalSlerp(float angle);
	void ChkSlerp();
	CQuaternion966 GetSlerpQua();
	
	void Init(COpenGL* pGL);
	void ShowView();
	void ShowGameView();
	void Rotate(int dir, double ang);
	void Move(int dir, float len);
	void GameRotate(int dir, float ang);

	CVector966 cvMovVec;//平移向量
	CEuler966 ceRotEul;//旋转欧拉角
	CMatrix966 cmEyeMat;//视图矩阵
	CMatrix966 cmIEyeMat;//视图矩阵的逆矩阵
	CVector966 cvGameVec;//游戏视角方向向量
	CEuler966 ceGameEul;//游戏视角调整值

private:
	float fViewDis;//跟踪视角视距
	int iViewMode;//视角模式，0为上帝视角，1为跟踪视角，2为同步视角
	int iCtrlMode;//实现模式，0为欧拉角，1为子坐标系
	int iGameMode;//游戏模式，0为开始，1为游戏中，2为结束
	bool bIsSlerp;//插值状态量
	int iSlerpNum;//插值量
	float fSlerpTs[360];//插值系数
	CQuaternion966 cqResults[360];//插值结果
	int iSlerpCount;//插值计数器
	COpenGL *pOpenGL;
	CModal966 *pModal;
};
