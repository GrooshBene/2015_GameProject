#pragma once
#include "Animation.h"
#include "Background.h"
#include "Player.h"

class CGameScene : public IScene
{
private:
	float time;
	float delay;
public:
	CGameScene();
	~CGameScene();

	CBackground *m_pBackground;
	CPlayer *m_pPlayer;

	bool isJumped;

	virtual void Input(float eTime);
	virtual void Update(float eTime);
	virtual void Render();

	void PushArrow(float x, float y);
	void PushEffect(float x, float y);
};

