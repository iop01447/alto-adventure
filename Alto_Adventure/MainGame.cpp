#include "stdafx.h"
#include "MainGame.h"

#include "Device.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
#include "BackgroundMgr.h"



CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	if (FAILED(CDevice::Get_Instance()->InitDevice()))
	{
		assert(false && "InitDevice Failed");
		return;
	}

	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SCENE::SCENE_MENU);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	CDevice::Get_Instance()->Render_Begin();

	CSceneMgr::Get_Instance()->Render();

	CDevice::Get_Instance()->Render_End();

}

void CMainGame::Release()
{
	CLineMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CTextureMgr::Destroy_Instance();
	CBackgroundMgr::Destroy_Instance();

	CObjMgr::Destroy_Instance();

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Destroy_Instance();
}
