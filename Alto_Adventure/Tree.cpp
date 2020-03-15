#include "stdafx.h"
#include "Tree.h"
#include "TextureMgr.h"
#include "ObjMgr.h"


CTree::CTree()
{
}


CTree::~CTree()
{
}

void CTree::Initialize()
{
	m_iID = rand() % 3;
}

int CTree::Update()
{
	m_tInfo.vPos.x -= (GET_INSTANCE(CObjMgr)->Get_Speed());
	Update_Rect();
	Fall();

	return OBJ_NOEVENT;
}

void CTree::Late_Update()
{
}

void CTree::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Tree", L"Idle", m_iID);

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.f);
	m_tInfo.vSize = { pTexInfo->tImageInfo.Width * 0.5f, pTexInfo->tImageInfo.Height * 0.5f, 0.f };
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	matWorld = matScale * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CTree::Release()
{
}
