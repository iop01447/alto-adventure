#include "stdafx.h"
#include "Effect.h"

#include "ObjMgr.h"
#include "LineMgr.h"
#include "TextureMgr.h"


// 점프상태 아닐때 나오는 스키 뒤로 날라가는 눈 이펙트
CEffect::CEffect()
{
	ZeroMemory(&m_vPoint, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_vOrigin, sizeof(D3DXVECTOR3) * 4);
}

CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize()
{
	INFO tInfo = CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER)->Get_Info();

	m_tInfo.vSize = { float(rand()%2+2), float(rand()%2+2), 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//원점 기준 좌상단 좌표 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우상단 좌표. 
	m_vOrigin[1] = {  m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우 하단. 
	m_vOrigin[2] = {  m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// 원점 기준 좌 하단. 
	m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_fAngle = CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER)->Get_Angle() + (rand() % 20) ;
	m_fSpeed = float(rand() % 1 + 1);
	m_iAlphaValue = 255;
}

int CEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (80 > m_iAlphaValue)
		m_fSize = 0.03f;
	else if (145 > m_iAlphaValue)
		m_fSize = 0.035f;
	else if (200 > m_iAlphaValue)
		m_fSize = 0.04f;
	else if (235 > m_iAlphaValue)
		m_fSize = 0.045f;
	else
		m_fSize = 0.03f;

	m_iAlphaValue -= 5;

	return OBJ_NOEVENT;
}

void CEffect::Late_Update()
{
	if (0 >= m_tInfo.vPos.x
		|| 0 >= m_iAlphaValue)
		m_bDead = true;

	m_tInfo.vPos.x -= 2;
	//m_tInfo.vPos.y -= (GET_INSTANCE(CLineMgr)->Get_SpeedY() * 0.1f);
}

void CEffect::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"SnowEffect", L"Snow", 0);

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
		D3DCOLOR_ARGB(m_iAlphaValue, 255, 255, 255));
}

void CEffect::Release()
{
}
