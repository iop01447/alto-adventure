#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Device.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "BackgroundMgr.h"
#include "TextureMgr.h"

LPD3DXLINE g_pLine;

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

	if (FAILED(CDevice::Get_Instance()->InitDevice()))
	{
		assert(false && "InitDevice Failed");
		return;
	}

	D3DXCreateLine(GET_INSTANCE(CDevice)->Get_Device(), &g_pLine);
	g_pLine->SetWidth(5);

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"Back.bmp", L"Back");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"BackBuffer.bmp", L"BackBuffer");

	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());

	//테스트용 라인
	CLineMgr::Get_Instance()->Initialize();

	//CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SCENE_LOGO);
}

void CMainGame::Update()
{
	//CSceneMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Key_Update();
	GET_INSTANCE(CBackgroundMgr)->Update();
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
	//HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	//HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	//BitBlt(hBackBuffer, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	////CSceneMgr::Get_Instance()->Render(hBackBuffer);

	
	//BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);


	//++m_iFPS;
	//if (m_dwTime + 1000 < GetTickCount())
	//{
	//	swprintf_s(m_szFPS, L"FPS: %d", m_iFPS);
	//	SetWindowText(g_hWnd, m_szFPS);

	//	m_iFPS = 0;
	//	m_dwTime = GetTickCount();
	//}

	CDevice::Get_Instance()->Render_Begin();

	GET_INSTANCE(CBackgroundMgr)->Render();
	CObjMgr::Get_Instance()->Render();
	g_pLine->Begin();
	g_pLine->Draw(GET_INSTANCE(CLineMgr)->Get_PointList(), GET_INSTANCE(CLineMgr)->Get_PointCnt(), D3DCOLOR_ARGB(255, 255, 255, 255));
	g_pLine->End();
	//GET_INSTANCE(CBackgroundMgr)->Render_Forward(0.5f); // 반투명하게 안그려져서 포기, 이유는 모르겠다.

	CDevice::Get_Instance()->Render_End();

}

void CMainGame::Release()
{
	CLineMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	//CSceneMgr::Destroy_Instance();
	CTextureMgr::Destroy_Instance();
	CBackgroundMgr::Destroy_Instance();

	CObjMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_DC);
}
