#pragma once
#include "IScene.h"
#include "Sprite.h"
class CStandBoss :
	public IScene
{
public:
	CStandBoss();
	~CStandBoss();
	CSprite *StandBoss;
	int blood;
	virtual void Update(float eTime);
	virtual void Render();
};

