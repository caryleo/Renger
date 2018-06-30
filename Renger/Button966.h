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
	CStartButton966(COpenGL *pGL);
	~CStartButton966(void);
	virtual void Set(int posx, int posy, int len, int bro);
	virtual bool OnPress(int x, int y, RECT rect);
	virtual bool OnUp(int x, int y, RECT rect);
	void render(RECT rect);
private:
	COpenGL *pOpenGL;
};

class CEndButton966: public CButton966
{
public:
	CEndButton966(COpenGL *pGL);
	~CEndButton966(void);
	virtual void Set(int posx, int posy, int len, int bro);
	virtual bool OnPress(int x, int y, RECT rect);
	virtual bool OnUp(int x, int y, RECT rect);
	void render(RECT rect);
private:
	COpenGL *pOpenGL;
};

class CRestartButton966: public CButton966
{
public:
	CRestartButton966(COpenGL *pGL);
	~CRestartButton966(void);
	virtual void Set(int posx, int posy, int len, int bro);
	virtual bool OnPress(int x, int y, RECT rect);
	virtual bool OnUp(int x, int y, RECT rect);
	void render(RECT rect);
private:
	COpenGL *pOpenGL;
};
