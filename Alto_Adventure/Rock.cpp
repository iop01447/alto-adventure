#include "stdafx.h"
#include "Rock.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"


CRock::CRock()
	:m_byAlphaValue(250)
{
}


CRock::~CRock()
{
}

void CRock::Initialize()
{
	m_iID = rand() % 2;

	m_fJumpPower = 10.f;
	m_fJumpAccel = 0.f;

	m_fSpeed = float(rand() % 5 + - 8);
	Update_Rect();
}

int CRock::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (0 == m_iPlayerState)
	{
		if (0 > m_tInfo.vPos.x + (m_tInfo.vSize.x *0.5f))
			return OBJ_DEAD;

		m_tInfo.vPos.x -= (GET_INSTANCE(CObjMgr)->Get_Speed());
		Fall();

		float fY;
		bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.vPos.x, &fY, int(m_tInfo.vPos.y), &m_fAngle);

		Update_Rect();
	}
	else
	{
		m_tInfo.vPos.x -= (GET_INSTANCE(CObjMgr)->Get_Speed()) + m_fSpeed;
		m_tInfo.vPos.y -= m_fJumpPower * m_fJumpAccel - 6.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;;
		m_fJumpAccel += 0.2f;

		m_fAngle += rand()%15;

		m_byAlphaValue -= 10;
		if (0 >= m_byAlphaValue)
			return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CRock::Late_Update()
{
}

void CRock::Render()
{

	Update_Rect();
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Rock", L"Idle", m_iID);

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	if (0 == m_iPlayerState)
	{
		D3DXMATRIX matScale, matTrans, matRotate, matWorld;
		D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.f);
		m_tInfo.vSize = { pTexInfo->tImageInfo.Width * 0.1f, pTexInfo->tImageInfo.Height * 0.1f, 0.f };
		D3DXMatrixRotationZ(&matRotate, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

		matWorld = matScale * matRotate * matTrans;
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{                                                                   
		D3DXMATRIX matScale, matTrans, matRotate, matWorld;
		D3DXMatrixScaling(&matScale, 0.04f, 0.04f, 0.2f);
		m_tInfo.vSize = { pTexInfo->tImageInfo.Width * 0.1f, pTexInfo->tImageInfo.Height * 0.1f, 0.f };
		D3DXMatrixRotationZ(&matRotate, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

		matWorld = matScale * matRotate * matTrans;
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CRock::Release()
{
}
