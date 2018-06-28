#pragma once
#include "stdafx.h"
#include "ModelLoader.h"
#define  BITMAP_ID 0x4D42 /**< 位图文件的标志 */


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
	bool LoadBitmap(const char *filename); /**< 装载一个bmp文件 */
	void FreeImage();                /**< 释放图像数据 */
	bool Load(const char* fileName);       /**< 载入位图并创建纹理 */

	unsigned int ID;                 /**< 生成纹理的ID号 */
	int imageWidth;                  /**< 图像宽度 */
	int imageHeight;                 /**< 图像高度 */
	unsigned char *image;            /**< 指向图像数据的指针 */
};
//////////////////////////////////////////////////////////////////////////
//
// CSkyBox
//
//////////////////////////////////////////////////////////////////////////
/** 天空盒类 */
class CSkyBox : public COpenGL
{
public:
	CSkyBox(void);
	~CSkyBox(void);
	/** 初始化 */
	bool init();

	/** 渲染 */
	void render();
private:

	CBMPLoader  m_texture[5];   /**< 天空盒纹理   */
	CVector966  m_CameraPos;    /**< 当前摄像机位置 */
	float       length;         /**< 长度 */
	float       width;          /**< 宽度 */
	float       height;         /**< 高度 */
	float       yRot;           /**< 绕Y轴旋转 */
	CVector966 m_Position;
};

//////////////////////////////////////////////////////////////////////////
//
// CTerrain
//
//////////////////////////////////////////////////////////////////////////
/** 地形类 */
class CTerrain
{
public:
	/** 构造函数 */
	CTerrain();

	~CTerrain();

	/** 初始化地形 */
	bool init();

	/** 渲染地形 */
	void render();

	/** 设置是否使用细节纹理标志 */ 
	void setDetail(bool _bDetail) { m_bDetail = _bDetail;}

	/** 获得地面高度 */
	float getAveHeight(float x, float z);

	/** 得到当前Terrain指针 */
	static CTerrain* GetTerrainPointer() { return m_pTerrain;}


private:

	/** 设置地形的大小 */
	void setSize(unsigned  int width, unsigned  int cell); 

	/** 载入'.raw'高度图 */
	bool loadRawFile(const char* fileName);

	/** 装载纹理 */
	bool loadTexture();

	/** 获得点(x,y)的高度信息 */
	int getHeight(int x, int y);

	/** 设置纹理坐标 */
	void setTexCoord(float x, float z);

	/** 设置雾效 */
	void initFog();



public:
	static CTerrain*  m_pTerrain;        /**< 当前Terrain指针 */
	unsigned  int     m_nWidth;          /**< 地形网格数 */
	unsigned  int     m_nCellWidth;      /**< 每一格宽度 */
	BYTE*             m_pHeightMap;      /**< 存放高度信息 */
	CBMPLoader        m_texture[2];      /**< 地面纹理和细节纹理 */
	bool              m_bDetail;         /**< 是否使用细节纹理标志 */
	int               m_DetailScale;     /**< 缩放比例 */

};

//////////////////////////////////////////////////////////////////////////
//
// CParticle
//
//////////////////////////////////////////////////////////////////////////
/** 粒子结构 */
struct Particle
{
	CVector966   position;		       /**< 粒子的位置 */

	CVector966   velocity;            /**< 粒子的速度 */

	CVector966   acceleration;        /**< 粒子的加速度 */

	float     lifetime;            /**< 粒子生命值 */

	float     dec;		           /**< 粒子消失的速度 */

	float     size;		           /**< 粒子尺寸 */

	float     color[3];            /**< 粒子的颜色 */

};


/** 粒子类 */
class CParticle
{

public:

	CParticle();                  /**< 构造函数 */

	virtual ~CParticle();         /**< 析构函数 */

	/** 粒子的初始化 */
	virtual bool Init(int _num);

	/** 粒子的渲染 */
	virtual void Render() = 0;

	/** 粒子的更新 */
	virtual void Update() = 0;

protected:

	int           m_iNum;	              /**< 粒子总数目 */
	Particle*     m_pList;				  /**< 粒子指针 */

};
//////////////////////////////////////////////////////////////////////////
//
// CSnow
//
//////////////////////////////////////////////////////////////////////////
/** 雪花渲染类 */
class CSnow : public CParticle
{

public:
	CSnow()  {};
	~CSnow() {};

	bool		Init(int num );  /** 初始化过程 */
	void		Render();        /**< 渲染过程 */
	void		Update();        /**< 更新过程 */

private:
	CBMPLoader  m_texture;       /**< 粒子的纹理 */


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
	void Render();/**< 场景渲染 */
	void init();

	CSkyBox m_SkyBox;
	CTerrain m_Terrain;
	CSnow m_Snow;
	bool IsInit;
};