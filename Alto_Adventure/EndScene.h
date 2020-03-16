#pragma once
#include "Scene.h"
class CEndScene :
	public CScene
{
public:
	CEndScene();
	virtual ~CEndScene();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

