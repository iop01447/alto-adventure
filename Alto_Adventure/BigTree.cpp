#include "stdafx.h"
#include "BigTree.h"
#include "TextureMgr.h"
#include "ObjMgr.h"

CBigTree::CBigTree()
{
}


CBigTree::~CBigTree()
{
}

void CBigTree::Initialize()
{
	m_fReflection = rand() % 2 ? -1.f : 1.f;
	m_eGroupID = GROUPID::BEFORE_GAMEOBJECT;
}

int CBigTree::Update()
{
	m_tInfo.vPos.x -= (GET_INSTANCE(CObjMgr)->Get_Speed());
	Update_Rect();
	Fall();

	return OBJ_NOEVENT;
}

void CBigTree::Late_Update()
{
}

void CBigTree::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"BigTree");

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_fReflection * 0.5f, 0.5f, 0.f);
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

void CBigTree::Release()
{
}