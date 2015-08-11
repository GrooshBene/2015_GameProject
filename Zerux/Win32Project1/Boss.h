#pragma once
#include "IScene.h"
#include "Sprite.h"
class CBoss :
	public IScene
{
public:
	CBoss();
	~CBoss();
	CSprite  *stand;
	int blood;
	virtual void Update(float eTime);
	virtual void Render();
};

