#pragma once
#include "IScene.h"
#include "Animation.h"
#include "Boss.h"
class CEnemyBullet :
	public IScene
{
public:
	CEnemyBullet();
	~CEnemyBullet();
	int chk;

	CAnimation *ani;
	CBoss *m_pBoss;
	float speed;
	virtual void Update(float eTime);
	virtual void Render();
};

