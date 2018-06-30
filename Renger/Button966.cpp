#include "StdAfx.h"
#include "Button966.h"
#include "Renger.h"


CButton966::CButton966(void)
{
}

void CButton966::Set(int posx, int posy, int len, int bro)
{
}

bool CButton966::OnPress(int x, int y, RECT rect)
{
	return true;
}

bool CButton966::OnUp(int x, int y, RECT rect)
{
	return true;
}

CButton966::~CButton966(void)
{
}

CStartButton966::CStartButton966(COpenGL *pGL)
{
	pOpenGL = pGL;
	bIsPressed = false;
}

CStartButton966::~CStartButton966()
{
}

void CStartButton966::Set(int posx, int posy, int len, int bro)
{
	fPosx = posx;
	fPosy = posy;
	iLength = len;
	iBroad = bro;
	fTop = fPosy + iBroad / 2;
	fBottom = fPosy - iBroad / 2;
	fLeft = fPosx - iLength / 2;
	fRight = fPosx + iLength / 2;
}

bool CStartButton966::OnPress(int x, int y, RECT rect)
{
	int bro = rect.bottom - rect.top;
	y = bro - y;
	if (x > fLeft && x < fRight && y > fBottom && y < fTop)
	{
		bIsPressed = true;
		std::cout << "按下开始按钮" << std::endl;
	}
	return true;
}

bool CStartButton966::OnUp(int x, int y, RECT rect)
{
	int bro = rect.bottom - rect.top;
	y = bro - y;
	if (x > fLeft && x < fRight && y > fBottom && y < fTop)
	{
		std::cout << "抬起开始按钮" << std::endl;
		bIsPressed = false;
		pOpenGL->pCar->newGame();
		pOpenGL->pCamera->SetGameMode(1);
	}
	return true;
}

void CStartButton966::render(RECT rect)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int len = rect.right - rect.left;
	int bro = rect.bottom - rect.top;
	glOrtho(0, len, 0, bro, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	if (bIsPressed)
	{
		glBindTexture(GL_TEXTURE_2D, pOpenGL->STARTDOWN);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, pOpenGL->START);
	}
	glColor3b(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
    glVertex2d(fLeft, fTop);
	glTexCoord2f(0.0, 0.0);
    glVertex2d(fLeft, fBottom);
	glTexCoord2f(1.0, 0.0);
    glVertex2d(fRight, fBottom);
	glTexCoord2f(1.0, 1.0);
    glVertex2d(fRight, fTop);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}

CEndButton966::CEndButton966(COpenGL *pGL)
{
	pOpenGL = pGL;
	bIsPressed = false;
}

CEndButton966::~CEndButton966()
{
}

void CEndButton966::Set(int posx, int posy, int len, int bro)
{
	fPosx = posx;
	fPosy = posy;
	iLength = len;
	iBroad = bro;
	fTop = fPosy + iBroad / 2;
	fBottom = fPosy - iBroad / 2;
	fLeft = fPosx - iLength / 2;
	fRight = fPosx + iLength / 2;
}

bool CEndButton966::OnPress(int x, int y, RECT rect)
{
	int bro = rect.bottom - rect.top;
	y = bro - y;
	if (x > fLeft && x < fRight && y > fBottom && y < fTop)
	{
		bIsPressed = true;
		std::cout << "按下结束按钮" << std::endl;
	}
	return true;
}

bool CEndButton966::OnUp(int x, int y, RECT rect)
{
	int bro = rect.bottom - rect.top;
	y = bro - y;
	if (x > fLeft && x < fRight && y > fBottom && y < fTop)
	{

		std::cout << "抬起结束按钮" << std::endl;
		bIsPressed = false;
		::PostMessage(AfxGetMainWnd()->m_hWnd,WM_CLOSE,0,0);
	}
	return true;
}

void CEndButton966::render(RECT rect)
{
	int e;
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	e = glGetError();
	int len = rect.right - rect.left;
	int bro = rect.bottom - rect.top;
	glOrtho(0, len, 0, bro, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	if (bIsPressed)
	{
		glBindTexture(GL_TEXTURE_2D, pOpenGL->ENDDOWN);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, pOpenGL->END);
	}
	glColor3b(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
    glVertex2d(fLeft, fTop);
	glTexCoord2f(0.0, 0.0);
    glVertex2d(fLeft, fBottom);
	glTexCoord2f(1.0, 0.0);
    glVertex2d(fRight, fBottom);
	glTexCoord2f(1.0, 1.0);
    glVertex2d(fRight, fTop);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	e = glGetError();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}


CRestartButton966::CRestartButton966(COpenGL *pGL)
{
	pOpenGL = pGL;
	bIsPressed = false;
}

CRestartButton966::~CRestartButton966()
{
}

void CRestartButton966::Set(int posx, int posy, int len, int bro)
{
	fPosx = posx;
	fPosy = posy;
	iLength = len;
	iBroad = bro;
	fTop = fPosy + iBroad / 2;
	fBottom = fPosy - iBroad / 2;
	fLeft = fPosx - iLength / 2;
	fRight = fPosx + iLength / 2;
}

bool CRestartButton966::OnPress(int x, int y, RECT rect)
{
	int bro = rect.bottom - rect.top;
	y = bro - y;
	if (x > fLeft && x < fRight && y > fBottom && y < fTop)
	{
		bIsPressed = true;
		std::cout << "按下重新开始按钮" << std::endl;
	}
	return true;
}

bool CRestartButton966::OnUp(int x, int y, RECT rect)
{
	int bro = rect.bottom - rect.top;
	y = bro - y;
	if (x > fLeft && x < fRight && y > fBottom && y < fTop)
	{
		std::cout << "抬起重新开始按钮" << std::endl;
		bIsPressed = false;
		pOpenGL->pCar->newGame();
		pOpenGL->pCamera->SetGameMode(1);
	}
	return true;
}

void CRestartButton966::render(RECT rect)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int len = rect.right - rect.left;
	int bro = rect.bottom - rect.top;
	glOrtho(0, len, 0, bro, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	if (bIsPressed)
	{
		glBindTexture(GL_TEXTURE_2D, pOpenGL->RESTARTDOWN);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, pOpenGL->RESTART);
	}
	glColor3b(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
    glVertex2d(fLeft, fTop);
	glTexCoord2f(0.0, 0.0);
    glVertex2d(fLeft, fBottom);
	glTexCoord2f(1.0, 0.0);
    glVertex2d(fRight, fBottom);
	glTexCoord2f(1.0, 1.0);
    glVertex2d(fRight, fTop);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}

