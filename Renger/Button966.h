#pragma once
class CButton966
{
public:
	CButton966(void);
	virtual bool OnPress(int x, int y);
	virtual ~CButton966(void);
private:
	//ƽ��ͶӰ���ĸ����������
	float fTop, fLeft, fBottom, fRight;
	//�ж��Ƿ񱻰���
	bool bIsPressed;
	//�ж��Ƿ�Hover
	bool bIsHovered;

};

