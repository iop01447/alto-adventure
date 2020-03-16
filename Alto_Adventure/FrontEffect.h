#pragma once

#ifndef __FRONTEFFECT_H__
#define __FRONTEFFECT_H__

#include "Obj.h"
class CFrontEffect : public CObj
{
public:
	CFrontEffect();
	virtual ~CFrontEffect();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	BYTE			m_byColor[4];
	float			m_fSize;
};



#endif // !__FRONTEFFECT_H__
