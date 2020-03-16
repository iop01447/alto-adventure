#pragma once
#include "Obj.h"
class CWaterFall :
	public CObj
{
public:
	CWaterFall();
	virtual ~CWaterFall();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;
};
