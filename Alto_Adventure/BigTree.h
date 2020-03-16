#pragma once
#include "Obj.h"
class CBigTree :
	public CObj
{
public:
	CBigTree();
	virtual ~CBigTree();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float m_fReflection{ 0 };
	static bool m_bToggle; 
	int m_zID{ 0 }; // 0: ��, 1: ��
};

