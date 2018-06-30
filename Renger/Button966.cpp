#include "StdAfx.h"
#include "Button966.h"


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

CStartButton966::CStartButton966(void)
{
	
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
	}
	return true;
}

void CStartButton966::render(RECT rect)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int len = rect.right - rect.left;
	int bro = rect.bottom - rect.top;
	glOrtho(0, len, 0, bro, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3b(0, 0, 0);
	glPolygonMode(GL_FRONT, GL_FILL); 
	glBegin(GL_POLYGON);              
    glVertex2d(fLeft, fTop);
    glVertex2d(fLeft, fBottom);
    glVertex2d(fRight, fBottom);
    glVertex2d(fRight, fTop);
	glEnd();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}

CEndButton966::CEndButton966(void)
{
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
	}
	return true;
}

void CEndButton966::render(RECT rect)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int len = rect.right - rect.left;
	int bro = rect.bottom - rect.top;
	glOrtho(0, len, 0, bro, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3b(0, 0, 0);
	glPolygonMode(GL_FRONT, GL_FILL); 
	glBegin(GL_POLYGON);              
    glVertex2d(fLeft, fTop);
    glVertex2d(fLeft, fBottom);
    glVertex2d(fRight, fBottom);
    glVertex2d(fRight, fTop);
	glEnd();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}


CRestartButton966::CRestartButton966(void)
{
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
	}
	return true;
}

void CRestartButton966::render(RECT rect)
{
	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int len = rect.right - rect.left;
	int bro = rect.bottom - rect.top;
	glOrtho(0, len, 0, bro, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3b(0, 0, 0);
	glPolygonMode(GL_FRONT, GL_FILL); 
	glBegin(GL_POLYGON);              
    glVertex2d(fLeft, fTop);
    glVertex2d(fLeft, fBottom);
    glVertex2d(fRight, fBottom);
    glVertex2d(fRight, fTop);
	glEnd();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}
