#include "Player.h"
#include"App.h"
#include<iostream>
CPlayer::CPlayer()
	:moving(false), left(false), isJumped(false)
{
	normalAni = new CAnimation(5.0f);
	this->PushScene(normalAni);
	normalAni->pushSprite("Resource/player/stand.png");

	moveAni = new CAnimation(7.0f);
	this->PushScene(moveAni);
	/*for (int i = 0; i < 7; i++)
	{
		char path[7][100];
		sprintf_s(path[i], 100, "Resource/player/waliking%d.png", i + 1);
		moveAni->pushSprite(path[i]);
	}*/
	moveAni->pushSprite("Resource/player/walking1.png");
	moveAni->pushSprite("Resource/player/walking2.png");
	moveAni->pushSprite("Resource/player/walking3.png");
	moveAni->pushSprite("Resource/player/walking4.png");
	moveAni->pushSprite("Resource/player/walking5.png");
	moveAni->pushSprite("Resource/player/walking6.png");
	moveAni->pushSprite("Resource/player/walking7.png");
}

CPlayer::~CPlayer(){}

void CPlayer::Update(float eTime)
{
	IScene::Update(eTime);
	if (!isJumped) {
		pos.y += 180 * eTime;
	}
	if (pos.y >= (App::GetInstance()->HEIGHT)-120) {
		pos.y = App::GetInstance()->HEIGHT - 120;
	}
	
}

void CPlayer::Render()
{
	IScene::Render();

	if (left)
	{
		this->scale.x = -1.0f;
	}
	else 
	{
		this->scale.x = 1.0f;
	}
	if (moving)
	{
		moveAni->Render();
		moving = false;
	}
	else
	{
		normalAni->Render();
	}

	this->scalingCenter = D3DXVECTOR2(normalAni->width / 2, normalAni->height / 2);
}

void CPlayer::Move(float dx)
{
	left = (bool)(dx <= 0);
	this->pos.x += dx;
	moving = true;
}
void CPlayer::MoveY(float dy) {
	up = (bool)(dy <= 0);
	this->pos.y += dy;
	moving = true;
}


