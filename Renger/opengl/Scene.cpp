#include "Scene.h"
#include "stdafx.h"
#include <afxver_.h>


//////////////////////////////////////////////////////////////////////////
//
// CBMPLoader
//
//////////////////////////////////////////////////////////////////////////
/** ���캯�� */
CBMPLoader::CBMPLoader()
{
	/** ��ʼ����ԱֵΪ0 */
	image = 0;
	imageWidth = 0;
	imageHeight = 0;
}

/** �������� */
CBMPLoader::~CBMPLoader()
{
	FreeImage(); /**< �ͷ�ͼ������ռ�ݵ��ڴ� */
}

/** װ��һ��λͼ�ļ� */
bool CBMPLoader::LoadBitmap(const char *file)
{
	FILE *pFile = 0; /**< �ļ�ָ�� */

	/** ����λͼ�ļ���Ϣ��λͼ�ļ�ͷ�ṹ */
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER header;

	unsigned char textureColors = 0;/**< ���ڽ�ͼ����ɫ��BGR�任��RGB */

	/** ���ļ�,�������� */
	pFile = fopen(file, "rb");
	if(pFile == 0) return false;

	/** ����λͼ�ļ�ͷ��Ϣ */ 
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);

	/** �����ļ��Ƿ�Ϊλͼ�ļ� */
	if(header.bfType != BITMAP_ID)
	{
		fclose(pFile);             /**< ������λͼ�ļ�,��ر��ļ������� */
		return false;
	}

	/** ����λͼ�ļ���Ϣ */
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

	/** ����ͼ��Ŀ�Ⱥ͸߶� */
	imageWidth = bitmapInfoHeader.biWidth;
	imageHeight = bitmapInfoHeader.biHeight;

	/** ȷ����ȡ���ݵĴ�С */
	if(bitmapInfoHeader.biSizeImage == 0)
		bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth *
		bitmapInfoHeader.biHeight * 3;

	/** ��ָ���Ƶ����ݿ�ʼλ�� */
	fseek(pFile, header.bfOffBits, SEEK_SET);

	/** �����ڴ� */
	image = new unsigned char[bitmapInfoHeader.biSizeImage];

	/** ����ڴ�����Ƿ�ɹ� */
	if(!image)                        /**< �������ڴ�ʧ���򷵻� */
	{
		delete[] image;
		fclose(pFile);
		return false;
	}

	/** ��ȡͼ������ */
	fread(image, 1, bitmapInfoHeader.biSizeImage, pFile);

	/** ��ͼ����ɫ���ݸ�ʽ���н���,��BGRת��ΪRGB */
	for(int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index+=3)
	{
		textureColors = image[index];
		image[index] = image[index + 2];
		image[index + 2] = textureColors;
	}

	fclose(pFile);       /**< �ر��ļ� */
	return true;         /**< �ɹ����� */
}

/** ����λͼ�ļ������������� */
bool CBMPLoader::Load(const char* fileName)
{
	if(!LoadBitmap(fileName))
	{
		MessageBox(NULL,"����λͼ�ļ�ʧ��!","����",MB_OK);
		exit(0);
	}

	/** ��������������� */
	glGenTextures(1, &ID);

	/** ����������� */
	glBindTexture(GL_TEXTURE_2D, ID);

	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageWidth,
		imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		image);
	return true;
}

/** �ͷ��ڴ� */
void CBMPLoader::FreeImage()
{
	/** �ͷŷ�����ڴ� */
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
	/** ɾ�����������ռ�õ��ڴ� */
	for(int i =0 ;i< 5; i++)
	{
		m_texture[i].FreeImage();
		glDeleteTextures(1,&m_texture[i].ID);
	}

}

/** ��պг�ʼ�� */
bool CSkyBox::init()
{
	char filename[128] ;                                         /**< ���������ļ��� */
	char *bmpName[] = { "back","front","top","left","right"};
	for(int i=0; i< 5; i++)
	{
		sprintf(filename,"data/%s",bmpName[i]);
		strcat(filename,".bmp");
		if(!m_texture[i].LoadBitmap(filename))                     /**< ����λͼ�ļ� */
		{
			MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);    /**< �������ʧ���򵯳��Ի��� */
			exit(0);
		}
		glGenTextures(1, &m_texture[i].ID);                        /**< ����һ������������� */

		glBindTexture(GL_TEXTURE_2D, m_texture[i].ID);             /**< ����������� */
		/** �����˲� */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		/** �������� */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture[i].imageWidth,
			m_texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
			m_texture[i].image);
	}
	return true;

}

void CSkyBox::render()
{
	/** ��ó����й���״̬ */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING,&lp);

	glDisable(GL_LIGHTING);            /**< �رչ��� */
	glEnable(GL_TEXTURE_2D);

	/** ��ʼ���� */
	glPushMatrix();
	glTranslatef(500,35,400);

	glRotatef(yRot,0.0f,1.0f,0.0f);

	/** ���Ʊ��� */
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);
	glBegin(GL_QUADS);		

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(  width, -height, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(  width,  height, -length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f( -width,  height, -length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( -width, -height, -length);

	glEnd();



	/** ����ǰ�� */
	glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);
	glBegin(GL_QUADS);	

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f( -width, -height, length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( -width,  height, length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(  width,  height, length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(  width, -height, length);

	glEnd();



	/** ���ƶ��� */
	glBindTexture(GL_TEXTURE_2D,  m_texture[2].ID);
	glBegin(GL_QUADS);		

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(  width, height, -length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(  width, height,  length); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f( -width, height,  length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( -width, height, -length);

	glEnd();



	/** �������� */
	glBindTexture(GL_TEXTURE_2D, m_texture[3].ID);
	glBegin(GL_QUADS);		

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 1.0f);  glVertex3f( -width,  height,	-length);		
	glTexCoord2f(0.0f, 1.0f);  glVertex3f( -width,  height,  length); 
	glTexCoord2f(0.0f, 0.0f);  glVertex3f( -width, -height,  length);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f( -width, -height, -length);	

	glEnd();

	/** �������� */
	glBindTexture(GL_TEXTURE_2D, m_texture[4].ID);
	glBegin(GL_QUADS);		

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f( width, -height, -length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( width, -height,  length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( width,  height,  length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f( width,  height, -length);
	glEnd();


	glPopMatrix();                 /** ���ƽ��� */

	if(lp)                         /** �ָ�����״̬ */  
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
//** ��ǰCTerrainָ�� */
CTerrain* CTerrain::m_pTerrain = NULL;


///** ����������ָ�� */
PFNGLMULTITEXCOORD2FARBPROC	glMultiTexCoord2fARB=NULL;
PFNGLACTIVETEXTUREARBPROC	glActiveTextureARB=NULL;


/** ���캯�� */
CTerrain::CTerrain():m_bDetail(true),m_DetailScale(128)
{
	/** ���õ��δ�С */
	setSize(MAP_WIDTH,CELL_WIDTH);

	/** Ϊ���θ̷߳����ڴ�,����ʼ�� */
	m_pHeightMap = new BYTE[m_nWidth * m_nWidth];
	for(int i=0; i<m_nWidth * m_nWidth; i++)
		m_pHeightMap[i] = 0;

	m_pTerrain = this;

}

/** �������� */
CTerrain::~CTerrain()
{
	/** ɾ���ڴ��ָ�� */
	if(m_pHeightMap)
	{
		delete[] m_pHeightMap;
		m_pHeightMap = 0;
	}

	/** ɾ�����������ռ���ڴ� */	
	for(int i=0; i<2; i++)
	{
		m_texture[i].FreeImage();
		glDeleteTextures(1,&m_texture[i].ID);
	}


}

/** ��ʼ����Ч */
void CTerrain::initFog()
{
	float fogColor[4] = { 0.8f,0.8f,0.8f,1.0f };

	glEnable(GL_FOG);

	glFogi(GL_FOG_MODE,GL_EXP);             /** ������Ч��ģʽ */
	glFogfv(GL_FOG_COLOR,fogColor);         /** ָ�������ɫ */ 
	glFogf(GL_FOG_DENSITY,0.001f);          /** �������Ũ�� */
	glFogf(GL_FOG_START,1.0);               /** ����������Ŀ�ʼλ�� */
	glFogf(GL_FOG_END,1000.0);              /** ����������Ľ���λ�� */
	glHint(GL_FOG_HINT,GL_DONT_CARE);       /** �涨��Ч�������� */ 

}


/** ��ʼ������ */
bool CTerrain::init()
{

	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");

	if(!glActiveTextureARB || !glMultiTexCoord2fARB)
	{
		//���������Ϣ
		MessageBox(NULL, "��֧�ֶ�������", "����", MB_OK);
		exit(0);
		//setDetail(false);
	}

	/** ����߶��ļ� */
	loadRawFile("data/terrain.raw");

	/** �������� */
	loadTexture();

	/** ��ʼ����Ч */
	initFog();

	return true;
}

/** ���õ��δ�С */
void CTerrain::setSize(unsigned  int width, unsigned  int cell)
{
	m_nWidth = width;
	m_nCellWidth = cell; 
}

/** ��ø߶�ͼ�и߶�ֵ */
int CTerrain::getHeight(int x,int y)
{
	if(!m_pHeightMap)
		return 0;
	int xx = x % m_nWidth;
	int yy = y % m_nWidth;
	/** ���ص�ǰ�߶� */
	return m_pHeightMap[(xx + yy * m_nWidth)];
}

/** ��õ���߶� */
float CTerrain::getAveHeight(float x,float z)
{
	float CameraX, CameraZ;

	CameraX = x / m_nCellWidth;
	CameraZ = z / m_nCellWidth;

	/** ����߳�����(Col0, Row0)��(Col1, Row1) */
	int col0 = int(CameraX);
	int row0 = int(CameraZ);
	unsigned int col1 = col0 + 1;
	unsigned int row1 = row0 + 1;

	/** ȷ����Ԫ���겻�����߳����� */
	if (col1 > m_nWidth) col1 = 0;
	if (row1 > m_nWidth) row1 = 0;

	/** ��ȡ��Ԫ���ĸ��ǵĸ߶� */
	float h00 = (float)(m_pHeightMap[col0*m_nCellWidth + row0*m_nCellWidth*m_nWidth]);
	float h01 = (float)(m_pHeightMap[col1*m_nCellWidth + row0*m_nCellWidth*m_nWidth]);
	float h11 = (float)(m_pHeightMap[col1*m_nCellWidth + row1*m_nCellWidth*m_nWidth]);
	float h10 = (float)(m_pHeightMap[col0*m_nCellWidth + row1*m_nCellWidth*m_nWidth]);

	/** ��������������ڵ�Ԫ���λ�� */
	float tx = CameraX - int(CameraX);
	float ty = CameraZ - int(CameraZ);

	/** ����˫���Բ�ֵ�õ�����߶� */
	float txty = tx * ty;

	float final_height	= h00 * (1.0f - ty - tx + txty)
		+ h01 * (tx - txty)
		+ h11 * txty
		+ h10 * (ty - txty);
	return final_height;
}

/** ����߶�ͼ */
bool CTerrain::loadRawFile(const char* fileName)
{
	FILE *pFile = NULL;

	/** ���ļ� */
	pFile = fopen( fileName, "rb" );

	/** ������ */
	if ( pFile == NULL )
	{
		/** ���������Ϣ��������false */
		MessageBox(NULL, "�򿪸߶�ͼ�ļ�ʧ�ܣ�", "����", MB_OK);
		exit(0);
	}

	/** ��ȡ�߶�ͼ�ļ� */
	fread( m_pHeightMap, 1, m_nWidth*m_nWidth, pFile );

	/** ��ȡ������� */
	int result = ferror( pFile );

	/** ��������� */
	if (result)
	{
		MessageBox(NULL, "�޷���ȡ�߶����ݣ�", "����", MB_OK);
		exit(0);
	}

	/** �ر��ļ����ɹ����� */
	fclose(pFile);
	return true;
}

/** ������������ */
void CTerrain::setTexCoord(float x,float z)
{

	float u =  (float)x / (float)m_nWidth;
	float v = -(float)z / (float)m_nWidth;

	///���õ����������������
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, u, v);

	///����ϸ���������������
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, u, v);
}


/** ����������� */
bool CTerrain::loadTexture()
{
	char* fileName[] = {"data/terrain.bmp","data/detail.bmp"};	
	for(int i=0; i < 2; i++)
	{
		if(!m_texture[i].LoadBitmap(fileName[i]) )                    /**< ����λͼ�ļ� */
		{
			MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);       /**< �������ʧ���򵯳��Ի��� */
			exit(0);
		}
		glGenTextures(1, &m_texture[i].ID);                            /**< ����һ������������� */


		glBindTexture(GL_TEXTURE_2D, m_texture[i].ID);                 /**< ����������� */

		/** �����˲� */
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

		/** �������� */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture[i].imageWidth,
			m_texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
			m_texture[i].image);
	}

	return true;

}

/** ��Ⱦ���� */
void CTerrain::render()
{

	int X = 0, Y = 0;						
	float x, y, z;							
	bool bSwitchSides = false;

	/** ���߶�ͼ�Ƿ���Ч */
	if(!m_pHeightMap) 
		return;					

	/** ������ */

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);

	/** ��Ⱦϸ������ */
	if(m_bDetail)
	{
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

		glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);

		/** �任������� */
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glScalef((float)m_DetailScale, (float)m_DetailScale, 1);
		glMatrixMode(GL_MODELVIEW);
	}

	/** ���������δ� */
	glBegin( GL_TRIANGLE_STRIP );			

	/** ����(X)��ʼѭ�� */
	for ( X = 0; X <= m_nWidth; X += m_nCellWidth )
	{
		/** �������Ƿ���Ҫ���෴˳����� */
		if(bSwitchSides)
		{	
			/** ���Ƶ��ε�һ�� */
			for ( Y = m_nWidth; Y >= 0; Y -= m_nCellWidth )
			{
				/** ����(X, Y, Z) */		
				x = X;							
				y = getHeight( X, Y );	
				z = Y;							

				/** ָ����������,�����Ͷ��� */
				//setFogCoord(m_FogDepth, (float)y);
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);		

				/** ����(X + m_nCellWidth, Y, Z) */		
				x = X + m_nCellWidth; 
				y = getHeight( X + m_nCellWidth, Y ); 
				z = Y;

				/** ָ����������,�����Ͷ��� */
				//setFogCoord(m_FogDepth, (float)y);
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);			
			}
		}
		else
		{	
			/** ���Ƶ��ε�һ�� */
			for ( Y = 0; Y <= m_nWidth; Y += m_nCellWidth )
			{
				/** ����(X + m_nCellWidth, Y, Z) */	
				x = X + m_nCellWidth; 
				y = getHeight( X + m_nCellWidth, Y ); 
				z = Y;

				/** ָ����������,�����Ͷ��� */
				//setFogCoord(m_FogDepth, (float)y);
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);

				/** ���� (X, Y, Z) */		
				x = X;							
				y = getHeight( X, Y );	
				z = Y;							

				/** ָ����������,�����Ͷ��� */
				//setFogCoord(m_FogDepth, (float)y);
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);		
			}
		}

		/** �任���� */
		bSwitchSides = !bSwitchSides;
	}

	/** ���ƽ��� */
	glEnd();

	///�ر�����Ԫ1
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);

	//�ر�����Ԫ0
	glActiveTextureARB(GL_TEXTURE0_ARB);		
	glDisable(GL_TEXTURE_2D);

}

//////////////////////////////////////////////////////////////////////////
//
// CParticle
//
//////////////////////////////////////////////////////////////////////////

/** ���캯�� */
CParticle::CParticle():m_iNum(0),m_pList(NULL)
{	
}

/** �������� */
CParticle::~CParticle()
{
	if(m_pList != NULL)
	{
		delete []m_pList;
		m_pList = NULL;
	}

}

/** ���ӵĳ�ʼ�� */
bool CParticle::Init(int _num)
{
	m_iNum = _num;
	m_pList = new Particle[m_iNum];
	if(m_pList == NULL)
		return false;
	return true;
}

/** ���ӵ���Ⱦ */
void CParticle::Render()
{
}

/** ���ӵĸ��� */
void CParticle::Update()
{
}

//////////////////////////////////////////////////////////////////////////
//
// CSnow
//
//////////////////////////////////////////////////////////////////////////

/** ѩ���ĳ�ʼ�� */
bool CSnow::Init(int num)
{
	/** ��ʼ��������ĿΪnum�� */
	if(CParticle::Init(num))
	{
		for(int i=0; i<m_iNum; i++)
		{
			/** ��ʼ��λ�� */
			float x,y,z,vx,vy,vz;
			x = 0.1f * (rand()%50) - 2.5f;
			y = 2 + 0.1f * (rand()%2);

			if((int)x%2 == 0)
				z = rand()%6;
			else 
				z = -rand()%3;
			m_pList[i].position = CVector966(x,y,z);

			/** ��ʼ���ٶ� */
			vx = 0.00001 * (rand()%100);
			vy = 0.0000002 * (rand()%28000);
			vz = 0.0;
			m_pList[i].velocity = CVector966(vx,vy,vz);

			/** ��ʼ�����ٶ� */
			m_pList[i].acceleration = CVector966(0.0,0.000005f,0.0);

			/** ��ʼ����������ʱ�� */
			m_pList[i].lifetime = 100;

			/** ��ʼ�����ӵĳߴ� */
			m_pList[i].size = 0.01f;

			/** ��ʼ�����ӵ���ʧ�ٶ� */
			m_pList[i].dec = 0.005 * (rand()%50);

			/** ��ʼ�����ӵ���ɫ */
			m_pList[i].color[0] = 255;
			m_pList[i].color[1] = 255;
			m_pList[i].color[2] = 255;

		}

		/** ������������ */
		if(!m_texture.Load("data/flare.bmp"))
		{
			MessageBox(NULL,"������������ʧ��!","����",MB_OK);
			return false;
		}
		else
			return true;
	}
	else
		return false;
}

/** ѩ������Ⱦ */
void CSnow::Render()
{
	/** ������ */
	glBindTexture(GL_TEXTURE_2D,m_texture.ID);

	/** ��ʼ��Ⱦѩ�� */
	for(int i=0; i<m_iNum; ++i)
	{
		float x = m_pList[i].position.x;
		float y = m_pList[i].position.y;
		float z = m_pList[i].position.z;
		float size = m_pList[i].size;

		/** �����������ʧ���������������� */
		if (y <= -1 || m_pList[i].lifetime <= 0)
			break;

		glColor3fv(m_pList[i].color);
		glNormal3f(0.0f,0.0f,1.0f);     /**< ���巨�߷��� */

		/** �������� */
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);glVertex3f(x-size,y-size,z);
		glTexCoord2f(1.0f,0.0f);glVertex3f(x-size,y+size,z);
		glTexCoord2f(1.0f,1.0f);glVertex3f(x+size,y+size,z);
		glTexCoord2f(0.0f,1.0f);glVertex3f(x+size,y-size,z);
		glEnd();

	}

	/** ������������ */
	Update();
}

/** ѩ���ĸ��� */
void CSnow::Update()
{
	for(int i = 0; i<m_iNum; ++i)
	{
		/** ����λ�� */
		m_pList[i].position.x += m_pList[i].velocity.x * 5;
		m_pList[i].position.y -= m_pList[i].velocity.y;
		if(m_pList[i].position.x > 3.0)
			m_pList[i].position.x = -2.0;

		/** �����ٶ� */
		m_pList[i].velocity.y += m_pList[i].acceleration.y;

		/** ��������ʱ�� */
		m_pList[i].lifetime -= m_pList[i].dec;

		/** ���������ʧ���������� */
		if (m_pList[i].position.y <= -1 || m_pList[i].lifetime <= 0)
		{
			/** ��ʼ��λ�� */
			float x,y,z,vx,vy,vz;
			x = 0.1f * (rand()%50) - 2.5f;
			y = 2 + 0.1f * (rand()%2);

			if((int)x%2 == 0)
				z = rand()%6;
			else 
				z = -rand()%3;
			m_pList[i].position = CVector966(x,y,z);

			/** ��ʼ���ٶ� */
			vx = (float)(0.00001 * (rand()%100));
			vy = (float)(0.0000002 * (rand()%28000));
			vz = 0.0;
			m_pList[i].velocity = CVector966(vx,vy,vz);

			/** ��ʼ�����ٶ� */
			m_pList[i].acceleration = CVector966(0.0,0.000005f,0.0);

			/** ��ʼ������ʱ�� */
			m_pList[i].lifetime = 100;

			/** ��ʼ����ʧ�ٶ� */
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


	/** ������� */
	m_SkyBox.render();

	/** ��Ⱦ���� */
	m_Terrain.render();

	glTranslatef(504.0f,222.0f,400.0f);
	/** ��Ⱦѩ�� */
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

	//glEnable(GL_TEXTURE_2D);             /**< ��������ӳ�� */   

	/** ���û�����ӻ�ð�͸��Ч�� */
/*	glBlendFunc(GL_SRC_ALPHA,GL_ONE);    
	glEnable(GL_BLEND);	*/			     /**< ���û�� */

	/** ��ʼ��ѩ��ʵ�� */	
	if(!m_Snow.Init(5000))
	{
		MessageBox(NULL,"ѩ��ϵͳ��ʼ��ʧ��!","����",MB_OK);
		exit(-1);
	}

	/** ��ʼ����� */
	if(!m_SkyBox.init())
	{
		MessageBox(NULL,"��ʼ�����ʧ��!","����",MB_OK);
		exit(0);
	}

	/** ��ʼ������ */	
	if(!m_Terrain.init())
	{
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
		exit(0);
	}
	IsInit=true;
}

