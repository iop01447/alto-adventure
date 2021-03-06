#pragma once
#ifndef __MYMENU_H__
#define __MYMENU_H__

#include "Scene.h"
class CMyMenu : public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

	bool bGameStartButton;
};

#endif