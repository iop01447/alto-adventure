#include "stdafx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"
#include "TileEdit.h"


CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SCENE_END), m_ePreScene(SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Update(DWORD time)
{
	m_pScene->Update(time);
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	m_pScene->Render(_DC);
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
		case SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case SCENE_MENU:
			m_pScene = new CMyMenu;
			break;
		case SCENE_STAGE:
			m_pScene = new Stage;
			break;
		case SCENE_EDIT:
			m_pScene = new TileEdit;
			break;
		}
		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}
