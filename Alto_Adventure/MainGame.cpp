#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0), m_szFPS(L"")
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"BackBuffer.bmp", L"BackBuffer");

	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());

	//테스트용 라인
	CLineMgr::Get_Instance()->Initialize();

	//CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SCENE_LOGO);
}

void CMainGame::Update()
{
	//CSceneMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Key_Update();
}

void CMainGame::Late_Update()
{
	//CSceneMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Key_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render()
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	BitBlt(hBackBuffer, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	//CSceneMgr::Get_Instance()->Render(hBackBuffer);
	CObjMgr::Get_Instance()->Render(hBackBuffer);

	CLineMgr::Get_Instance()->Render(hBackBuffer);
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);


	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release()
{
	CLineMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	//CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
