#pragma once
#include "stdafx.h"
#include "opengl/OpenGL.h"
#include "opengl/Scene.h"
#include <gl/GLAux.h>
#include "Button966.h"
#pragma comment(lib, "GLAUX.lib")
#define POINTNUM 200
#define CIRCLENUM 20

class CMyOpenGL : public COpenGL
{
public:
	CMyOpenGL(void);
	~CMyOpenGL(void);
	void DrawAxes(int size);
	void changeGothicTrans(float trans[],double x,double y,double z,double a,double b,double c,double r,double _x,double _y,double _z);
	void drawHulan();
	void hulanInit(); 
	int power_of_two(int n);
	GLuint load_texture(const char* file_name);
	void drawRoad(double x,double z);
	void drawAllRoad();
	void drawArrow();
	virtual void PostInit(void);
	virtual void InDraw(void);
	virtual bool OnKey(unsigned char nChar, bool bDown);
	virtual void Update();
	
};

