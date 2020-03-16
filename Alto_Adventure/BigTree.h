#pragma once
#include "Obj.h"
class CBigTree :
	public CObj
{
public:
	CBigTree();
	virtual ~CBigTree();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float m_fReflection{ 0 };
	int m_zID{ 0 }; // 앞이냐 뒤냐
};

