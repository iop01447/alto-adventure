#include "stdafx.h"
#include "Rock.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"


CRock::CRock()
{
}


CRock::~CRock()
{
}

void CRock::Initialize()
{
	m_iID = rand() % 2;
}

int CRock::Update()
{
	m_tInfo.vPos.x -= (GET_INSTANCE(CObjMgr)->Get_Speed());
	Update_Rect();
	Fall();

	float fY;
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.vPos.x, &fY, int(m_tInfo.vPos.y), &m_fAngle);

	return OBJ_NOEVENT;
}

void CRock::Late_Update()
{
}

void CRock::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Rock", L"Idle", m_iID);

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.f);
	m_tInfo.vSize = { pTexInfo->tImageInfo.Width * 0.1f, pTexInfo->tImageInfo.Height * 0.1f, 0.f };
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	matWorld = matScale * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CRock::Release()
{
}
