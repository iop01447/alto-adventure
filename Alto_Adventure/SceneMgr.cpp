#include "stdafx.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Stage.h"
#include "MyMenu.h"
#include "EndScene.h"
#include "UIMgr.h"


CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr()
	: m_pScene(nullptr)
	, m_eCurScene(SCENE::SCENE_END)
	, m_ePreScene(SCENE::SCENE_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render()
{
	m_pScene->Render();
}

void CSceneMgr::Release()
{
	SAFE_DELETE(m_pScene);
}


void CSceneMgr::Scene_Change(SCENE::ID _eScene)
{
	m_eCurScene = _eScene;

	using namespace SCENE;

	if (m_ePreScene != m_eCurScene)
	{
		SAFE_DELETE(m_pScene);

		switch (m_eCurScene)
		{
		case SCENE_MENU:
			m_pScene = new CMyMenu;
			break;
		case SCENE_STAGE:
			m_pScene = new CStage;
			break;
		case SCENE_END:
			m_pScene = new CEndScene;
			CUIMgr::Get_Instance()->Set_SceneID(SCENE::SCENE_END);
			break;
		default:
			break;
		}
		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}
