#include "stdafx.h"
#include "Heart.h"
#include "ObjMgr.h"
#include "TextureMgr.h"


CHeart::CHeart()
{
}


CHeart::~CHeart()
{
}

void CHeart::Initialize()
{
	m_tInfo.vScale = { 0.03f, 0.03f, 0.03f };
	m_eGroupID = GROUPID::FOREWORD_GAMEOBJECT;
}

int CHeart::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos.x -= (GET_INSTANCE(CObjMgr)->Get_Speed());
	Update_Rect();
	if (Fall())
		m_tInfo.vPos.y -= 25;

	return OBJ_NOEVENT;
}

void CHeart::Late_Update()
{
	if (m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f < 0)
		m_bDead = true;
}

void CHeart::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Heart");

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, 0.f);
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

void CHeart::Release()
{
}

void CHeart::Collision(CObj * pOther)
{
	if (pOther->Get_ObjID() != OBJID::PLAYER) return;
	m_bDead = true;
}