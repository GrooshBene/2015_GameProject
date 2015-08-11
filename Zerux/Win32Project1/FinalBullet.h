#pragma once
#include "IScene.h"
#include "Animation.h"
#include "FinalBoss.h"
class CFinalBullet :
	public IScene
{
public:
	CFinalBullet();
	~CFinalBullet();
	int chk;

	CAnimation *ani;
	FinalBoss *m_pFinalBoss;
	float speed;
	virtual void Update(float eTime);
	virtual void Render();
};

