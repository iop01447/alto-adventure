#pragma once
#include "Obj.h"
class CRock :
	public CObj
{
public:
	CRock();
	virtual ~CRock();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int m_iID{ 0 };
	BYTE m_byAlphaValue;

	float			m_fJumpPower;	// 점프 파워
	float			m_fJumpAccel;	// 점프 진행 시간
};

