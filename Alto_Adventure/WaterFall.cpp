#include "stdafx.h"
#include "WaterFall.h"
#include "ObjMgr.h"
#include "TextureMgr.h"


CWaterFall::CWaterFall()
{
}


CWaterFall::~CWaterFall()
{
}

void CWaterFall::Initialize()
{
	m_tInfo.vScale = { 0.3f, 1.5f, 0.f };
	m_eGroupID = GROUPID::FOREWORD_GAMEOBJECT;
}

int CWaterFall::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos.x -= (GET_INSTANCE(CObjMgr)->Get_Speed());
	Update_Rect();
	Update_ParticlePos();

	return OBJ_NOEVENT;
}

void CWaterFall::Late_Update()
{
	if (m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f < 0)
		m_bDead = true;
}

void CWaterFall::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"SnowEffect", L"Snow", 0);
	
	float fAlpha = 0.7f;
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
		D3DCOLOR_ARGB(int(255 * fAlpha), 4, 52, 100));

	for (int i = 0; i < 50; ++i) {
		D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vParticlePos[i].x 
			, m_vParticlePos[i].y, 0.f);

		matWorld = matScale * matTrans;
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(int(255 * 0.8f), 255, 255, 255));
	}
}

void CWaterFall::Release()
{
}

void CWaterFall::Update_ParticlePos()
{
	if (GetTickCount() - m_dwLateParticleUpdate < m_dwParticleUpdate) return;
	m_dwLateParticleUpdate = GetTickCount();


	for (int i = 0; i < 50; ++i) {
		m_vParticlePos[i] = { -80 + m_tInfo.vPos.x + rand() % 160, float(rand() % WINCY), 0.f };
	}
}
