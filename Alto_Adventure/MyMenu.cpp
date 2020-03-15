#include "stdafx.h"
#include "MyMenu.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "TextureMgr.h"


CMyMenu::CMyMenu()
{
}

CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Image/Menu0.png", L"Menu", L"Menu", 1);
	CSoundMgr::Get_Instance()->PlayBGM(L"MenuBGM.wav");
}

void CMyMenu::Update()
{
}

void CMyMenu::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
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
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMyMenu::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
}
