#pragma once
#include "Obj.h"
class CCoin :
	public CObj
{
public:
	CCoin();
	virtual ~CCoin();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void Collision(CObj* pOther) override;
};

