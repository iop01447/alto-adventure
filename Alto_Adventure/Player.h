#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "Obj.h"
class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	enum STATE { IDLE, WALK, ATTACK, HIT, DEAD, END };

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render();
	virtual void Release();
	
	virtual void Collision(CObj* pOther) override;

public:
	void Render_ItemEffect();
	void Collision_Object();
	void Update_Size();
	void Key_Check();
	void Jump();
	void Fall();

public:
	int Get_Coin() { return m_iCoin; }
	int Get_HP() { return m_iHP; }
	bool Get_UnDeadMode() { return m_bUnDead; }

private:
	//RECT m_tRect; 
	bool			m_bJump;
	bool			m_bFall;
	bool			m_bHit;

	float			m_fJumpPower;	// ���� �Ŀ�
	float			m_fJumpAccel;	// ���� ���� �ð�

	float			m_fRotHeight; // ĳ���Ͱ� ȸ���ϸ鼭 �ٲ� ����~bottom ������ �Ÿ�

	DWORD			m_dwIdleTime;
	DWORD			m_dwHitEffectTime;
	DWORD			m_dwFrontEffectTime;
	DWORD			m_dwDurationPowerUp;
	DWORD			m_dwDurationMagnet;

	BYTE			m_byColor[4];

	int				m_iCoin{ 0 };
	int				m_iHP{ 3 };
	CObj*			m_pRock{ nullptr };

	bool			m_bUnDead{ false };

};

#endif // !__PLAYER_H__
