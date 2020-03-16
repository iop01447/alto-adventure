#pragma once
#include "Obj.h"
class CTree :
	public CObj
{
public:
	CTree();
	virtual ~CTree();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int m_iID{ 0 };
};

