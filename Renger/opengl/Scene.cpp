#include "Scene.h"
#include "stdafx.h"
#include <afxver_.h>


//////////////////////////////////////////////////////////////////////////
//
// CBMPLoader
//
//////////////////////////////////////////////////////////////////////////
/** 构造函数 */
CBMPLoader::CBMPLoader()
{
	/** 初始化成员值为0 */
	image = 0;
	imageWidth = 0;
	imageHeight = 0;
}

/** 析构函数 */
CBMPLoader::~CBMPLoader()
{
	FreeImage(); /**< 释放图像数据占据的内存 */
}

/** 装载一个位图文件 */
bool CBMPLoader::LoadBitmap(const char *file)
{
	FILE *pFile = 0; /**< 文件指针 */

	/** 创建位图文件信息和位图文件头结构 */
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER header;

	unsigned char textureColors = 0;/**< 用于将图像颜色从BGR变换到RGB */

	/** 打开文件,并检查错误 */
	pFile = fopen(file, "rb");
	if(pFile == 0) return false;

	/** 读入位图文件头信息 */ 
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);

	/** 检查该文件是否为位图文件 */
	if(header.bfType != BITMAP_ID)
	{
		fclose(pFile);             /**< 若不是位图文件,则关闭文件并返回 */
		return false;
	}

	/** 读入位图文件信息 */
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

	/** 保存图像的宽度和高度 */
	imageWidth = bitmapInfoHeader.biWidth;
	imageHeight = bitmapInfoHeader.biHeight;

	/** 确保读取数据的大小 */
	if(bitmapInfoHeader.biSizeImage == 0)
		bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth *
		bitmapInfoHeader.biHeight * 3;

	/** 将指针移到数据开始位置 */
	fseek(pFile, header.bfOffBits, SEEK_SET);

	/** 分配内存 */
	image = new unsigned char[bitmapInfoHeader.biSizeImage];

	/** 检查内存分配是否成功 */
	if(!image)                        /**< 若分配内存失败则返回 */
	{
		delete[] image;
		fclose(pFile);
		return false;
	}

	/** 读取图像数据 */
	fread(image, 1, bitmapInfoHeader.biSizeImage, pFile);

	/** 将图像颜色数据格式进行交换,由BGR转换为RGB */
	for(int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index+=3)
	{
		textureColors = image[index];
		image[index] = image[index + 2];
		image[index + 2] = textureColors;
	}

	fclose(pFile);       /**< 关闭文件 */
	return true;         /**< 成功返回 */
}

/** 载入位图文件，并创建纹理 */
bool CBMPLoader::Load(const char* fileName)
{
	if(!LoadBitmap(fileName))
	{
		MessageBox(NULL,"载入位图文件失败!","错误",MB_OK);
		exit(0);
	}

	/** 生成纹理对象名称 */
	glGenTextures(1, &ID);

	/** 创建纹理对象 */
	glBindTexture(GL_TEXTURE_2D, ID);

	/** 控制滤波 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	/** 创建纹理 */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageWidth,
		imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		image);
	return true;
}

/** 释放内存 */
void CBMPLoader::FreeImage()
{
	/** 释放分配的内存 */
	if(image)
	{
		delete[] image;
		image = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
//
// CSkyBox
//
//////////////////////////////////////////////////////////////////////////

CSkyBox::CSkyBox():length(750.0f),width(550.0f),height(400.0f),yRot(0.01f)
{	
}

CSkyBox::~CSkyBox()
{
	/** 删除纹理对象及其占用的内存 */
	for(int i =0 ;i< 5; i++)
	{
		m_texture[i].FreeImage();
		glDeleteTextures(1,&m_texture[i].ID);
	}

}

/** 天空盒初始化 */
bool CSkyBox::init()
{
	char filename[128] ;                                         /**< 用来保存文件名 */
	char *bmpName[] = { "back","front","top","left","right"};
	for(int i=0; i< 5; i++)
	{
		sprintf(filename,"data/%s",bmpName[i]);
		strcat(filename,".bmp");
		if(!m_texture[i].LoadBitmap(filename))                     /**< 载入位图文件 */
		{
			MessageBox(NULL,"装载位图文件失败！","错误",MB_OK);    /**< 如果载入失败则弹出对话框 */
			exit(0);
		}
		glGenTextures(1, &m_texture[i].ID);                        /**< 生成一个纹理对象名称 */

		glBindTexture(GL_TEXTURE_2D, m_texture[i].ID);             /**< 创建纹理对象 */
		/** 控制滤波 */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		/** 创建纹理 */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture[i].imageWidth,
			m_texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
			m_texture[i].image);
	}
	return true;

}

void CSkyBox::render()
{
	/** 获得场景中光照状态 */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING,&lp);

	glDisable(GL_LIGHTING);            /**< 关闭光照 */
	glEnable(GL_TEXTURE_2D);

	/** 开始绘制 */
	glPushMatrix();
	glTranslatef(500,35,400);

	glRotatef(yRot,0.0f,1.0f,0.0f);

	/** 绘制背面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);
	glBegin(GL_QUADS);		

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(  width, -height, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(  width,  height, -length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f( -width,  height, -length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( -width, -height, -length);

	glEnd();



	/** 绘制前面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);
	glBegin(GL_QUADS);	

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f( -width, -height, length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( -width,  height, length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(  width,  height, length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(  width, -height, length);

	glEnd();



	/** 绘制顶面 */
	glBindTexture(GL_TEXTURE_2D,  m_texture[2].ID);
	glBegin(GL_QUADS);		

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(  width, height, -length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(  width, height,  length); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f( -width, height,  length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( -width, height, -length);

	glEnd();



	/** 绘制左面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[3].ID);
	glBegin(GL_QUADS);		

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 1.0f);  glVertex3f( -width,  height,	-length);		
	glTexCoord2f(0.0f, 1.0f);  glVertex3f( -width,  height,  length); 
	glTexCoord2f(0.0f, 0.0f);  glVertex3f( -width, -height,  length);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f( -width, -height, -length);	

	glEnd();

	/** 绘制右面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[4].ID);
	glBegin(GL_QUADS);		

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f( width, -height, -length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( width, -height,  length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( width,  height,  length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f( width,  height, -length);
	glEnd();


	glPopMatrix();                 /** 绘制结束 */

	if(lp)                         /** 恢复光照状态 */  
		glEnable(GL_LIGHTING);

	glDisable(GL_TEXTURE_2D);

	yRot += 0.01f;
	if(yRot > 360.0f)
		yRot = 0.0f;
}

//////////////////////////////////////////////////////////////////////////
//
// CTerrain
//
//////////////////////////////////////////////////////////////////////////
//** 当前CTerrain指针 */
CTerrain* CTerrain::m_pTerrain = NULL;


///** 多重纹理函数指针 */
PFNGLMULTITEXCOORD2FARBPROC	glMultiTexCoord2fARB=NULL;
PFNGLACTIVETEXTUREARBPROC	glActiveTextureARB=NULL;


/** 构造函数 */
CTerrain::CTerrain():m_bDetail(true),m_DetailScale(128)
{
	/** 设置地形大小 */
	setSize(MAP_WIDTH,CELL_WIDTH);

	/** 为地形高程分配内存,并初始化 */
	m_pHeightMap = new BYTE[m_nWidth * m_nWidth];
	for(int i=0; i<m_nWidth * m_nWidth; i++)
		m_pHeightMap[i] = 0;

	m_pTerrain = this;

}

/** 析构函数 */
CTerrain::~CTerrain()
{
	/** 删除内存和指针 */
	if(m_pHeightMap)
	{
		delete[] m_pHeightMap;
		m_pHeightMap = 0;
	}

	/** 删除纹理对象及其占用内存 */	
	for(int i=0; i<2; i++)
	{
		m_texture[i].FreeImage();
		glDeleteTextures(1,&m_texture[i].ID);
	}


}

/** 初始化雾效 */
void CTerrain::initFog()
{
	float fogColor[4] = { 0.8f,0.8f,0.8f,1.0f };

	glEnable(GL_FOG);

	glFogi(GL_FOG_MODE,GL_EXP);             /** 设置雾效的模式 */
	glFogfv(GL_FOG_COLOR,fogColor);         /** 指定雾的颜色 */ 
	glFogf(GL_FOG_DENSITY,0.001f);          /** 设置雾的浓度 */
	glFogf(GL_FOG_START,1.0);               /** 设置线性雾的开始位置 */
	glFogf(GL_FOG_END,1000.0);              /** 设置线性雾的结束位置 */
	glHint(GL_FOG_HINT,GL_DONT_CARE);       /** 规定雾化效果的质量 */ 

}


/** 初始化地形 */
bool CTerrain::init()
{

	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");

	if(!glActiveTextureARB || !glMultiTexCoord2fARB)
	{
		//输出错误信息
		MessageBox(NULL, "不支持多重纹理！", "错误", MB_OK);
		exit(0);
		//setDetail(false);
	}

	/** 载入高度文件 */
	loadRawFile("data/terrain.raw");

	/** 载入纹理 */
	loadTexture();

	/** 初始化雾效 */
	initFog();

	return true;
}

/** 设置地形大小 */
void CTerrain::setSize(unsigned  int width, unsigned  int cell)
{
	m_nWidth = width;
	m_nCellWidth = cell; 
}

/** 获得高度图中高度值 */
int CTerrain::getHeight(int x,int y)
{
	if(!m_pHeightMap)
		return 0;
	int xx = x % m_nWidth;
	int yy = y % m_nWidth;
	/** 返回当前高度 */
	return m_pHeightMap[(xx + yy * m_nWidth)];
}

/** 获得地面高度 */
float CTerrain::getAveHeight(float x,float z)
{
	float CameraX, CameraZ;

	CameraX = x / m_nCellWidth;
	CameraZ = z / m_nCellWidth;

	/** 计算高程坐标(Col0, Row0)，(Col1, Row1) */
	int col0 = int(CameraX);
	int row0 = int(CameraZ);
	unsigned int col1 = col0 + 1;
	unsigned int row1 = row0 + 1;

	/** 确保单元坐标不超过高程以外 */
	if (col1 > m_nWidth) col1 = 0;
	if (row1 > m_nWidth) row1 = 0;

	/** 获取单元的四个角的高度 */
	float h00 = (float)(m_pHeightMap[col0*m_nCellWidth + row0*m_nCellWidth*m_nWidth]);
	float h01 = (float)(m_pHeightMap[col1*m_nCellWidth + row0*m_nCellWidth*m_nWidth]);
	float h11 = (float)(m_pHeightMap[col1*m_nCellWidth + row1*m_nCellWidth*m_nWidth]);
	float h10 = (float)(m_pHeightMap[col0*m_nCellWidth + row1*m_nCellWidth*m_nWidth]);

	/** 计算机摄像机相对于单元格的位置 */
	float tx = CameraX - int(CameraX);
	float ty = CameraZ - int(CameraZ);

	/** 进行双线性插值得到地面高度 */
	float txty = tx * ty;

	float final_height	= h00 * (1.0f - ty - tx + txty)
		+ h01 * (tx - txty)
		+ h11 * txty
		+ h10 * (ty - txty);
	return final_height;
}

/** 载入高度图 */
bool CTerrain::loadRawFile(const char* fileName)
{
	FILE *pFile = NULL;

	/** 打开文件 */
	pFile = fopen( fileName, "rb" );

	/** 错误检查 */
	if ( pFile == NULL )
	{
		/** 输出错误信息，并返回false */
		MessageBox(NULL, "打开高度图文件失败！", "错误", MB_OK);
		exit(0);
	}

	/** 读取高度图文件 */
	fread( m_pHeightMap, 1, m_nWidth*m_nWidth, pFile );

	/** 获取错误代码 */
	int result = ferror( pFile );

	/** 检查错误代码 */
	if (result)
	{
		MessageBox(NULL, "无法获取高度数据！", "错误", MB_OK);
		exit(0);
	}

	/** 关闭文件，成功返回 */
	fclose(pFile);
	return true;
}

/** 设置纹理坐标 */
void CTerrain::setTexCoord(float x,float z)
{

	float u =  (float)x / (float)m_nWidth;
	float v = -(float)z / (float)m_nWidth;

	///设置地面纹理的纹理坐标
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, u, v);

	///设置细节纹理的纹理坐标
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, u, v);
}


/** 载入地面纹理 */
bool CTerrain::loadTexture()
{
	char* fileName[] = {"data/terrain.bmp","data/detail.bmp"};	
	for(int i=0; i < 2; i++)
	{
		if(!m_texture[i].LoadBitmap(fileName[i]) )                    /**< 载入位图文件 */
		{
			MessageBox(NULL,"装载位图文件失败！","错误",MB_OK);       /**< 如果载入失败则弹出对话框 */
			exit(0);
		}
		glGenTextures(1, &m_texture[i].ID);                            /**< 生成一个纹理对象名称 */


		glBindTexture(GL_TEXTURE_2D, m_texture[i].ID);                 /**< 创建纹理对象 */

		/** 控制滤波 */
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

		/** 创建纹理 */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture[i].imageWidth,
			m_texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
			m_texture[i].image);
	}

	return true;

}

/** 渲染地形 */
void CTerrain::render()
{

	int X = 0, Y = 0;						
	float x, y, z;							
	bool bSwitchSides = false;

	/** 检查高度图是否有效 */
	if(!m_pHeightMap) 
		return;					

	/** 绑定纹理 */

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);

	/** 渲染细节纹理 */
	if(m_bDetail)
	{
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

		glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);

		/** 变换纹理矩阵 */
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glScalef((float)m_DetailScale, (float)m_DetailScale, 1);
		glMatrixMode(GL_MODELVIEW);
	}

	/** 绘制三角形带 */
	glBegin( GL_TRIANGLE_STRIP );			

	/** 从行(X)开始循环 */
	for ( X = 0; X <= m_nWidth; X += m_nCellWidth )
	{
		/** 检查该列是否需要从相反顺序绘制 */
		if(bSwitchSides)
		{	
			/** 绘制地形的一列 */
			for ( Y = m_nWidth; Y >= 0; Y -= m_nCellWidth )
			{
				/** 顶点(X, Y, Z) */		
				x = X;							
				y = getHeight( X, Y );	
				z = Y;							

				/** 指定纹理坐标,并发送顶点 */
				//setFogCoord(m_FogDepth, (float)y);
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);		

				/** 顶点(X + m_nCellWidth, Y, Z) */		
				x = X + m_nCellWidth; 
				y = getHeight( X + m_nCellWidth, Y ); 
				z = Y;

				/** 指定纹理坐标,并发送顶点 */
				//setFogCoord(m_FogDepth, (float)y);
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);			
			}
		}
		else
		{	
			/** 绘制地形的一列 */
			for ( Y = 0; Y <= m_nWidth; Y += m_nCellWidth )
			{
				/** 顶点(X + m_nCellWidth, Y, Z) */	
				x = X + m_nCellWidth; 
				y = getHeight( X + m_nCellWidth, Y ); 
				z = Y;

				/** 指定纹理坐标,并发送顶点 */
				//setFogCoord(m_FogDepth, (float)y);
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);

				/** 顶点 (X, Y, Z) */		
				x = X;							
				y = getHeight( X, Y );	
				z = Y;							

				/** 指定纹理坐标,并发送顶点 */
				//setFogCoord(m_FogDepth, (float)y);
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);		
			}
		}

		/** 变换开关 */
		bSwitchSides = !bSwitchSides;
	}

	/** 绘制结束 */
	glEnd();

	///关闭纹理单元1
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);

	//关闭纹理单元0
	glActiveTextureARB(GL_TEXTURE0_ARB);		
	glDisable(GL_TEXTURE_2D);

}

//////////////////////////////////////////////////////////////////////////
//
// CParticle
//
//////////////////////////////////////////////////////////////////////////

/** 构造函数 */
CParticle::CParticle():m_iNum(0),m_pList(NULL)
{	
}

/** 析构函数 */
CParticle::~CParticle()
{
	if(m_pList != NULL)
	{
		delete []m_pList;
		m_pList = NULL;
	}

}

/** 粒子的初始化 */
bool CParticle::Init(int _num)
{
	m_iNum = _num;
	m_pList = new Particle[m_iNum];
	if(m_pList == NULL)
		return false;
	return true;
}

/** 粒子的渲染 */
void CParticle::Render()
{
}

/** 粒子的更新 */
void CParticle::Update()
{
}

//////////////////////////////////////////////////////////////////////////
//
// CSnow
//
//////////////////////////////////////////////////////////////////////////

/** 雪花的初始化 */
bool CSnow::Init(int num)
{
	/** 初始化粒子数目为num个 */
	if(CParticle::Init(num))
	{
		for(int i=0; i<m_iNum; i++)
		{
			/** 初始化位置 */
			float x,y,z,vx,vy,vz;
			x = 0.1f * (rand()%50) - 2.5f;
			y = 2 + 0.1f * (rand()%2);

			if((int)x%2 == 0)
				z = rand()%6;
			else 
				z = -rand()%3;
			m_pList[i].position = CVector966(x,y,z);

			/** 初始化速度 */
			vx = 0.00001 * (rand()%100);
			vy = 0.0000002 * (rand()%28000);
			vz = 0.0;
			m_pList[i].velocity = CVector966(vx,vy,vz);

			/** 初始化加速度 */
			m_pList[i].acceleration = CVector966(0.0,0.000005f,0.0);

			/** 初始化粒子生命时间 */
			m_pList[i].lifetime = 100;

			/** 初始化粒子的尺寸 */
			m_pList[i].size = 0.01f;

			/** 初始化粒子的消失速度 */
			m_pList[i].dec = 0.005 * (rand()%50);

			/** 初始化粒子的颜色 */
			m_pList[i].color[0] = 255;
			m_pList[i].color[1] = 255;
			m_pList[i].color[2] = 255;

		}

		/** 载入粒子纹理 */
		if(!m_texture.Load("data/flare.bmp"))
		{
			MessageBox(NULL,"载入粒子纹理失败!","错误",MB_OK);
			return false;
		}
		else
			return true;
	}
	else
		return false;
}

/** 雪花的渲染 */
void CSnow::Render()
{
	/** 绑定纹理 */
	glBindTexture(GL_TEXTURE_2D,m_texture.ID);

	/** 开始渲染雪花 */
	for(int i=0; i<m_iNum; ++i)
	{
		float x = m_pList[i].position.x;
		float y = m_pList[i].position.y;
		float z = m_pList[i].position.z;
		float size = m_pList[i].size;

		/** 如果该粒子消失或生命结束则跳出 */
		if (y <= -1 || m_pList[i].lifetime <= 0)
			break;

		glColor3fv(m_pList[i].color);
		glNormal3f(0.0f,0.0f,1.0f);     /**< 定义法线方向 */

		/** 画出粒子 */
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);glVertex3f(x-size,y-size,z);
		glTexCoord2f(1.0f,0.0f);glVertex3f(x-size,y+size,z);
		glTexCoord2f(1.0f,1.0f);glVertex3f(x+size,y+size,z);
		glTexCoord2f(0.0f,1.0f);glVertex3f(x+size,y-size,z);
		glEnd();

	}

	/** 更新粒子属性 */
	Update();
}

/** 雪花的更新 */
void CSnow::Update()
{
	for(int i = 0; i<m_iNum; ++i)
	{
		/** 更新位置 */
		m_pList[i].position.x += m_pList[i].velocity.x * 5;
		m_pList[i].position.y -= m_pList[i].velocity.y;
		if(m_pList[i].position.x > 3.0)
			m_pList[i].position.x = -2.0;

		/** 更新速度 */
		m_pList[i].velocity.y += m_pList[i].acceleration.y;

		/** 更新生存时间 */
		m_pList[i].lifetime -= m_pList[i].dec;

		/** 如果粒子消失或生命结束 */
		if (m_pList[i].position.y <= -1 || m_pList[i].lifetime <= 0)
		{
			/** 初始化位置 */
			float x,y,z,vx,vy,vz;
			x = 0.1f * (rand()%50) - 2.5f;
			y = 2 + 0.1f * (rand()%2);

			if((int)x%2 == 0)
				z = rand()%6;
			else 
				z = -rand()%3;
			m_pList[i].position = CVector966(x,y,z);

			/** 初始化速度 */
			vx = (float)(0.00001 * (rand()%100));
			vy = (float)(0.0000002 * (rand()%28000));
			vz = 0.0;
			m_pList[i].velocity = CVector966(vx,vy,vz);

			/** 初始化加速度 */
			m_pList[i].acceleration = CVector966(0.0,0.000005f,0.0);

			/** 初始化生命时间 */
			m_pList[i].lifetime = 100;

			/** 初始化消失速度 */
			m_pList[i].dec = 0.005*(rand()%50);
		}

	}

}

//////////////////////////////////////////////////////////////////////////
//
// CScene
//
//////////////////////////////////////////////////////////////////////////


void CScene::Render()
{
	if (IsInit==false)
	{
		CScene::init();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();
	gluLookAt(500,220,400,501.99493,219.93904, 400.07977,  0, 1, 0);


	/** 绘制天空 */
	m_SkyBox.render();

	/** 渲染地形 */
	m_Terrain.render();

	glTranslatef(504.0f,222.0f,400.0f);
	/** 渲染雪花 */
	m_Snow.Render();

	glFlush();
}

void CScene::init()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_CULL_FACE);	
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glEnable(GL_TEXTURE_2D);             /**< 开启纹理映射 */   

	/** 设置混合因子获得半透明效果 */
/*	glBlendFunc(GL_SRC_ALPHA,GL_ONE);    
	glEnable(GL_BLEND);	*/			     /**< 启用混和 */

	/** 初始化雪花实例 */	
	if(!m_Snow.Init(5000))
	{
		MessageBox(NULL,"雪花系统初始化失败!","错误",MB_OK);
		exit(-1);
	}

	/** 初始化天空 */
	if(!m_SkyBox.init())
	{
		MessageBox(NULL,"初始化天空失败!","错误",MB_OK);
		exit(0);
	}

	/** 初始化地形 */	
	if(!m_Terrain.init())
	{
		MessageBox(NULL,"初始化地形失败!","错误",MB_OK);
		exit(0);
	}
	IsInit=true;
}

