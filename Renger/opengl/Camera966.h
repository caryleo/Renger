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

	CVector966 cvMovVec;//ƽ������
	CEuler966 ceRotEul;//��תŷ����
	CMatrix966 cmEyeMat;//��ͼ����
	CMatrix966 cmIEyeMat;//��ͼ����������
	CVector966 cvGameVec;//��Ϸ�ӽǷ�������
	CEuler966 ceGameEul;//��Ϸ�ӽǵ���ֵ

private:
	float fViewDis;//�����ӽ��Ӿ�
	int iViewMode;//�ӽ�ģʽ��0Ϊ�ϵ��ӽǣ�1Ϊ�����ӽǣ�2Ϊͬ���ӽ�
	int iCtrlMode;//ʵ��ģʽ��0Ϊŷ���ǣ�1Ϊ������ϵ
	int iGameMode;//��Ϸģʽ��0Ϊ��ʼ��1Ϊ��Ϸ�У�2Ϊ����
	bool bIsSlerp;//��ֵ״̬��
	int iSlerpNum;//��ֵ��
	float fSlerpTs[360];//��ֵϵ��
	CQuaternion966 cqResults[360];//��ֵ���
	int iSlerpCount;//��ֵ������
	COpenGL *pOpenGL;
	CModal966 *pModal;
};
