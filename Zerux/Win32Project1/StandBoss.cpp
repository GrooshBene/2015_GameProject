#include "StandBoss.h"
#include "App.h"
#include <iostream>
#include "GameScene.h"
using namespace std;



CStandBoss::CStandBoss()
{
	blood = 700;
	StandBoss = new CSprite("Resource/monster/zerux.png");
	PushScene(StandBoss);
}


CStandBoss::~CStandBoss()
{
}

void CStandBoss::Update(float eTime) {
	CGameScene *gs = (CGameScene*)this->parent;
	if (this->pos.y < 0) {
		this->pos.y += 900 * eTime;
		if (this->pos.y > 0) {
			pos.y = 0;
		}
	}
	if (this->blood < 0) {
		gs->m_pStandBoss = nullptr;
		gs->m_pFinalBoss = new FinalBoss();
		gs->PushScene(gs->m_pFinalBoss);
		parent->PopScene(this);
		return;
	}
	cout <<  blood << endl;
}

void CStandBoss::Render() {
	IScene::Render();
	StandBoss->Render();
}