#include "GameScene.h"
#include "App.h"
#include "Arrow.h"
#include "ParticleSystem.h"
CGameScene::CGameScene() : time(0.0f), delay(1.5f)
{
	m_pBackground = new CBackground();
	PushScene(m_pBackground);

	m_pPlayer = new CPlayer();
	PushScene(m_pPlayer);
	m_pPlayer->SetPosition(App::WIDTH / 2 - m_pPlayer->normalAni->width / 2,
		App::HEIGHT - m_pPlayer->normalAni->height);
}

CGameScene::~CGameScene()
{
}

void CGameScene::Input(float eTime)
{
	IScene::Input(eTime);
	if (App::GetInstance()->g_pInputManager->keyState(VK_LEFT)> 0)
	{
		m_pPlayer->Move(-300 * eTime);
	}
	if (App::GetInstance()->g_pInputManager->keyState(VK_RIGHT) > 0)
	{
		m_pPlayer->Move(300 * eTime);
	}
	if (App::GetInstance()->g_pInputManager->keyState(VK_UP) > 0) {
		m_pPlayer->pos.y -= 10;
	}
	if (App::GetInstance()->g_pInputManager->keyState(VK_DOWN) > 0) {
		m_pPlayer->pos.y += 10;
	}
}

void CGameScene::Update(float eTime)
{
	IScene::Update(eTime);
	time += eTime;
	if (time >= delay){
		delay = 0.25;
		time = 0.f;
		this->PushArrow(m_pPlayer->pos.x -70 , m_pPlayer->pos.y);
	}
}

void CGameScene::Render()
{
	IScene::Render();
	m_pBackground->Render();
	m_pPlayer->Render();
	for (auto iter = children.begin(); iter != children.end(); iter++) {
		if (*iter == m_pPlayer || *iter == m_pBackground)
			continue;
		(*iter)->Render();
	}
}

void CGameScene::PushArrow(float x, float y) {
	CArrow *p = new CArrow();
	p->SetPosition(x, y);
	this->PushScene(p);
}
void CGameScene::PushEffect(float x, float y) {
	CParticleSystem *p = new CParticleSystem("resourse/particle/particle.png",50);
	p->SetPosition(x, y);
	p->setColor1(255, 200, 220, 200);
	this->PushScene(p);
	p->start();
}