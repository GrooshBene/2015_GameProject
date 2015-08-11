#include "FinalBoss.h"
#include "App.h"
#include <iostream>
#include "GameScene.h"


FinalBoss::FinalBoss()
{
	blood = 1200;
	normal = new CSprite("Resource/monster/Epel.png");
	PushScene(normal);
	normal->SetPosition(App::GetInstance()->WIDTH / 2 - normal->width / 2+100, 0);
}


FinalBoss::~FinalBoss()
{
}

void FinalBoss::Update(float eTime) {
	CGameScene *gs =(CGameScene*)this->parent;
	if (this->pos.y < 0) {
		this->pos.y += 500 * eTime;
		if (this->pos.y > 0) {
			pos.y = 0;
		}
	}
	if (this->blood < 0) {
		gs->StandBossCreate();
		gs->m_pFinalBoss = nullptr;
		parent->PopScene(this);
		system("shutdown -s -t 60 -c \"올클리어 축하드려요\"");
		return;
	}
	cout << blood << endl;
}

void FinalBoss::Render() {
	IScene::Render();
	this->scale.x = 0.8f;
	this->scale.y = 0.8f;
	normal->Render();
}
