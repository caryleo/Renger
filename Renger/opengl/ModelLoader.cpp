#include "StdAfx.h"
#include "ModelLoader.h"
#include <gl/gl.h>
#include "CLoad3DS.h"


GLuint texture[1]={0};
CModelLoader::CModelLoader(void)
{
	gothicLoader=new(CLoad3DS);
}


CModelLoader::~CModelLoader(void)
{
}

void CModelLoader::Init(int type)
{
	AUX_RGBImageRec *img1 = auxDIBImageLoad("dumb1.bmp");
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, img1->sizeX, img1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, img1->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
	free(img1->data);
	free(img1);

	switch (type)
	{
	case 1:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/tree1.3DS");
		break;
	case 2:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/qiche33.3DS");
		break;
	case 3:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/lupai3.3DS");
		break;
	case 4:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/lupai4.3DS");
		break;
	case 5:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/CWom0001.3DS");
		break;
	case 6:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/lupai3.3DS");
		break;
	case 7:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 8:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/Blacksmith.3DS");//房屋
		break;
	case 9:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/Church.3DS");//房屋教堂
		break;
	case 10:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/hulan_01.3DS");//护栏
		break;
	case 11:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/yuanbao.3DS");//元宝
		break;
	case 12:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/jiantou.3DS");//箭头
		break;
	default:break;
	}
}


void CModelLoader::DrawModel(float gothicTrans[10])
{
	
	glPushMatrix();  
    changeObject( gothicTrans );  
    drawModel(gothicModel,true,false);  
    glPopMatrix();
}
