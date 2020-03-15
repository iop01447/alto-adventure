#pragma once

#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "Obj.h"
class CEffect : public CObj
{
public:
	CEffect();
	virtual ~CEffect();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int			m_iAlphaValue;
	float		m_fSize;
};

#endif