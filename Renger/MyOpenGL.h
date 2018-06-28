#pragma once
#include "stdafx.h"
#include "opengl/OpenGL.h"
#include "Scene.h"
#include <gl/GLAux.h>
#pragma comment(lib, "GLAUX.lib")
#define POINTNUM 200
#define CIRCLENUM 20

class CMyOpenGL : public COpenGL
{
public:
	CMyOpenGL(void);
	~CMyOpenGL(void);
	void DrawAxes();
	virtual void PostInit(void);
	virtual void InDraw(void);
	virtual bool OnKey(unsigned char nChar, bool bDown);
	virtual void Update();
	CScene scene;
};

