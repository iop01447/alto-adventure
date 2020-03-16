#pragma once
#ifndef  __MAGNET_H__
#define __MAGNET_H__

#include "Obj.h"
class CMagnet : public CObj
{
public:
	CMagnet();
	virtual ~CMagnet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void Collision(CObj* pOther) override;
};


#endif // ! __MAGNET_H__
