#pragma once
#include "Obj.h"
class CWaterFall :
	public CObj
{
public:
	CWaterFall();
	virtual ~CWaterFall();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;
};
