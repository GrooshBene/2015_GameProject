#include "GameScene.h"
#include<Windows.h>
#include "App.h"
#include "Arrow.h"
#include "ParticleSystem.h"
#include "ArrowScene.h"
#include "EnemyBullet.h"
#include "StandBullet.h"
#include "FinalBullet.h"
CGameScene::CGameScene() : time(0.0f), delay(1.5f)
{
	m_pBackground = new CBackground();
	PushScene(m_pBackground);
	m_pBoss = new CBoss();
	PushScene(m_pBoss);
	m_pBoss->SetPosition(App::WIDTH / 2 - m_pBoss->stand->width / 2 + 50, -1000);

	m_pFinalBoss = nullptr;
	m_pStandBoss = nullptr;
	m_pPlayer = new CPlayer();
	PushScene(m_pPlayer);
	m_pPlayer->SetPosition(App::WIDTH / 2 - m_pPlayer->normalAni->width / 2,
		App::HEIGHT - m_pPlayer->normalAni->height);

	m_pArrowScene = new CArrowScene();
	PushScene(m_pArrowScene);
	m_pEffectScene = new IScene();
	PushScene(m_pEffectScene);
	speed = 1.0f;

	CGSoundManager *sm = App::GetInstance()->g_pSoundManager;
	sm->AddSoundBuffer(sm->LoadWav(_T("resource/sounds/tok.wav")));
	sm->AddSoundBuffer(sm->LoadWav(_T("resource/sounds/play.wav")));
	sm->AddSoundBuffer(sm->LoadWav(_T("resource/sounds/potal.wav")));
	sm->Play(1, TRUE);

}

void CGameScene::StandBossCreate()
{
	cnt = 0;
	m_pStandBoss = new CStandBoss();
	PushScene(m_pStandBoss);
	m_pStandBoss->SetPosition(App::WIDTH / 2 - m_pBoss->stand->width / 2, 0);

}

void CGameScene::FinalBossCreate() {
	cnt = 0;
	m_pFinalBoss = new FinalBoss();
	PushScene(m_pFinalBoss);
	m_pFinalBoss->SetPosition(App::WIDTH / 2, 0);
}

CGameScene::~CGameScene()
{
}

void CGameScene::Input(float eTime)
{
	CGSoundManager *sm = App::GetInstance()->g_pSoundManager;
	eTime *= speed;
	IScene::Input(eTime);
	if (App::GetInstance()->g_pInputManager->keyState(VK_LEFT) > 0)
	{
		m_pPlayer->Move(-300 * eTime);
		if (m_pPlayer->pos.x < 0) {
			m_pPlayer->pos.x = 0;
		}
	}
	if (App::GetInstance()->g_pInputManager->keyState(VK_RIGHT) > 0)
	{
		m_pPlayer->Move(300 * eTime);
		if (m_pPlayer->pos.x > (App::GetInstance()->WIDTH - 50)) {
			m_pPlayer->pos.x = (App::GetInstance()->WIDTH - 50);
		}
	}
	if (App::GetInstance()->g_pInputManager->keyState(VK_UP) > 0) {
		m_pPlayer->pos.y -= 200 * eTime;
		if (m_pPlayer->pos.y < 0) {
			m_pPlayer->pos.y = 0;
		}
	}
	if (App::GetInstance()->g_pInputManager->keyState(VK_DOWN) > 0) {
		m_pPlayer->pos.y += 200 * eTime;
	}
	if (App::GetInstance()->g_pInputManager->keyState(VK_SPACE) == 1) {
		sm->Play(2);
		if (speed == 1.0f) {
			speed = 0.0f;
		}
		else {
			speed = 1.0f;
		}
	}
	if (App::GetInstance()->g_pInputManager->keyState(VK_LSHIFT) ==1) {
		if (speed == 1.0f) {
			speed = 0.3f;
		}
		else if (speed == 0.0f) {
			speed = 0.0f;
		}
		else if (speed == 0.3f) {
			speed = 1.0f;
		}
	}
}

void CGameScene::Update(float eTime)
{
	CGSoundManager *sm = App::GetInstance()->g_pSoundManager;
	eTime *= speed;
	IScene::Update(eTime);
	time += eTime;
	bulletTime += eTime;
	if (time >= delay) {
		sm->Play(0);
		delay = 0.1;
		time = 0.f;
		this->PushArrow(rand() % App::WIDTH, -200.0f, -D3DX_PI / 2);
	}//총알

	if (m_pBoss == nullptr && m_pStandBoss != nullptr && bulletTime >= delay) {//에러메시지
		if (m_pStandBoss == nullptr)
			parent->PopScene(this);
		delay = 0.001;
		bulletTime = 0.f;
		switch (cnt) {
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
			for (int i = 0; i < 15; i++)
			{
				this->PushStandBullet(m_pStandBoss->pos.x + (i * 30),
					m_pStandBoss->pos.y + m_pStandBoss->StandBoss->height / 2,
					D3DX_PI / 2);
				//수직패턴
			}
			++cnt;
			break;
		case 50:
			for (int i = 0; i < 8; i++) {
				float angle = D3DX_PI / 2 - 0.1*(i - 4);
				this->PushStandBullet(m_pStandBoss->pos.x + m_pStandBoss->StandBoss->width / 2,
					m_pStandBoss->pos.y + m_pStandBoss->StandBoss->height / 2,
					angle);
			}
			cnt = 0;
			//방사형패턴 카운트 초기화 해주기 패턴 더 집어넣을거면 카운트 증가 시켜주기
			break;
		default:
			this->PushStandBullet(m_pStandBoss->pos.x + m_pStandBoss->StandBoss->width / 2,
				m_pStandBoss->pos.y + m_pStandBoss->StandBoss->height / 2,
				(rand() % (int)(D3DX_PI * 1 * 100)) / 100.0f);
			cnt++;
			break;
		}
	}
	//에러메시지 끝
	if (m_pBoss != nullptr && bulletTime >= delay) {		//창림
		if (m_pBoss == nullptr) {
			parent->PopScene(this);
		}
		delay = 0.005;
		bulletTime = 0.f;
		switch (cnt) {
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
			delay = 0.001;
			for (int i = 0; i < 2; i++) {
				this->PushBullet(m_pBoss->pos.x + 40 + (i * 40) + 115,
					m_pBoss->pos.y + 80,
					D3DX_PI / 2);
				/*this->PushBullet(m_pStandBoss->pos.x + m_pBoss->stand->width / 2,
					m_pBoss->pos.y + m_pBoss->stand->height / 2,
					angle);*/
			}
			delay = 0.05;
			++cnt;
			break;
		case 95:
			for (int i = 0; i < 8; i++) {
				float angle = D3DX_PI / 2 - 0.1*(i - 5);
				this->PushBullet(m_pBoss->pos.x + m_pBoss->stand->width / 2 - 52,
					m_pBoss->pos.y + m_pBoss->stand->height / 2 - 35,
					angle);
			}
			cnt = 0;
			break;
		default:
			this->PushBullet(m_pBoss->pos.x + m_pBoss->stand->width / 2 - 52,
				m_pBoss->pos.y + m_pBoss->stand->height / 2 - 35,
				(rand() % (int)(D3DX_PI * 1 * 100)) / 100.0f);
			++cnt;
			break;
		}
	}
	//창림끝

	//장석현
	if (m_pBoss == nullptr && m_pStandBoss == nullptr && bulletTime >= delay && m_pFinalBoss != nullptr) {
		if (m_pFinalBoss == nullptr) {
			parent->PopScene(this);
		}
		bulletTime = 0.f;
		delay = 0.0001;
			switch (cnt) {
			case 25:
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			case 32:
			case 33:
			case 34:
			case 35:
				for (int i = 0; i < 15; i++)
				{
					this->PushFinalBullet(m_pFinalBoss->normal->pos.x + m_pFinalBoss->normal->width/2+(i * 30) - 350,
						m_pFinalBoss->pos.y + m_pFinalBoss->normal->height / 2,
						D3DX_PI / 2);
					//수직패턴
				}
				this->PushFinalBullet(m_pFinalBoss->normal->pos.x + m_pFinalBoss->normal->width / 2 - 40,
					m_pFinalBoss->normal->pos.y + m_pFinalBoss->normal->height / 2,
					(rand() % (int)(D3DX_PI * 1 * 100)) / 100.0f);
				++cnt;
				break;
			case 50:
				for (int i = 0; i < 8; i++) {
					float angle = D3DX_PI / 2 - 0.1*(i - 4);
					this->PushFinalBullet(m_pFinalBoss->normal->pos.x + m_pFinalBoss->normal->width / 2-40,
						m_pFinalBoss->pos.y + m_pFinalBoss->normal->height / 2,
						angle);
				}
				for (int i = 0; i < 8; i++) {
					float angle = D3DX_PI / 2 - 0.1*(i - 4);
					this->PushFinalBullet(m_pFinalBoss->normal->pos.x + m_pFinalBoss->normal->width / 2 - 10,
						m_pFinalBoss->pos.y + m_pFinalBoss->normal->height / 2,
						angle);
				}
						cnt = 0;
						//방사형패턴 카운트 초기화 해주기 패턴 더 집어넣을거면 카운트 증가 시켜주기
						break;
			default:
				this->PushFinalBullet(m_pFinalBoss->normal->pos.x + m_pFinalBoss->normal->width / 2 - 40,
					m_pFinalBoss->normal->pos.y + m_pFinalBoss->normal->height / 2,
					(rand() % (int)(D3DX_PI * 1 * 100)) / 100.0f);
				this->PushFinalBullet(m_pFinalBoss->normal->pos.x + m_pFinalBoss->normal->width / 2 - 70,
					m_pFinalBoss->normal->pos.y + m_pFinalBoss->normal->height / 2,
					(rand() % (int)(D3DX_PI * 1 * 100)) / 100.0f);
				this->PushFinalBullet(m_pFinalBoss->normal->pos.x + m_pFinalBoss->normal->width / 2 - 40 - 40,
					m_pFinalBoss->normal->pos.y + m_pFinalBoss->normal->height / 2,
					(rand() % (int)(D3DX_PI * 1 * 100)) / 100.0f);
				this->PushFinalBullet(m_pFinalBoss->normal->pos.x + m_pFinalBoss->normal->width / 2 - 70 - 40,
					m_pFinalBoss->normal->pos.y + m_pFinalBoss->normal->height / 2,
					(rand() % (int)(D3DX_PI * 1 * 100)) / 100.0f);
				cnt++;
					}
				}
	}



void CGameScene::Render()
{
	IScene::Render();
	m_pBackground->Render();
	if (m_pBoss != nullptr) {
		m_pBoss->Render();
	}
	if (m_pStandBoss != nullptr) {
		m_pStandBoss->Render();
	}
	if (m_pFinalBoss != nullptr) {
		m_pFinalBoss->Render();
	}
	m_pArrowScene->RenderAll();
	m_pEffectScene->RenderAll();
	m_pPlayer->Render();


}

void CGameScene::PushArrow(float x, float y, float rot) {
	CArrow *p = new CArrow();
	p->SetPosition(m_pPlayer->pos.x, m_pPlayer->pos.y);
	m_pArrowScene->PushScene(p);
	p->rot = rot;
}

void CGameScene::PushBullet(float x, float y, float rot) {
	if (m_pBoss != nullptr && m_pBoss->pos.y == 0) {
		CEnemyBullet *bullet = new CEnemyBullet();
		bullet->SetPosition(x, y);
		m_pArrowScene->PushScene(bullet);
		bullet->rot = rot;
	}
}

void CGameScene::PushStandBullet(float x, float y, float rot) {
	if (m_pStandBoss != nullptr && m_pStandBoss->pos.y == 0) {
		CStandBullet *standBullet = new CStandBullet();
		standBullet->SetPosition(x, y);
		m_pArrowScene->PushScene(standBullet);
		standBullet->rot = rot;
	}
}

void CGameScene::PushFinalBullet(float x, float y, float rot) {
	if (m_pFinalBoss != nullptr && m_pFinalBoss->pos.y == 0) {
		CFinalBullet *finalBullet = new CFinalBullet();
		finalBullet->SetPosition(x, y);
		m_pArrowScene->PushScene(finalBullet);
		finalBullet->rot = rot;
	}
}

void CGameScene::PushEffect(float x, float y) {
	CParticleSystem *p = new CParticleSystem("resource/particle/particle.png", 50);
	p->SetPosition(x, y);
	p->setScalep(1, 1);
	p->setColor1(400, 200, 220, 200);
	p->setLife(0.2, 0.3);
	m_pEffectScene->PushScene(p);
	p->start();
}