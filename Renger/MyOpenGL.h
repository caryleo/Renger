#pragma once
#include "stdafx.h"
#include "opengl/OpenGL.h"
#include <gl/GLAux.h>
#pragma comment(lib, "GLAUX.lib")
#define POINTNUM 200
#define CIRCLENUM 20

class CMyOpenGL : public COpenGL
{
public:
	CMyOpenGL(void);
	~CMyOpenGL(void);
	void DrawRobot();
	void DrawUfo();
	void DrawAxes();
	void DrawBall(GLfloat radius,int lon,int lat);
	void Normalize(GLfloat *v);
	bool GetTexture();
	void DrawBox(float size);
	void CMyOpenGL::CalculateNormal(GLfloat v1[],GLfloat v2[],GLfloat v3[],GLfloat normal[]);
	virtual void PostInit(void);
	virtual void InDraw(void);
	virtual bool OnKey(unsigned char nChar, bool bDown);
	virtual void Update();
};

