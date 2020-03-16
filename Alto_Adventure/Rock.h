#pragma once
#include "Obj.h"
class CRock :
	public CObj
{
public:
	CRock();
	virtual ~CRock();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int m_iID{ 0 };
	BYTE m_byAlphaValue;

	float			m_fJumpPower;	// ���� �Ŀ�
	float			m_fJumpAccel;	// ���� ���� �ð�
};

