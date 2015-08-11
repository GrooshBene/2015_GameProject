#include "Player.h"
#include"App.h"
#include<iostream>
CPlayer::CPlayer()
	:movingR(false), movingL(false), left(false), isJumped(false)
{
	p_Blood = 8;
	normalAni = new CAnimation(5.0f);
	this->PushScene(normalAni);
	normalAni->pushSprite("Resource/player/jet_top.png");
	
	rightAni = new CAnimation(0);
	this->PushScene(rightAni);
	rightAni->pushSprite("Resource/player/jet_right.png");
	
	leftAni = new CAnimation(0);
	this->PushScene(leftAni);
	leftAni->pushSprite("resource/player/jet_left.png");
	
	
}

CPlayer::~CPlayer(){}

void CPlayer::Update(float eTime)
{
	IScene::Update(eTime);
	if (pos.y >= (App::GetInstance()->HEIGHT)-120) {
		pos.y = App::GetInstance()->HEIGHT - 120;
	}
	if (this->p_Blood < 0) {
		parent->PopScene(this);
		return;
	}
	
}

void CPlayer::Render()
{
	IScene::Render();

	if (left)
	{
		//this->scale.x = -1.0f;
	}
	else 
	{
		//this->scale.x = 1.0f;
	}
	if (movingR)
	{
		rightAni->Render();
		movingR = false;
	}
	else if (movingL) {
		leftAni->Render();
		movingL = false;
	}
	else
	{
		normalAni->Render();
	}

	this->scalingCenter = D3DXVECTOR2(normalAni->width / 2, normalAni->height / 2);
}

void CPlayer::Move(float dx)
{
	if(dx != 0) left = (bool)(dx <= 0);
	this->pos.x += dx;
	if (left)
		movingL = true;
	else if(dx>0)
		movingR = true;
}
void CPlayer::MoveY(float dy) {
	up = (bool)(dy <= 0);
	this->pos.y += dy;
}


