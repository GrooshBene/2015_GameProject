#include "Background.h"
#include <math.h>

CBackground::CBackground()
	:time(0.f)
{
	bg = new CSprite("Resource/Background/bg.png");
	star = new CSprite("Resource/Background/star.png");
	this->PushScene(bg);
	this->PushScene(star);
}

CBackground::~CBackground()
{
}

void CBackground::Update(float eTime)
{
	IScene::Update(eTime);
	time += eTime;
}

void CBackground::Render()
{
	IScene::Render();
	bg->Render();
	float alpha = sin(time * 10) * 127 + 128; //1~255
	star->color = D3DCOLOR_ARGB((int)alpha, 255, 255, 255);
	star->Render();
}