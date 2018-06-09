#include "StdAfx.h"
#include "ModelLoader.h"
#include <gl/gl.h>
#include "CLoad3DS.h"
#include <gl/GLAux.h>

CLoad3DS *gothicLoader=new(CLoad3DS);
GLuint texture[1]={0};

CModelLoader::CModelLoader(void)
{
	
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
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 2:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 3:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 4:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 5:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 6:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 7:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 8:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 9:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 10:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
		break;
	case 11:
		gothicLoader->Import3DS(&gothicModel, "Data/3ds/model.3DS");
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
