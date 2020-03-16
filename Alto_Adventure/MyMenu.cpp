#include "stdafx.h"
#include "MyMenu.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "TextureMgr.h"


CMyMenu::CMyMenu()
	:bGameStartButton(false)
{
}

CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	D3DXCreateLine(GET_INSTANCE(CDevice)->Get_Device(), &g_pLine);
	g_pLine->SetWidth(6);

	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Image/Menu0.png", L"Menu", L"Menu", 1);
	CSoundMgr::Get_Instance()->PlayBGM(L"MenuBGM.wav");
}

void CMyMenu::Update()
{
}

void CMyMenu::Late_Update()
{
	if (bGameStartButton && CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SCENE_STAGE);

}

void CMyMenu::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Menu", L"Menu", 0);

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0));
	D3DXMatrixTranslation(&matTrans, fCenterX, fCenterY, 0.f);

	matWorld = matScale * matRotZ * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(128, 255, 255, 255));

	RECT StartBotton = { 590, 595, 675, 645 };

	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&StartBotton, pt))
	{
		D3DXVECTOR2 Point[5] = {};
		Point[0].x = float(StartBotton.left);
		Point[0].y = float(StartBotton.top);

		Point[1].x = float(StartBotton.right);
		Point[1].y = float(StartBotton.top);

		Point[2].x = float(StartBotton.right);
		Point[2].y = float(StartBotton.bottom);

		Point[3].x = float(StartBotton.left);
		Point[3].y = float(StartBotton.bottom);

		Point[4].x = float(StartBotton.left);
		Point[4].y = float(StartBotton.top);

		g_pLine->Draw(Point, 5, D3DCOLOR_ARGB(255, 0, 0, 0));

		bGameStartButton = true;
	}
	else
	{
		bGameStartButton = false;
	}
}

void CMyMenu::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
}
