#include "StdAfx.h"
#include "ModelLoader.h"
#include <gl/gl.h>
#include "CLoad3DS.h"

CLoad3DS *gothicLoader=new(CLoad3DS);

CModelLoader::CModelLoader(void)
{
	
}


CModelLoader::~CModelLoader(void)
{
}

void CModelLoader::Init(int type)
{
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
