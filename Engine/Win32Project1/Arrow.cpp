#include "Arrow.h"
#include "App.h"
#include "Player.h"
#include "GameScene.h"


CArrow::CArrow()
{
	ani = new CAnimation(7.0f);
	PushScene(ani);
	ani->pushSprite("Resource/arrow/1.png");
	ani->pushSprite("Resource/arrow/2.png");
	ani->pushSprite("Resource/arrow/3.png");
	ani->pushSprite("Resource/arrow/2.png");
	float degree = (float)(rand() % 61 + 60);
	float radian = degree / 180.0f * D3DX_PI;
	this->rot = radian;

	this->rotatingCenter = D3DXVECTOR2(ani->width-7, ani->height / 2);
	speed = rand() % 301 + 150;;

}


CArrow::~CArrow()
{

}

void CArrow::Update(float eTime) {
	IScene::Update(eTime);
	pos.x += cos(rot)*speed*eTime;
	pos.y += sin(rot)*speed * eTime;
	if (pos.y > App::HEIGHT + 200) {
		this->parent->PopScene(this);
	}

	RECT arrowRect, playerRect, tempRect;
	arrowRect.left = pos.x + rotatingCenter.x - 1;
	arrowRect.right = pos.x + rotatingCenter.x + 1;
	arrowRect.top = pos.y + rotatingCenter.y - 1;
	arrowRect.bottom = pos.y + rotatingCenter.y + 1;

	CGameScene *gs = (CGameScene*)this->parent;
	CPlayer *player = gs->m_pPlayer;
	playerRect.left = player->pos.x;
	playerRect.right = player->pos.x + player->normalAni->width;
	playerRect.top = player->pos.y;
	playerRect.bottom = player->pos.y + player->normalAni->height;

	if (IntersectRect(&tempRect, &playerRect, &arrowRect) == true) {
		this->parent->PopScene(this);
	}
}

void CArrow::Render() {
	IScene::Render();
	ani->Render();
}