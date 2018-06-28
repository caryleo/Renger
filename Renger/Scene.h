#pragma once
#include "stdafx.h"
#include "ModelLoader.h"
#define  BITMAP_ID 0x4D42 /**< λͼ�ļ��ı�־ */


class CBMPLoader;
class CSkyBox;
class CTerrain;
class CParticle;
class CSnow;
class CScene;

//////////////////////////////////////////////////////////////////////////
//
// CBMPLoader
//
//////////////////////////////////////////////////////////////////////////
class CBMPLoader
{
public:

	CBMPLoader(void);
	~CBMPLoader(void);
	bool LoadBitmap(const char *filename); /**< װ��һ��bmp�ļ� */
	void FreeImage();                /**< �ͷ�ͼ������ */
	bool Load(const char* fileName);       /**< ����λͼ���������� */

	unsigned int ID;                 /**< ���������ID�� */
	int imageWidth;                  /**< ͼ���� */
	int imageHeight;                 /**< ͼ��߶� */
	unsigned char *image;            /**< ָ��ͼ�����ݵ�ָ�� */
};
//////////////////////////////////////////////////////////////////////////
//
// CSkyBox
//
//////////////////////////////////////////////////////////////////////////
/** ��պ��� */
class CSkyBox : public COpenGL
{
public:
	CSkyBox(void);
	~CSkyBox(void);
	/** ��ʼ�� */
	bool init();

	/** ��Ⱦ */
	void render();
private:

	CBMPLoader  m_texture[5];   /**< ��պ�����   */
	CVector966  m_CameraPos;    /**< ��ǰ�����λ�� */
	float       length;         /**< ���� */
	float       width;          /**< ��� */
	float       height;         /**< �߶� */
	float       yRot;           /**< ��Y����ת */
	CVector966 m_Position;
};

//////////////////////////////////////////////////////////////////////////
//
// CTerrain
//
//////////////////////////////////////////////////////////////////////////
/** ������ */
class CTerrain
{
public:
	/** ���캯�� */
	CTerrain();

	~CTerrain();

	/** ��ʼ������ */
	bool init();

	/** ��Ⱦ���� */
	void render();

	/** �����Ƿ�ʹ��ϸ�������־ */ 
	void setDetail(bool _bDetail) { m_bDetail = _bDetail;}

	/** ��õ���߶� */
	float getAveHeight(float x, float z);

	/** �õ���ǰTerrainָ�� */
	static CTerrain* GetTerrainPointer() { return m_pTerrain;}


private:

	/** ���õ��εĴ�С */
	void setSize(unsigned  int width, unsigned  int cell); 

	/** ����'.raw'�߶�ͼ */
	bool loadRawFile(const char* fileName);

	/** װ������ */
	bool loadTexture();

	/** ��õ�(x,y)�ĸ߶���Ϣ */
	int getHeight(int x, int y);

	/** ������������ */
	void setTexCoord(float x, float z);

	/** ������Ч */
	void initFog();



public:
	static CTerrain*  m_pTerrain;        /**< ��ǰTerrainָ�� */
	unsigned  int     m_nWidth;          /**< ���������� */
	unsigned  int     m_nCellWidth;      /**< ÿһ���� */
	BYTE*             m_pHeightMap;      /**< ��Ÿ߶���Ϣ */
	CBMPLoader        m_texture[2];      /**< ���������ϸ������ */
	bool              m_bDetail;         /**< �Ƿ�ʹ��ϸ�������־ */
	int               m_DetailScale;     /**< ���ű��� */

};

//////////////////////////////////////////////////////////////////////////
//
// CParticle
//
//////////////////////////////////////////////////////////////////////////
/** ���ӽṹ */
struct Particle
{
	CVector966   position;		       /**< ���ӵ�λ�� */

	CVector966   velocity;            /**< ���ӵ��ٶ� */

	CVector966   acceleration;        /**< ���ӵļ��ٶ� */

	float     lifetime;            /**< ��������ֵ */

	float     dec;		           /**< ������ʧ���ٶ� */

	float     size;		           /**< ���ӳߴ� */

	float     color[3];            /**< ���ӵ���ɫ */

};


/** ������ */
class CParticle
{

public:

	CParticle();                  /**< ���캯�� */

	virtual ~CParticle();         /**< �������� */

	/** ���ӵĳ�ʼ�� */
	virtual bool Init(int _num);

	/** ���ӵ���Ⱦ */
	virtual void Render() = 0;

	/** ���ӵĸ��� */
	virtual void Update() = 0;

protected:

	int           m_iNum;	              /**< ��������Ŀ */
	Particle*     m_pList;				  /**< ����ָ�� */

};
//////////////////////////////////////////////////////////////////////////
//
// CSnow
//
//////////////////////////////////////////////////////////////////////////
/** ѩ����Ⱦ�� */
class CSnow : public CParticle
{

public:
	CSnow()  {};
	~CSnow() {};

	bool		Init(int num );  /** ��ʼ������ */
	void		Render();        /**< ��Ⱦ���� */
	void		Update();        /**< ���¹��� */

private:
	CBMPLoader  m_texture;       /**< ���ӵ����� */


}; 

//////////////////////////////////////////////////////////////////////////
//
// CScene
//
//////////////////////////////////////////////////////////////////////////
class CScene
{
public:
	CScene()  {IsInit=false;};
	~CScene() {};
	void Render();/**< ������Ⱦ */
	void init();

	CSkyBox m_SkyBox;
	CTerrain m_Terrain;
	CSnow m_Snow;
	bool IsInit;
};