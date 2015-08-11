#include "StandBullet.h"
#include "App.h"
#include "GameScene.h"
#include "StandBoss.h"



CStandBullet::CStandBullet()
{
	ani = new CAnimation(7.0f);
	PushScene(ani);
	ani->pushSprite("resource/arrow/bullet.png");
	this->rotatingCenter = D3DXVECTOR2(ani->width, ani->height / 2);
	speed = 500;

}




CStandBullet::~CStandBullet()
{
}

void CStandBullet::Update(float eTime) {
	IScene::Update(eTime);
	pos.x += cos(rot)*speed*eTime;
	pos.y += sin(rot)*speed * eTime;
	if (pos.y > App::HEIGHT + 200) {
		this->parent->PopScene(this);
		return;
	}
	RECT bulletRect, playerRect, tempRect;
	bulletRect.left = pos.x + rotatingCenter.x - 1;
	bulletRect.right = pos.x + rotatingCenter.x + 1;
	bulletRect.top = pos.y + rotatingCenter.y - 1;
	bulletRect.bottom = pos.y + rotatingCenter.y + 1;
	CGameScene *gs = (CGameScene*)this->parent->parent;
	CPlayer *player = gs->m_pPlayer;
	playerRect.left = player->pos.x+45;
	playerRect.right = player->pos.x + player->normalAni->width-45;
	playerRect.top = player->pos.y;
	playerRect.bottom = player->pos.y + player->normalAni->height-90;
	if (IntersectRect(&tempRect, &playerRect, &bulletRect) == true) {
		player->p_Blood -= 2;
		gs->PushEffect(pos.x + rotatingCenter.x, pos.y + rotatingCenter.y);
		this->parent->PopScene(this);
		return;
	}
}

void CStandBullet::Render() {
	IScene::Render();
	ani->Render();
}