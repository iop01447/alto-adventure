#include "stdafx.h"
#include "Magnet.h"
#include "ObjMgr.h"
#include "TextureMgr.h"


CMagnet::CMagnet()
{
}

CMagnet::~CMagnet()
{
	Release();
}

void CMagnet::Initialize()
{
	m_tInfo.vScale = { 0.06f, 0.06f, 0.f };
	m_eGroupID = GROUPID::FOREWORD_GAMEOBJECT;
}

int CMagnet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos.x -= (GET_INSTANCE(CObjMgr)->Get_Speed());
	Update_Rect();
	if (Fall())
		m_tInfo.vPos.y -= 25;

	return OBJ_NOEVENT;
}

void CMagnet::Late_Update()
{
	if (m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f < 0)
		m_bDead = true;

	if (GET_INSTANCE(CObjMgr)->Get_Obj(OBJID::PLAYER)->Get_MagnetON())
	{
		D3DXVECTOR3 vPlayer = GET_INSTANCE(CObjMgr)->Get_Obj(OBJID::PLAYER)->Get_Info().vPos;
		vPlayer -= m_tInfo.vPos;
		if (WINCX >> 1 > sqrtf((vPlayer.x * vPlayer.x) + (vPlayer.y * vPlayer.y)))
			m_tInfo.vPos.x -= 15;
	}
}

void CMagnet::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Magnet");

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.08f, 0.08f, 0.f);
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

void CMagnet::Release()
{
}

void CMagnet::Collision(CObj * pOther)
{
	if (pOther->Get_ObjID() != OBJID::PLAYER)
		return;
	m_bDead = true;
}
