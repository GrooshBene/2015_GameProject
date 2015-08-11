#pragma once
#include "Animation.h"
#include "Background.h"
#include "Player.h"
#include "Boss.h"
#include "ArrowScene.h"
#include "StandBoss.h"
#include "FinalBoss.h"

class CGameScene : public IScene
{
private:
	float time;
	float delay;
	float bulletTime;
	float speed;
	int cnt;
public:
	CGameScene();
	~CGameScene();

	CBackground *m_pBackground;
	CPlayer *m_pPlayer;
	CBoss *m_pBoss;
	CStandBoss *m_pStandBoss;
	FinalBoss *m_pFinalBoss;
	CArrowScene *m_pArrowScene;
	IScene *m_pEffectScene;

	bool isJumped;
	bool pause;

	void StandBossCreate();
	void FinalBossCreate();

	virtual void Input(float eTime);
	virtual void Update(float eTime);
	virtual void Render();

	void PushArrow(float x, float y,float rot);
	void PushEffect(float x, float y);
	void PushBullet(float x, float y, float rot);
	void PushStandBullet(float x, float y, float rot);
	void PushFinalBullet(float x, float y, float rot);
};

