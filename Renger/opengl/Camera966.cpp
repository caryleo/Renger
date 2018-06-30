#include "stdafx.h"
#include <cmath>
#include "Camera966.h"
#include "OpenGL.h"
#include "Modal966.h"
#include <iostream>
#include <xmmintrin.h>


CCamera966::CCamera966(COpenGL* pGL)
{
	Init(pGL);
}

CCamera966::~CCamera966()
{

}

/**
 * \brief 设置视角
 * \param view 视角号码，0为上帝视角，1为跟踪视角，2为同步视角
 */
void CCamera966::SetViewMode(int view)
{
	//在1或2下，只有再按一次当前模式按键，切换到上帝视角才能继续切换
	if (iViewMode == 0)
	{
		iViewMode = view;
	}
	else if (iViewMode == view)
	{
		iViewMode = 0;
	}
}

/**
 * \brief 设置实现模式
 * \param mode 模式号码，0为欧拉角，1为子坐标系
 */
void CCamera966::SetCtrlMode(int mode)
{
	if (iCtrlMode == 0 && mode == 1)
	{
		//由欧拉角切换为子坐标系
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-ceRotEul.b, 0, 0, 1);
		glRotatef(-ceRotEul.p, 1, 0, 0);
		glRotatef(-ceRotEul.h, 0, 1, 0);
		glTranslatef(-cvMovVec.x, -cvMovVec.y, -cvMovVec.z);
		glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
		cmIEyeMat = cmEyeMat.GetInverse();
		glPopMatrix();
		iCtrlMode = mode;
	}
	if (iCtrlMode == 1 && mode == 0)
	{
		//由子坐标系切换为欧拉角
		CMatrix966 tmpMat = cmEyeMat.GetInverse();
		cvMovVec.x = tmpMat[12];
		cvMovVec.y = tmpMat[13];
		cvMovVec.z = tmpMat[14];
		CEuler966 tmpEul = tmpMat.ToEuler();
		ceRotEul = tmpEul;
		iCtrlMode = mode;
	}
}

/**
 * \brief 设置游戏模式
 * \param game 模式参数，0为开始，1为游戏中，2为结束
 */
void CCamera966::SetGameMode(int game)
{
	if (iGameMode == 0 || iGameMode == 1)
	{
		if (game == 0)
		{
			//AfxMessageBox("游戏已经开始！");
		}
		else
		{
			iGameMode = game;
		}
	}
	else
	{
		if (game == 1 || game == 2)
		{
			//AfxMessageBox("现在还没开始游戏哦！");
		}
		else
		{
			iGameMode = game;
		}
	}
}

/**
 * \brief 设置插值状态
 * \param state 插值状态
 */
void CCamera966::SetSlerp(bool state)
{
	bIsSlerp = state;
}

bool CCamera966::GetSlerp() const
{
	return bIsSlerp;
}

void CCamera966::CalSlerp(float angle)
{
	iSlerpNum = floor(angle) / 3;
	for(int i = 1; i < iSlerpNum; i++)
	{
		fSlerpTs[i - 1] = i * 1.0 / iSlerpNum;
	}
	CQuaternion966 prevQua = pModal->cvModPrevDir.ToEuler().ToQuanternion();
	CQuaternion966 curQua = pModal->cvModCurDir.ToEuler().ToQuanternion();
	prevQua.Normalize();
	curQua.Normalize();
	prevQua.Slerp(curQua, iSlerpNum - 1, fSlerpTs, cqResults);
	SetSlerp(true);
	iSlerpCount = 0;
}

void CCamera966::ChkSlerp()
{
	if (iSlerpCount >= iSlerpNum - 1)
	{
		bIsSlerp = false;
		iSlerpNum = 0;
		iSlerpCount = 0;
	}
}

CQuaternion966 CCamera966::GetSlerpQua()
{
	return cqResults[iSlerpCount++];
}


/**
 * \brief 视角的初始化操作
 */
void CCamera966::Init(COpenGL* pGL)
{
	//默认的实现模式是欧拉角，视角为上帝视角，默认不插值
	iViewMode = 0;
	iCtrlMode = 0;
	bIsSlerp = false;
	cvMovVec.Set(0, 0, 0);
	ceRotEul.Set(0, 0, 0);
	//两个矩阵置成单位矩阵
	cmEyeMat.One();
	cmIEyeMat = cmEyeMat.GetInverse();
	//默认视距为-10
	fViewDis = -10;
	pOpenGL = pGL;
	pModal = pGL->pModal;
	//
	iGameMode = 0;
	cvGameVec.Set(0, 0, 0);
	ceGameEul.Set(0, 0, 0);
	iWeight = 15;
	isGameMouseAvail = true;
}


void CCamera966::ShowView()
{
	if (iViewMode == 0)
	{
		if (iCtrlMode == 1)
		{
			glLoadMatrixf(cmEyeMat);
		}
		else
		{
			glLoadIdentity();
			glRotatef(-ceRotEul.b, 0, 0, 1);	
			glRotatef(-ceRotEul.p, 1, 0, 0);
			glRotatef(-ceRotEul.h, 0, 1, 0);
			glTranslatef(-cvMovVec.x, -cvMovVec.y, -cvMovVec.z);
		}
	}
	else if (iViewMode == 1)
	{
		glLoadIdentity();
		CVector966 pos;
		CVector966 head;
		if (bIsSlerp)
		{
			pos = pModal->cvModPrevPos + cqResults[iSlerpCount].ToEuler().ToVector3(&head) * fViewDis;
			gluLookAt(pos.x, pos.y, pos.z, pModal->cvModPrevPos.x, pModal->cvModPrevPos.y, pModal->cvModPrevPos.z, head.x, head.y, head.z);
		}
		else
		{
			if (pModal->iModelMode == 0)
			{
				pos = pModal->cvModCurPos + pModal->cvModCurDir * fViewDis;
				pModal->cvModCurDir.ToEuler().ToVector3(&head);
				gluLookAt(pos.x, pos.y, pos.z, pModal->cvModCurPos.x, pModal->cvModCurPos.y, pModal->cvModCurPos.z, head.x, head.y, head.z);
			}
			else
			{
				pos = pModal->cvModCurPos + pModal->cvUfoDir * fViewDis;
				head.Y(1);
				head = pModal->cmModCur.MulVector(head);
				gluLookAt(pos.x, pos.y, pos.z, pModal->cvModCurPos.x, pModal->cvModCurPos.y, pModal->cvModCurPos.z, head.x, head.y, head.z);
			}
		}
		
	}
	else
	{
		CVector966 dis = pModal->cvModCurPos - pModal->cvModPrevPos;
		if (iCtrlMode == 1)
		{
			glPushMatrix();
			glLoadIdentity();
			glMultMatrixf(cmEyeMat);
			if (!bIsSlerp)
			{
				glTranslatef(-dis.x, -dis.y, -dis.z);
			}
			glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
			glPopMatrix();
			glLoadMatrixf(cmEyeMat);
		}
		else
		{
			if (!bIsSlerp)
			{
				cvMovVec.x += dis.x;
				cvMovVec.y += dis.y;
				cvMovVec.z += dis.z;
			}
			glLoadIdentity();
			glRotatef(-ceRotEul.b, 0, 0, 1);	
			glRotatef(-ceRotEul.p, 1, 0, 0);
			glRotatef(-ceRotEul.h, 0, 1, 0);
			glTranslatef(-cvMovVec.x, -cvMovVec.y, -cvMovVec.z);
		}
	}
	glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
	cmIEyeMat = cmEyeMat.GetInverse();
}

/**
 * \brief 调整游戏视角
 */
void CCamera966::ShowGameView()
{
	if (iGameMode == 0)
	{
		//开始界面视角	
	}
	else if (iGameMode == 1)
	{
		
		//游戏视角
		cvGameVec.Set(float(pOpenGL->pCar->car_point.dirx), float(pOpenGL->pCar->car_point.diry) - 0.37, float(pOpenGL->pCar->car_point.dirz));
		
		CEuler966 tmpEul = cvGameVec.ToEuler();
		tmpEul.h += ceGameEul.h;
		tmpEul.p += ceGameEul.p;
		tmpEul.p = tmpEul.p < -89.0 ? -89.0 : (tmpEul.p > 0 ? 0 : tmpEul.p);
		CVector966 ansVec = tmpEul.ToVector3();
		CVector966 pos(float(pOpenGL->pCar->car_point.x), float(pOpenGL->pCar->car_point.y), float(pOpenGL->pCar->car_point.z));
		CVector966 tmp;
		if (isGameMouseAvail)
		{
			tmp = ansVec * iWeight;
		}
		else
		{
			tmp = cvGameVec * iWeight;
		}
		CVector966 viewPos = pos - tmp;
		gluLookAt(viewPos.x, viewPos.y, viewPos.z, pos.x, pos.y, pos.z, 0, 1, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
		cmIEyeMat = cmEyeMat.GetInverse();
		
	}
	else
	{
		//结束界面视角
	}
	
}

/**
 * \brief 旋转视角实现
 * \param dir 方向，0为x轴，1为y轴，2为z轴
 * \param ang 旋转角度（角度）
 */
void CCamera966::Rotate(int dir, double ang)
{
	bool bChange = false;
	if (dir == 0)
	{
		if (iViewMode == 0 || iViewMode == 2)
		{
			if (iCtrlMode == 1)
			{
				glPushMatrix();
				glLoadIdentity();
				glRotatef(-ang, 1, 0, 0);
				glMultMatrixf(cmEyeMat);
				glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
				cmIEyeMat = cmEyeMat.GetInverse();
				glPopMatrix();
			}
			else
			{
				ceRotEul.p += ang;
				bChange = true;
			}
		}
	}
	else if (dir == 1)
	{
		if (iViewMode == 0 || iViewMode == 2)
		{
			if (iCtrlMode == 1)
			{
				glPushMatrix();
				glLoadIdentity();
				glRotatef(-ang, 0, 1, 0);
				glMultMatrixf(cmEyeMat);
				glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
				cmIEyeMat = cmEyeMat.GetInverse();
				glPopMatrix();
			}
			else
			{
				ceRotEul.h += ang;
				bChange = true;
			}
		}
	}
	else
	{
		if (iViewMode == 0 || iViewMode == 2)
		{
			if (iCtrlMode == 1)
			{
				glPushMatrix();
				glLoadIdentity();
				glRotatef(-ang, 0, 0, 1);
				glMultMatrixf(cmEyeMat);
				glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
				cmIEyeMat = cmEyeMat.GetInverse();
				glPopMatrix();
			}
			else
			{
				ceRotEul.b -= ang;
				bChange = true;
			}
		}
	}
	if(bChange)//计算视点矩阵的逆矩阵
	{
		glPushMatrix();
		glLoadIdentity();		
		glRotatef(ceRotEul.h,0,1,0);
		glRotatef(ceRotEul.p,1,0,0);
		glRotatef(ceRotEul.b,0,0,1);
		glGetFloatv(GL_MODELVIEW_MATRIX,cmIEyeMat);
		glPopMatrix();
	}
}

/**
 * \brief 平移视角实现
 * \param dir 方向，0为x轴，1为y轴，2为z轴
 * \param len 平移长度
 */
void CCamera966::Move(int dir, float len)
{
	if (dir == 0)
	{
		if (iViewMode == 0 || iViewMode == 2)
		{
			if (iCtrlMode == 0)
			{
				cvMovVec.x += cmIEyeMat[0] * len;
				cvMovVec.y += cmIEyeMat[1] * len;
				cvMovVec.z += cmIEyeMat[2] * len;
			}
			else
			{
				glPushMatrix();
				glLoadIdentity();
				glTranslatef(-len, 0, 0);
				glMultMatrixf(cmEyeMat);
				glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
				glPopMatrix();
			}
		}
	}
	else if (dir == 1)
	{
		if (iViewMode == 0 || iViewMode == 2)
		{
			if (iCtrlMode == 0)
			{
				cvMovVec.x += cmIEyeMat[4] * len;
				cvMovVec.y += cmIEyeMat[5] * len;
				cvMovVec.z += cmIEyeMat[6] * len;
			}
			else
			{
				glPushMatrix();
				glLoadIdentity();
				glTranslatef(0, -len, 0);
				glMultMatrixf(cmEyeMat);
				glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
				glPopMatrix();
			}
		}
	}
	else
	{
		if (iViewMode == 0 || iViewMode == 2)
		{
			if (iCtrlMode == 0)
			{
				cvMovVec.x += cmIEyeMat[8] * len;
				cvMovVec.y += cmIEyeMat[9] * len;
				cvMovVec.z += cmIEyeMat[10] * len;
			}
			else
			{
				glPushMatrix();
				glLoadIdentity();
				glTranslatef(0, 0, -len);
				glMultMatrixf(cmEyeMat);
				glGetFloatv(GL_MODELVIEW_MATRIX, cmEyeMat);
				glPopMatrix();
			}
		}
		else
		{
			fViewDis += len;
		}
	}
}

/**
 * \brief 调整游戏视角
 * \param dir 方向，0为x，1为y
 * \param ang 旋转角度
 */
void CCamera966::GameRotate(int dir, float ang)
{
	if (dir == 0)
	{
		ceGameEul.h = ang;
	}
	else
	{
		ceGameEul.p = ang;
	}
}

void CCamera966::ChangeZoomWeight(int len)
{
	iWeight += len;
}
