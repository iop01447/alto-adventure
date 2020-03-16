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
}

void CUIMgr::Update()
{
	CPlayer* player = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
	m_iCoin = player->Get_Coin();

	m_iDistance += 10;
}

void CUIMgr::Render()
{
	Render_Coin();
	Render_HP();
	Render_Distance();
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
	TCHAR szBuff[50] = L"";
	switch (m_iHP)
	{
	case 1:
		swprintf_s(szBuff, L"¢¾");
		break;
	case 2:
		swprintf_s(szBuff, L"¢¾ ¢¾");
		break;
	case 3:
		swprintf_s(szBuff, L"¢¾ ¢¾ ¢¾");
		break;
	default:
		break;
	}

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 38, 80, 0.f);
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
	m_pSmallFont->DrawTextW(CDevice::Get_Instance()->Get_Sprite(), szBuff, lstrlen(szBuff), nullptr, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0));
}

void CUIMgr::Render_Distance()
{
	TCHAR szBuff[50] = L"";
	swprintf_s(szBuff, L"%dm", m_iDistance);

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 0, 0, 0.f);
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
	RECT rect = { WINCX - 500, 30, WINCX - 30, 200 };
	m_pBigFont->DrawTextW(CDevice::Get_Instance()->Get_Sprite(), szBuff, lstrlen(szBuff), &rect, DT_RIGHT, D3DCOLOR_ARGB(255, 255, 255, 255));
}
