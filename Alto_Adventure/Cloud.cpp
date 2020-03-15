#include "stdafx.h"
#include "Cloud.h"
#include "TextureMgr.h"


CCloud::CCloud()
{
	Initialize();
}


CCloud::~CCloud()
{
}

void CCloud::Initialize()
{
	m_iID = rand() % 23;
	m_tInfo.vPos = { float(rand() % WINCX), 100.f + float(rand()%300), 0.f };

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Cloud", L"Idle", m_iID);
	m_tInfo.vSize = { float(pTexInfo->tImageInfo.Width), float(pTexInfo->tImageInfo.Height), 0.f };

	m_fSpeed = 1.f + (rand() / (float)RAND_MAX) * 1.f;
}

int CCloud::Update()
{
	m_tInfo.vPos.x -= m_fSpeed;
	if (m_tInfo.vPos.x + m_tInfo.vSize.x / 2 < 0) {
		Initialize();
		m_tInfo.vPos.x = WINCX + m_tInfo.vSize.x / 2;
	}

	return OBJ_NOEVENT;
}

void CCloud::Late_Update()
{
}

void CCloud::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Cloud", L"Idle", m_iID);

	int iAlpha = int(255 * 0.1f);
	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	matWorld = matScale * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(iAlpha, 255, 255, 255));
}

void CCloud::Release()
{
}
