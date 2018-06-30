#pragma once
class CButton966
{
public:
	CButton966(void);
	virtual void Set(int posx, int posy, int len, int bro);
	virtual bool OnPress(int x, int y, RECT rect);
	virtual bool OnUp(int x, int y, RECT rect);
	virtual ~CButton966(void);
protected:
	//ƽ��ͶӰ���ĸ����������
	int fTop, fLeft, fBottom, fRight;
	//λ�úͰ�ť�ĳ���
	int fPosx, fPosy;
	int iLength, iBroad;
	//�ж��Ƿ񱻰���
	bool bIsPressed;
	//�ж��Ƿ�Hover
	bool bIsHovered;

};

class CStartButton966: public CButton966
{
public:
	CStartButton966(void);
	~CStartButton966(void);
	virtual void Set(int posx, int posy, int len, int bro);
	virtual bool OnPress(int x, int y, RECT rect);
	virtual bool OnUp(int x, int y, RECT rect);
	void render(RECT rect);
};

class CEndButton966: public CButton966
{
public:
	CEndButton966(void);
	~CEndButton966(void);
	virtual void Set(int posx, int posy, int len, int bro);
	virtual bool OnPress(int x, int y, RECT rect);
	virtual bool OnUp(int x, int y, RECT rect);
	void render(RECT rect);
};

class CRestartButton966: public CButton966
{
public:
	CRestartButton966(void);
	~CRestartButton966(void);
	virtual void Set(int posx, int posy, int len, int bro);
	virtual bool OnPress(int x, int y, RECT rect);
	virtual bool OnUp(int x, int y, RECT rect);
	void render(RECT rect);
};
