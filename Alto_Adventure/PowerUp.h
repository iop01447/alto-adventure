#pragma once
#ifndef __POWERUP_H__
#define __POWERUP_H__
#include "Obj.h"
class CPowerUp : public CObj
{
public:
	CPowerUp();
	virtual ~CPowerUp();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void Collision(CObj* pOther) override;
};


#endif // !__POWERUP_H__
