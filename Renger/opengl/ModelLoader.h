#pragma once
#include "CLoad3DS.h"

class CModelLoader
{
public:
	CModelLoader(void);
	~CModelLoader(void);
	t3DModel gothicModel;
	CLoad3DS *gothicLoader;

	void Init(int type);
	void DrawModel(float gothicTrans[10]);
	
};

