#include "stdafx.h"
#include <afxver_.h>
#include "Control966.h"
#include "Camera966.h"
#include "Modal966.h"
#include "OpenGL.h"
#include <iostream>

CControl966::CControl966(COpenGL* pGL)
{
	pOpenGL = pGL;
	pCamera = pGL->pCamera;
	pModal = pGL->pModal;
	//���а�����ʼ״̬�¶�û�б�����
	for (int i = 0; i < KS_ALL; i++)
	{
		bKeyState[i] = false;
	}
	//��ʼ������Ϊ1
	fMovSpeed = 0.5;
	fRotSpeed = 0.5;
	bMouseLeftDown = false;
	bMouseRightDown = false;
	bIsKeyAvail = true;
	bIsMouseAvail = true;
	//GetCursorPos(&cpMousePos);
	//ScreenToClient(pOpenGL->m_hmyWnd, &cpMousePos);
}

CControl966::~CControl966()
{

}

/**
 * \brief ������Ӧ�����������
 * \param message ������Ϣ
 * \param wParam ��������
 * \param lParam �������
 * \return 
 */
bool CControl966::PreTranslateMessage(unsigned message, unsigned wParam, unsigned lParam)
{
	
	CPoint point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	if (point.x != 0 && point.y != 0)
	{
		std::cout << point.x << " " << point.y << std::endl;
	}
	if (message == WM_LBUTTONDOWN)
	{
		if (!bIsMouseAvail)
		{
			return true;
		}
		bMouseLeftDown = true;
	}
	if (message == WM_LBUTTONUP)
	{
		if (!bIsMouseAvail)
		{
			return true;
		}
		bMouseLeftDown = false;
	}
	if (message == WM_RBUTTONDOWN)
	{
		if (!bIsMouseAvail)
		{
			return true;
		}
		bMouseRightDown = true;
	}
	if (message == WM_RBUTTONUP)
	{
		if (!bIsMouseAvail)
		{
			return true;
		}
		bMouseRightDown = false;
	}
	if (message == WM_LBUTTONDBLCLK)
	{
		if (!bIsMouseAvail)
		{
			return true;
		}
		
	}
	if (message == WM_RBUTTONDBLCLK)
	{
		if (!bIsMouseAvail)
		{
			return true;
		}
	}
	if (message == WM_MOUSEMOVE)
	{
		std::cout << "HA!" << std::endl;
		if (!bIsMouseAvail)
		{
			return true;
		}
		//����ƶ�ʱ��������ת�ӽ�
		MouseControl(WM_MOUSEMOVE, point);
		//�����λ�ý��и���
		cpMousePos = point;
	}
	if (message == WM_MOUSEWHEEL)
	{
		std::cout << "NA!" << std::endl;
		if (!bIsMouseAvail)
		{
			return true;
		}
		//������ʱ����������
		ScreenToClient(pOpenGL->m_hmyWnd, &point);
		short len = HIWORD(wParam);
		MouseControl(WM_MOUSEWHEEL, point, len);
		cpMousePos = point;
	}
	if (message == WM_MOUSEHOVER)
	{
		if (!bIsMouseAvail)
		{
			return true;
		}
	}
	if (message == WM_MOUSELEAVE)
	{
		if (!bIsMouseAvail)
		{
			return true;
		}
	}
	if (message == WM_KEYDOWN)
	{
		if (!bIsKeyAvail)
		{
			return true;
		}
		//��⵽��������
		bool ans = SetKeyStatus(wParam, true);
		KeyControl();
		return ans;
	}
	if (message == WM_KEYUP)
	{
		if (!bIsKeyAvail)
		{
			return true;
		}
		//��⵽����̧��
		bool ans = SetKeyStatus(wParam, false);
		KeyControl();
		return ans;
	}
	return false;
}

void CControl966::KeyControl()
{
	//��ʾ�ӽǣ��ϵ��ӽǡ������ӽǺ�ͬ���ӽ�
	if (bKeyState[KS_T_GOD])
	{
		pCamera->SetViewMode(0);
	}
	if (bKeyState[KS_T_CATCH])
	{
		pCamera->SetViewMode(1);
	}
	if (bKeyState[KS_T_SYNC])
	{
		pCamera->SetViewMode(2);
	}

	//ʵ��ģʽ��ŷ���ǡ�������ϵ
	if (bKeyState[KS_D_EULER])
	{
		pCamera->SetCtrlMode(0);
	}
	if (bKeyState[KS_D_MATRIX])
	{
		pCamera->SetCtrlMode(1);
	}

	//ģ���л����ɴ���������
	if (bKeyState[KS_C_UFO])
	{
		pModal->SetModelMode(1);
	}
	if (bKeyState[KS_C_ROBOT])
	{
		pModal->SetModelMode(0);
	}

	//�˶��ٶ��޸�
	if (bKeyState[KS_S_N])
	{
		pModal->fSpeed -= 0.01;
	}
	if (bKeyState[KS_S_P])
	{
		pModal->fSpeed += 0.01;
	}

	//�л���ʾģʽ
	if (bKeyState[KS_P])
	{
		int tmp = pModal->iTraceMode;
		pModal->iTraceMode = 1 - tmp;
	}

	//�ƶ��ٶ��޸ģ�ƽ�ơ���ת
	if (bKeyState[KS_M_STEP_N])
	{
		fMovSpeed *= 0.99;
	}
	if (bKeyState[KS_M_STEP_P])
	{
		fMovSpeed *= 1.01;
	}
	if (bKeyState[KS_R_STEP_N])
	{
		if (bKeyState[KS_SHIFT])
		{
			fRotSpeed *= 0.99;
		}
	}
	if (bKeyState[KS_R_STEP_P])
	{
		if (bKeyState[KS_SHIFT])
		{
			fRotSpeed *= 1.01;
		}
	}

	//�ɴ��ƶ�
	if (bKeyState[KS_F_LEFT])
	{
		pModal->RotateUfo(1, 1);
	}
	if (bKeyState[KS_F_RIGHT])
	{
		pModal->RotateUfo(1, -1);
	}
	if (bKeyState[KS_F_UP])
	{
		pModal->RotateUfo(0, 1);
	}
	if (bKeyState[KS_F_DOWN])
	{
		pModal->RotateUfo(0, -1);
	}

}

void CControl966::MouseControl(unsigned message, CPoint point, int delta)
{
	bool isRet = false;
	if (message == WM_MOUSEMOVE)
	{
		isRet = true;
		CPoint dis = point - cpMousePos;
		if (dis.x == 0 && dis.y == 0)
		{
			return;
		}
		//std::cout << dis.x << " " << dis.y << std::endl;
		int lenx = pOpenGL->m_windowrect.right;
		int leny = pOpenGL->m_windowrect.bottom;
		double movx = dis.x * 1.0 / (lenx * 1.0 / 180);
		double movy = dis.y * 1.0 / (leny * 1.0 / 360);
		//std::cout << movx << " " << movy << std::endl;
		pCamera->Rotate(1, -movx);
		pCamera->Rotate(0, -movy);
	}
	else if (message == WM_MOUSEWHEEL)
	{
		isRet = true;
		std::cout << delta << std::endl;
		pCamera->Move(2, -delta * 0.01);
	}
	if (isRet)
	{
		pOpenGL->OnPaint();
	}
}


/**
 * \brief �����ٶ�
 * \param mov_speed ƽ���ٶ� 
 * \param rot_speed ��ת�ٶ�
 */
void CControl966::SetSpeed(float mov_speed, float rot_speed)
{
	fMovSpeed = mov_speed;
	fRotSpeed = rot_speed;
}

/**
 * \brief ִ�м����߼�
 * \return ����ִ�еĽ�����Ƿ��а����߼���ִ�У����ɹ�����ʧ��
 */
bool CControl966::KeyProcess()
{
	bool bIsAnyDown = false;

	//ƽ��
	if (bKeyState[KS_M_FRONT])
	{
		pCamera->Move(2, fMovSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_M_BACK])
	{
		pCamera->Move(2, -fMovSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_M_LEFT])
	{
		pCamera->Move(0, -fMovSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_M_RIGHT])
	{
		pCamera->Move(0, fMovSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_M_UP])
	{
		pCamera->Move(1, fMovSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_M_DOWN])
	{
		pCamera->Move(1, -fMovSpeed);
		bIsAnyDown = true;
	}

	//��ת
	if (bKeyState[KS_R_FRONT])
	{
		pCamera->Rotate(2, -fRotSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_R_BACK])
	{
		pCamera->Rotate(2, fRotSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_R_LEFT])
	{
		pCamera->Rotate(1, fRotSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_R_RIGHT])
	{
		pCamera->Rotate(1, -fRotSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_R_UP])
	{
		pCamera->Rotate(0, fRotSpeed);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_R_DOWN])
	{
		pCamera->Rotate(0, -fRotSpeed);
		bIsAnyDown = true;
	}
	
	//�ɴ��ƶ�
	if (bKeyState[KS_F_LEFT])
	{
		pModal->RotateUfo(1, 1);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_F_RIGHT])
	{
		pModal->RotateUfo(1, -1);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_F_UP])
	{
		pModal->RotateUfo(0, 1);
		bIsAnyDown = true;
	}
	if (bKeyState[KS_F_DOWN])
	{
		pModal->RotateUfo(0, -1);
		bIsAnyDown = true;
	}

	return bIsAnyDown;
}

/**
 * \brief ���ð���״̬
 * \param nInput ����
 * \param bState ״̬
 * \return 
 */
bool CControl966::SetKeyStatus(unsigned nInput, bool bState)
{
	pOpenGL->OnKey(nInput, bState);
	switch (nInput)
	{
	case '0':
		bKeyState[KS_T_GOD] = bState;
		break;
	case '1':
		bKeyState[KS_T_CATCH] = bState;
		break;
	case '2':
		bKeyState[KS_T_SYNC] = bState;
		break;
	case '3':
		bKeyState[KS_D_EULER] = bState;
		break;
	case '4':
		bKeyState[KS_D_MATRIX] = bState;
		break;
	case '5':
		bKeyState[KS_C_UFO] = bState;
		break;
	case '6':
		bKeyState[KS_C_ROBOT] = bState;
		break;
	case 'Q':
		bKeyState[KS_M_BACK] = bState;
		break;
	case 'E':
		bKeyState[KS_M_FRONT] = bState;
		break;
	case 'A':
		bKeyState[KS_M_LEFT] = bState;
		break;
	case 'D':
		bKeyState[KS_M_RIGHT] = bState;
		break;
	case 'W':
		bKeyState[KS_M_UP] = bState;
		break;
	case 'S':
		bKeyState[KS_M_DOWN] = bState;
		break;
	case 'U':
		bKeyState[KS_R_FRONT] = bState;
		break;
	case 'O':
		bKeyState[KS_R_BACK] = bState;
		break;
	case 'J':
		bKeyState[KS_R_LEFT] = bState;
		break;
	case 'L':
		bKeyState[KS_R_RIGHT] = bState;
		break;
	case 'I':
		bKeyState[KS_R_UP] = bState;
		break;
	case 'K':
		bKeyState[KS_R_DOWN] = bState;
		break;
	case '-':
	case '_':
	case 189:
		bKeyState[KS_S_N] = bState;
		break;
	case '+':
	case '=':
	case 187:
		bKeyState[KS_S_P] = bState;
		break;
	case '[':
		bKeyState[KS_M_STEP_N] = bState;
		break;
	case '{':
	case 219:
		bKeyState[KS_M_STEP_N] = bState;
		bKeyState[KS_R_STEP_N] = bState;
		break;
	case ']':
		bKeyState[KS_M_STEP_P] = bState;
		break;
	case '}':
	case 221:
		bKeyState[KS_M_STEP_P] = bState;
		bKeyState[KS_R_STEP_P] = bState;
		break;
	case ' ':
		bKeyState[KS_P] = bState;
		break;
	case VK_SHIFT:
		bKeyState[KS_SHIFT] = bState;
		break;
	case VK_UP:
		bKeyState[KS_F_UP] = bState;
		break;
	case VK_DOWN:
		bKeyState[KS_F_DOWN] = bState;
		break;
	case VK_LEFT:
		bKeyState[KS_F_LEFT] = bState;
		break;
	case VK_RIGHT:
		bKeyState[KS_F_RIGHT] = bState;
		break;
	default: return false;
	}
	KeyProcess();
	return true;
}

/**
 * \brief ���ļ��̺����Ŀ���״̬
 * \param key ���̿���״̬��0���䣬1��true��2��false
 * \param mouse ������״̬��0���䣬1��true��2��false
 */
void CControl966::SetAvialMode(int key, int mouse)
{
	if (key == 1)
	{
		bIsKeyAvail = true;
	}
	else if (key == 2)
	{
		bIsKeyAvail = false;
	}
	if (mouse == 1)
	{
		bIsMouseAvail = true;
	}
	else if (mouse == 2)
	{
		bIsMouseAvail = false;
	}
}


