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
	// CObj을(를) 통해 상속됨
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

public:
	void Update_Size();
	void Key_Check();
	void Jump();
	void Fall();

private:
	//RECT m_tRect; 


	bool			m_bJump;
	bool			m_bFall;

	float			m_fJumpPower;	// 점프 파워
	float			m_fJumpAccel;	// 점프 진행 시간

	float			m_fRotHeight;
};

#endif // !__PLAYER_H__
