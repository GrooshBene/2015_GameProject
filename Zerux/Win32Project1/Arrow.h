#pragma once
#include "Animation.h"
#include "Player.h"
class CArrow
	:public IScene
{
public:
	CArrow();
	~CArrow();
	int chk;

	CAnimation *ani;
	CPlayer *m_pPlayer;
	float speed;
	virtual void Update(float eTime);
	virtual void Render();
};

