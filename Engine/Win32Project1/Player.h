#pragma once
#include "Animation.h"
class CPlayer :
	public IScene
{
private:
	bool moving, left, up;
public:
	CPlayer();
	~CPlayer();
	CAnimation *normalAni, *moveAni;
	D3DXVECTOR2 colPos;
	CPlayer *m_pPlayer;
	bool isJumped;
	virtual void Update(float eTime);
	virtual void Render();

	void Move(float dx);
	void MoveY(float dy);
};