#pragma once
#include "IScene.h"
#include "Sprite.h"

class FinalBoss :public IScene
{
public:
	FinalBoss();
	~FinalBoss();
	CSprite *normal;
	int blood;
	virtual void Update(float eTime);
	virtual void Render();
};

