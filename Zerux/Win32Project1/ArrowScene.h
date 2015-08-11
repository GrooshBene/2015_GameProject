#pragma once
#include "IScene.h"
class CArrowScene :
	public IScene
{
public:
	CArrowScene();
	~CArrowScene();

	virtual void Update(float eTime);
	virtual void Render();
};

