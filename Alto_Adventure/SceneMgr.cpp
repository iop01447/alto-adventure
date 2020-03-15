#include "stdafx.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Stage.h"
#include "MyMenu.h"


CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr()
	: m_pScene(nullptr)
	, m_eCurScene(SCENE_END)
	, m_ePreScene(SCENE_END)
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


void CSceneMgr::Scene_Change(SCENEID _eScene)
{
	m_eCurScene = _eScene;

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
		default:
			break;
		}
		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}
