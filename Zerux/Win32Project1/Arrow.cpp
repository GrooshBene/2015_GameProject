#include "Arrow.h"
#include "App.h"
#include "GameScene.h"
#include "Boss.h"
#include "SoundManager.h"



CArrow::CArrow()
{
	ani = new CAnimation(7.0f);
	PushScene(ani);
	ani->pushSprite("Resource/arrow/icon.png");
	float degree = (float)(rand() % 61 + 60);
	float radian = degree / 180.0f * D3DX_PI;
	this->rot = -D3DX_PI/2;

	this->rotatingCenter = D3DXVECTOR2(ani->width+37, ani->height / 2);
	speed = 1000;

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
	RECT arrowRect, bossRect, tempRect,standBossRect,finalBossRect;
	arrowRect.left = pos.x + rotatingCenter.x - 1;
	arrowRect.right = pos.x + rotatingCenter.x + 1;
	arrowRect.top = pos.y + rotatingCenter.y - 1;
	arrowRect.bottom = pos.y + rotatingCenter.y + 1;

	CGameScene *gs = (CGameScene*)this->parent->parent;
	CBoss *boss = gs->m_pBoss;
	CStandBoss *standBoss = gs->m_pStandBoss;
	FinalBoss *finalBoss = gs->m_pFinalBoss;
	CGSoundManager *sm = (CGSoundManager*)this->parent->parent;
	if (boss != nullptr)
	{
		bossRect.left = boss->pos.x + 70;
		bossRect.right = boss->pos.x + boss->stand->width - 120;
		bossRect.top = boss->pos.y;
		bossRect.bottom = boss->pos.y + boss->stand->height - 100;
		if (IntersectRect(&tempRect, &bossRect, &arrowRect) == true) {
				boss->blood -= 2;
			gs->PushEffect(pos.x + rotatingCenter.x, pos.y + rotatingCenter.y);
			this->parent->PopScene(this);
			return;
		}
	}
	if (standBoss != nullptr) {
		standBossRect.left = standBoss->pos.x;
		standBossRect.right = standBoss->pos.x + standBoss->StandBoss->width;
		standBossRect.top = standBoss->pos.y;
		standBossRect.bottom = standBoss->pos.y + standBoss->StandBoss->height;
		if (IntersectRect(&tempRect, &standBossRect, &arrowRect) == true) {
			standBoss->blood -=   2;
			gs->PushEffect(pos.x + rotatingCenter.x, pos.y + rotatingCenter.y);
			this->parent->PopScene(this);
			return;
		}
	}
	if (finalBoss != nullptr) {
		finalBossRect.left = finalBoss->normal->pos.x-70;
		finalBossRect.right = finalBoss->normal->pos.x + finalBoss->normal->width-90;
		finalBossRect.top = finalBoss->normal->pos.y-40;
		finalBossRect.bottom = finalBoss->normal->pos.y + finalBoss->normal->height-50;
		if (IntersectRect(&tempRect, &finalBossRect, &arrowRect) == true) {
			finalBoss->blood -= 3;
			gs->PushEffect(pos.x+rotatingCenter.x, pos.y + rotatingCenter.y);
			this->parent->PopScene(this);
			return;
		}

	}
}

void CArrow::Render() {
	IScene::Render();
	ani->Render();
}