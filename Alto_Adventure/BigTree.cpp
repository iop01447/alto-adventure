#include "stdafx.h"
#include "BigTree.h"
#include "TextureMgr.h"
#include "ObjMgr.h"

bool CBigTree::m_bToggle{ 0 };

CBigTree::CBigTree()
{
}


CBigTree::~CBigTree()
{
}

void CBigTree::Initialize()
{
	m_fReflection = rand() % 2 ? -1.f : 1.f;
	m_bToggle = !m_bToggle;
	m_zID = m_bToggle;
	if (m_zID) {
		m_eGroupID = GROUPID::FOREWORD_GAMEOBJECT;
		m_tInfo.vScale = { 1.f, 1.f, 1.f };
	}
	else {
		m_eGroupID = GROUPID::BEFORE_GAMEOBJECT;
		m_tInfo.vScale = { 0.5f, 0.5f, 0.5f };
	}
}

int CBigTree::Update()
{
	if (0 > m_tInfo.vPos.x + (m_tInfo.vSize.x *0.5f))
		return OBJ_DEAD;

	m_tInfo.vPos.x -= (GET_INSTANCE(CObjMgr)->Get_Speed());
	Update_Rect();
	if (Fall() && m_zID)
		m_tInfo.vPos.y += 200;
	
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
	D3DXMatrixScaling(&matScale, m_fReflection * m_tInfo.vScale.x, m_tInfo.vScale.y, 0.f);
	m_tInfo.vSize = { pTexInfo->tImageInfo.Width * m_tInfo.vScale.x, pTexInfo->tImageInfo.Height * m_tInfo.vScale.y, 0.f };
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
