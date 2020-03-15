#pragma once

#ifndef __STAGE_H__
#define __STAGE_H__


#include "Scene.h"
class CStage : public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

};


#endif // !__STAGE_H__
