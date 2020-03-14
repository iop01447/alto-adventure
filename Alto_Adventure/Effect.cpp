#include "stdafx.h"
#include "Effect.h"

#include "ObjMgr.h"
#include "LineMgr.h"
#include "TextureMgr.h"


// 점프상태 아닐때 나오는 스키 뒤로 날라가는 눈 이펙트
CEffect::CEffect()
	:m_iAlphaValue(255)
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

	//m_tInfo.vPos = { tInfo.vPos.x - (tInfo.vSize.x * 0.5f), tInfo.vPos.y + (tInfo.vSize.y * 0.5f), 0.f };
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
}

int CEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CEffect::Late_Update()
{
	if (0 >= m_vPoint[0].x
		|| 0 >= m_vPoint[1].x
		|| 0 >= m_vPoint[2].x
		|| 0 >= m_vPoint[3].x)
		m_bDead = true;

	if (0 >= m_iAlphaValue)
		m_bDead = true;

	m_tInfo.vPos.x -= 2;
	m_tInfo.vPos.y -= (GET_INSTANCE(CLineMgr)->Get_SpeedY());
}

void CEffect::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"SnowEffect", L"Snow", 0);

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	float fSize;
	if (80 > m_iAlphaValue)
	{
		fSize = 0.01f;
		m_tInfo.vPos.y -= 0.5f;
	}
	else if (135 > m_iAlphaValue)
	{
		fSize = 0.015f;
		m_tInfo.vPos.y -= 0.4f;
	}
	else if (175 > m_iAlphaValue)
	{
		fSize = 0.02f;
		m_tInfo.vPos.y -= 0.3f;
	}
	else if (225 > m_iAlphaValue)
	{
		fSize = 0.025f;
		m_tInfo.vPos.y -= 0.2f;
	}
	else
		fSize = 0.03f;

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, fSize, fSize, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	matWorld = matScale * matRotZ * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(m_iAlphaValue, 255, 255, 255));

	m_iAlphaValue -= 5;
}

void CEffect::Release()
{
}
