#pragma once
#include "Animation.h"
class CPlayer :
	public IScene
{
private:
	bool movingL,movingR, left, up;
	
public:
	CPlayer();
	~CPlayer();
	int p_Blood;
	CAnimation *normalAni, *leftAni, *rightAni;
	D3DXVECTOR2 colPos;
	CPlayer *m_pPlayer;
	bool isJumped;
	virtual void Update(float eTime);
	virtual void Render();

	void Move(float dx);
	void MoveY(float dy);
};