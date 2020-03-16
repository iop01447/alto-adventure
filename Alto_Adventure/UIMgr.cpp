#include "stdafx.h"
#include "UIMgr.h"
#include "Device.h"
#include "ObjMgr.h"
#include "Player.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CUIMgr);


CUIMgr::CUIMgr()
{
	Initialize();
}


CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize()
{
	const DWORD _dwSize = 200;

	D3DXFONT_DESCW tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));
	tFontInfo.Width = 15;
	tFontInfo.Height = static_cast<int>(tFontInfo.Width * 2.083f);
	tFontInfo.Weight = FW_NORMAL;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"");
	if (FAILED(D3DXCreateFontIndirect(CDevice::Get_Instance()->Get_Device(), &tFontInfo, &m_pSmallFont)))
	{
		assert(false && L"Create Font Failed!");
	}

	tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));
	tFontInfo.Width = 30;
	tFontInfo.Height = static_cast<int>(tFontInfo.Width * 2.083f);
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"");
	if (FAILED(D3DXCreateFontIndirect(CDevice::Get_Instance()->Get_Device(), &tFontInfo, &m_pBigFont)))
	{
		assert(false && L"Create Font Failed!");
	}
	m_byMagnetAlphaValue = 250;
	m_byPowerUpAlphaValue = 250;
}

void CUIMgr::Update()
{
	CPlayer* player = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
	m_iCoin = player->Get_Coin();
	m_iHP = player->Get_HP();
	m_bUnDeadMode = player->Get_UnDeadMode();

	m_fDistance += 0.2f;
}

void CUIMgr::Render()
{
	switch (m_eSceneID)
	{
	case SCENE::SCENE_STAGE:
		Render_Coin();
		Render_HP();
		Render_Distance();
		Render_UnDeadMode();
		Render_MagnetItem();
		Render_PowerUpItem();
		break;
	case SCENE::SCENE_END:
		Render_EndScene();
		break;
	}
}

void CUIMgr::Release()
{
	m_pSmallFont->Release();
	m_pBigFont->Release();
}

void CUIMgr::Render_Coin()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Coin");

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.013f, 0.013f, 0.f);
	D3DXMatrixTranslation(&matTrans, 50, 50, 0.f);

	matWorld = matScale * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	TCHAR szBuff[50] = L"";
	swprintf_s(szBuff, L"%d", m_iCoin);

	D3DXMatrixTranslation(&matTrans, 80, 34, 0.f);
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
	m_pSmallFont->DrawTextW(CDevice::Get_Instance()->Get_Sprite(), szBuff, lstrlen(szBuff), nullptr, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUIMgr::Render_HP()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Heart");

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.03f, 0.03f, 0.f);

	for (int i = 0; i < m_iHP; ++i) {
		D3DXMatrixTranslation(&matTrans, 50 + i * (pTexInfo->tImageInfo.Width * 0.03f + 3), 90, 0.f);

		matWorld = matScale * matTrans;
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CUIMgr::Render_Distance()
{
	TCHAR szBuff[50] = L"";
	swprintf_s(szBuff, L"%.1fm", m_fDistance);

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 0, 0, 0.f);
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
	RECT rect = { WINCX - 500, 30, WINCX - 30, 200 };
	m_pBigFont->DrawTextW(CDevice::Get_Instance()->Get_Sprite(), szBuff, lstrlen(szBuff), &rect, DT_RIGHT, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUIMgr::Render_MagnetItem()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Magnet");

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.f);
	D3DXMatrixTranslation(&matTrans, 50.f, float(WINCY - 50), 0.f);

	matWorld = matScale * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	

	if (GET_INSTANCE(CObjMgr)->Get_Obj(OBJID::PLAYER)->Get_MagnetON())
		m_byMagnetAlphaValue -= 15;
	else
		m_byMagnetAlphaValue = 0;

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(m_byMagnetAlphaValue, 255, 255, 255));
}

void CUIMgr::Render_PowerUpItem()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"PowerUp");

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.25f, 0.25f, 0.f);
	D3DXMatrixTranslation(&matTrans, 130.f, float(WINCY - 50), 0.f);

	matWorld = matScale * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	if (GET_INSTANCE(CObjMgr)->Get_Obj(OBJID::PLAYER)->Get_PowerUpON())
		m_byPowerUpAlphaValue -= 15;
	else
		m_byPowerUpAlphaValue = 0;

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(m_byPowerUpAlphaValue, 255, 255, 255));
}

void CUIMgr::Render_EndScene()
{
	int sum = int(m_fDistance) + m_iCoin * 10;
	TCHAR szBuff[50] = L"내 점수";
	const int d = 100;
	const int x_offset = 200;

	LONG lY = 100;
	RECT rect = { 0, lY, WINCX, lY + d };
	m_pBigFont->DrawTextW(nullptr, szBuff, lstrlen(szBuff), &rect, DT_CENTER, D3DCOLOR_ARGB(255, 255, 255, 255));

	lY += 200;
	rect = { x_offset, lY, WINCX - x_offset, lY + d };
	swprintf_s(szBuff, L"이동한 거리");
	m_pSmallFont->DrawTextW(nullptr, szBuff, lstrlen(szBuff), &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
	swprintf_s(szBuff, L"%.1fm", m_fDistance);
	m_pSmallFont->DrawTextW(nullptr, szBuff, lstrlen(szBuff), &rect, DT_RIGHT, D3DCOLOR_ARGB(255, 255, 255, 255));

	lY += d;
	rect = { x_offset, lY, WINCX - x_offset, lY + d };
	swprintf_s(szBuff, L"획득한 동전");
	m_pSmallFont->DrawTextW(nullptr, szBuff, lstrlen(szBuff), &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
	swprintf_s(szBuff, L"%d x 10", m_iCoin);
	m_pSmallFont->DrawTextW(nullptr, szBuff, lstrlen(szBuff), &rect, DT_RIGHT, D3DCOLOR_ARGB(255, 255, 255, 255));

	lY += d;
	rect = { x_offset, lY, WINCX - x_offset, lY + d };
	swprintf_s(szBuff, L"합계");
	m_pSmallFont->DrawTextW(nullptr, szBuff, lstrlen(szBuff), &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
	swprintf_s(szBuff, L"%d", sum);
	m_pSmallFont->DrawTextW(nullptr, szBuff, lstrlen(szBuff), &rect, DT_RIGHT, D3DCOLOR_ARGB(255, 255, 255, 255));

	lY += d;
	rect = { x_offset, lY, WINCX - x_offset, lY + d };
	swprintf_s(szBuff, L"계속하려면 Enter를 누르시오.");
	m_pSmallFont->DrawTextW(nullptr, szBuff, lstrlen(szBuff), &rect, DT_CENTER, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUIMgr::Render_UnDeadMode()
{
	if (!m_bUnDeadMode) return;

	TCHAR szBuff[50] = L"무적 모드";
	RECT rect = { WINCX - 500, 100, WINCX - 30, 200 };
	m_pSmallFont->DrawTextW(nullptr, szBuff, lstrlen(szBuff), &rect, DT_RIGHT, D3DCOLOR_ARGB(255, 255, 255, 255));
}