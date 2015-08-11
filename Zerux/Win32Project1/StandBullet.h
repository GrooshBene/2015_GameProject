#pragma once
#include "IScene.h"
#include "Animation.h"
#include "StandBoss.h"
class CStandBullet :
	public IScene
{
public:
	CStandBullet();
	~CStandBullet();
	int chk;
	
	CAnimation *ani;
	CStandBoss *m_pStandBoss;
	float speed;
	virtual void Update(float eTime);
	virtual void Render();
};

