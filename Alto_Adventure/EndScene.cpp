#include "stdafx.h"
#include "EndScene.h"
#include "BackgroundMgr.h"
#include "UIMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "TextureMgr.h"


CEndScene::CEndScene()
{
}


CEndScene::~CEndScene()
{
	Release();
}

void CEndScene::Initialize()
{
	CUIMgr::Get_Instance()->Update();
}

void CEndScene::Update()
{
	GET_INSTANCE(CBackgroundMgr)->Update();
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
		CSceneMgr::Get_Instance()->Scene_Change(SCENE::SCENE_MENU);
}

void CEndScene::Late_Update()
{
}

void CEndScene::Render()
{
	GET_INSTANCE(CBackgroundMgr)->Render();
	CUIMgr::Get_Instance()->Render();
}

void CEndScene::Release()
{
	CUIMgr::Get_Instance()->Destroy_Instance();
	CBackgroundMgr::Get_Instance()->Destroy_Instance();
	CTextureMgr::Get_Instance()->Destroy_Instance();
}
