#include "stdafx.h"
#include "FrontEffect.h"

#include "ObjMgr.h"
#include "TextureMgr.h"



CFrontEffect::CFrontEffect()
{
	ZeroMemory(&m_vPoint, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_vOrigin, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_byColor, sizeof(BYTE) * 4);
}

CFrontEffect::~CFrontEffect()
{
	Release();
}

void CFrontEffect::Initialize()
{
	m_fAngle = CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER)->Get_Angle() + (rand() % 20);

	m_tInfo.vSize = {100.f, 100.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	m_byColor[0] = 200;
	m_byColor[1] = 255;
	m_byColor[2] = 255;
	m_byColor[3] = 255;
}

int CFrontEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	m_fAngle = CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER)->Get_Angle() + (rand() % 20);


	return OBJ_NOEVENT;
}

void CFrontEffect::Late_Update()
{
	const INFO& tInfo = GET_INSTANCE(CObjMgr)->Get_Obj(OBJID::PLAYER)->Get_Info();
	m_tInfo.vPos = { tInfo.vPos.x, tInfo.vPos.y, 0.f };

	m_byColor[0] -= 5;

	if (0 >= m_byColor[0])
		m_bDead = true;
}

void CFrontEffect::Render()
{
	m_fSize = 0.3f;

	const TEXINFO* pTexInfo;
	if(0 == m_iPlayerState)
		pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"FrontEffect", L"FrontEffect", 1);
	else
		pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"FrontEffect", L"FrontEffect", 0);
	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle + 45));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	matWorld = matScale * matRotZ * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(m_byColor[0], m_byColor[1], m_byColor[2], m_byColor[3]));
}

void CFrontEffect::Release()
{
}
