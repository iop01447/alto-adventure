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
	void Update_Size();
	void Key_Check();
	void Jump();
	void Fall();

private:
	//RECT m_tRect; 
	bool			m_bJump;
	bool			m_bFall;

	float			m_fJumpPower;	// ���� �Ŀ�
	float			m_fJumpAccel;	// ���� ���� �ð�

	float			m_fRotHeight; // ĳ���Ͱ� ȸ���ϸ鼭 �ٲ� ����~bottom ������ �Ÿ�

	DWORD			m_dwIdleTime;

};

#endif // !__PLAYER_H__
