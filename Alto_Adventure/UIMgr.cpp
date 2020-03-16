#include "stdafx.h"
#include "UIMgr.h"
#include "Device.h"
#include "ObjMgr.h"
#include "Player.h"

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

	D3DXFONT_DESC desc;
	desc.CharSet = HANGUL_CHARSET;
	lstrcpy(desc.FaceName, L"");
	desc.Height = static_cast<int>(_dwSize * 2.083f);
	desc.Width = _dwSize;
	desc.Weight = FW_NORMAL;
	desc.Quality = DEFAULT_QUALITY;
	desc.MipLevels = 1;
	desc.Italic = 0;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(CDevice::Get_Instance()->Get_Device(), &desc, &m_pFont);
}

void CUIMgr::Update()
{
	CPlayer* player = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
	m_iCoin = player->Get_Coin();
}

void CUIMgr::Render()
{
	TCHAR szBuf[64] = L"";
	swprintf_s(szBuf, L"COIN %d", m_iCoin);

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixTranslation(&matTrans, 40, 30, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUIMgr::Release()
{
	m_pFont->Release();
}
