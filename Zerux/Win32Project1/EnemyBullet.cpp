#include "EnemyBullet.h"
#include "Animation.h"
#include "Sprite.h"
#include "App.h"
#include "GameScene.h"
#include "Player.h"



CEnemyBullet::CEnemyBullet()
{
	ani = new CAnimation(7.0f);
	PushScene(ani);
	ani->pushSprite("Resource/arrow/bullet.png");

	this->rotatingCenter = D3DXVECTOR2(ani->width , ani->height / 2);
	speed = 450;
}


CEnemyBullet::~CEnemyBullet()
{
}

void CEnemyBullet::Update(float eTime) {
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
		playerRect.left = player->pos.x+40;
		playerRect.right = player->pos.x + player->normalAni->width-40;
		playerRect.top = player->pos.y;
		playerRect.bottom = player->pos.y + player->normalAni->height - 80;
		if (IntersectRect(&tempRect, &playerRect, &bulletRect) == true) {
			player->p_Blood -= 2;
			gs->PushEffect(pos.x + rotatingCenter.x, pos.y + rotatingCenter.y);
			this->parent->PopScene(this);
			return;
		}
	}

void CEnemyBullet::Render() {
	IScene::Render();
	ani->Render();
}
