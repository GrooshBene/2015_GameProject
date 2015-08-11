#include "Boss.h"
#include "App.h"
#include <iostream>
#include "GameScene.h"
using namespace std;

CBoss::CBoss()
{
	blood = 500;
	stand = new CSprite("Resource/monster/Luminon.png");
	PushScene(stand);

}


CBoss::~CBoss()
{
}

void CBoss::Update(float eTime) {
	CGameScene *gs = (CGameScene*)this->parent;
	if (this->pos.y < 0) {
		this->pos.y += 500 * eTime;
		if (this->pos.y > 0) {
			pos.y = 0;
		}
	}
	if (this->blood < 0) {
		gs->StandBossCreate();
		gs->m_pBoss = nullptr;
		parent->PopScene(this);
		return;
	}
	cout << blood << endl;
}

void CBoss::Render() {
	IScene::Render();
	this->scale.x = 0.8f;
	this->scale.y = 0.8f;
	stand->Render();
}
