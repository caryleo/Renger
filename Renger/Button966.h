#pragma once
class CButton966
{
public:
	CButton966(void);
	virtual bool OnPress(int x, int y);
	virtual ~CButton966(void);
private:
	//平行投影下四个顶点的坐标
	float fTop, fLeft, fBottom, fRight;
	//判断是否被按下
	bool bIsPressed;
	//判断是否被Hover
	bool bIsHovered;

};

