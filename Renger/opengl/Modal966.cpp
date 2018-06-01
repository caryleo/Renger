#include "StdAfx.h"
#include "Modal966.h"


CModal966::CModal966(void)
{
	Init();
}


CModal966::~CModal966(void)
{
}

void CModal966::Init()
{
	cvModCurDir.Set(0, 0, 0);
	cvModPrevDir.Set(0, 0, 0);
	cvModCurPos.Set(0, 0, 0);
	cvModPrevPos.Set(0, 0, 0);
	cvUfoDir.Set(0, 0, 0);
	iTraceMode = 0;
	iModelMode = 0;
	bModelChange = false;
	cmModCur.One();
	cmModPrev.One();
	fSpeed = 0.1f;
}

void CModal966::RotateUfo(int dir, float ang)
{
	cmModPrev = cmModCur;
	if (dir == 0)
	{
		CMatrix966 mat;
		mat.One();
		CVector966 axis;
		axis.X(1);
		mat.SetRotate(ang, axis);
		cmModCur = cmModPrev * mat;
		CVector966 Zz;
		Zz.Z(-1);
		cvUfoDir = cmModCur.MulVector(Zz);
	}
	else
	{
		CMatrix966 mat;
		mat.One();
		CVector966 axis;
		axis.Y(1);
		mat.SetRotate(ang, axis);
		cmModCur = cmModPrev * mat;
		CVector966 Zz;
		Zz.Z(-1);
		cvUfoDir = cmModCur.MulVector(Zz);
	}
}

void CModal966::SetModelMode(int input)
{
	if (iModelMode != input)
	{

		iModelMode = input;
		if (input == 1)
		{
			if (fSpeed > 0)
			{
				bSpeed = true;
			}
			else
			{
				bSpeed = false;
			}
			fSpeed = 0;
		}
		bModelChange = true;
		
	}
	else
	{
		bModelChange = false;
	}
}
