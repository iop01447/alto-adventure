#include "stdafx.h"
#include "Player.h"

#include "Rock.h"
#include "Effect.h"
#include "Magnet.h"
#include "PowerUp.h"
#include "FrontEffect.h"

#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "TextureMgr.h"
#include "SceneMgr.h"



CPlayer::CPlayer()
	:m_bJump(false)
	, m_bFall(true)
	, m_bHit(false)
	, m_dwIdleTime(GetTickCount())
	, m_dwFrontEffectTime(GetTickCount())
	, m_dwDurationMagnet(0)
	, m_dwDurationPowerUp(0)
{
	ZeroMemory(&m_vPoint, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_vOrigin, sizeof(D3DXVECTOR3) * 4);
	m_byColor[0] = 255;
	m_byColor[1] = 255;
	m_byColor[2] = 255;
	m_byColor[3] = 255;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Image/player/%d.png", L"Player", L"Idle", 2);   // 0.일어선 자세 1.활강 자세
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Image/White%d.png", L"SnowEffect", L"Snow", 1);

	m_tInfo.vPos = { 150.f, 300.f, 0.f };
	m_tInfo.vSize = { 20.f, 40.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//원점 기준 좌상단 좌표 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우상단 좌표. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우 하단. 
	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// 원점 기준 좌 하단. 
	m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_fAngle = 0.f;
	m_fSpeed = 8.f;

	m_fJumpPower = 10.f;
	m_fJumpAccel = 0.f;

	Update_Rect();
}

int CPlayer::Update()
{
	Update_Rect();
	Key_Check();

	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	Jump();
	Fall();
	Collision_Object();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	if (m_dwIdleTime + 2500 < GetTickCount())
	{
		m_iPlayerState = 1;
	}
	else
	{
		m_iPlayerState = 0;
	}
	if (8.f > m_fSpeed)
	{
		m_fSpeed += 0.02f;
	}
	if (8.f < m_fSpeed)
	{
		m_fSpeed -= 0.02f;
	}

	if (m_iHP <= 0) {
		CSceneMgr::Get_Instance()->Scene_Change(SCENE::SCENE_END);
	}
}

void CPlayer::Render()
{
	Update_Rect();

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Player", L"Idle", m_iPlayerState);

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.f);
	m_tInfo.vSize = { pTexInfo->tImageInfo.Width * 0.3f, pTexInfo->tImageInfo.Height * 0.3f, 0.f };
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	matWorld = matScale * matRotZ * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(m_byColor[0], m_byColor[1], m_byColor[2], m_byColor[3]));

	Render_ItemEffect();
}

void CPlayer::Release()
{
}

void CPlayer::Collision(CObj * pOther)
{
	switch (pOther->Get_ObjID())
	{
	case OBJID::ROCK:
		if (!m_bIsPowerUpON)
		{
			if (m_pRock != pOther) {
				m_iHP = max(0, m_iHP - 1);
				m_pRock = pOther;
			}
			m_bHit = true;
			m_dwHitEffectTime = GetTickCount();
		}
		else
		{
			pOther->Set_Dead();
			for( int i = 0; i < 6; ++i)
				GET_INSTANCE(CObjMgr)->Add_Object(OBJID::EFFECT, CAbstractFactory<CRock>::Create(m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y, BYTE(1)));
		}
		break;
	case OBJID::COIN:
		++m_iCoin;
		break;
	case OBJID::MAGNET:
		m_dwDurationMagnet = GetTickCount();
		m_dwFrontEffectTime = 0;
		m_bIsMagnetON = true;
		break;
	case OBJID::POWERUP:
		m_dwDurationPowerUp = GetTickCount();
		m_dwFrontEffectTime = 0;
		m_bIsPowerUpON = true;
		break;
	case OBJID::HEART:
		m_iHP = min(5, m_iHP + 1);
		break;
	default:
		break;
	}
}

void CPlayer::Render_ItemEffect()
{
	// 바위 부수는 아이템 먹었을 때 지속시간동안 효과 발생
	if (0 != m_dwDurationPowerUp && m_dwDurationPowerUp + 10000 > GetTickCount())
	{
		if (m_dwFrontEffectTime + 1000 < GetTickCount())
		{
			GET_INSTANCE(CObjMgr)->Add_Object(OBJID::EFFECT, CAbstractFactory<CFrontEffect>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y, BYTE(1)));
			m_dwFrontEffectTime = GetTickCount();
		}
	}
	else
	{
		m_bIsPowerUpON = false;
		m_dwDurationPowerUp = 0;
	}

	if (0 != m_dwDurationMagnet && m_dwDurationMagnet + 10000 > GetTickCount())
	{
		if (m_dwFrontEffectTime + 1000 < GetTickCount())
		{
			GET_INSTANCE(CObjMgr)->Add_Object(OBJID::EFFECT, CAbstractFactory<CFrontEffect>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y, BYTE(0)));
			m_dwFrontEffectTime = GetTickCount();
		}
	}
	else
	{
		m_bIsMagnetON = false;
		m_dwDurationMagnet = 0;
	}
}

void CPlayer::Collision_Object()
{
	if(m_bHit)
	{
		if (0 != m_byColor[2] 
			&& 0!= m_byColor[3] 
			&& 255 == m_byColor[0] 
			&& m_dwHitEffectTime < GetTickCount())
		{
			m_byColor[2] = 0;
			m_byColor[3] = 0;
		}
		else if (m_dwHitEffectTime + 50 < GetTickCount())
		{
			m_byColor[2] = 255;
			m_byColor[3] = 255;
			m_byColor[0] = 0;
		}
		else if (m_dwHitEffectTime + 150 < GetTickCount())
		{
			m_byColor[0] = 75;
		}
		else if (m_dwHitEffectTime + 250 < GetTickCount())
		{
			m_byColor[0] = 150;
		}
		else if (m_dwHitEffectTime + 350 < GetTickCount())
		{
			m_byColor[0] = 255;
		}
		else
		{
			m_bHit = false;
			m_byColor[0] = 255;
			m_byColor[1] = 255;
			m_byColor[2] = 255;
			m_byColor[3] = 255;
			m_dwHitEffectTime = GetTickCount();
		}
	}
}

void CPlayer::Update_Size()
{
	// 앉았을 때 일어섰을 때 크기 조절
	//원점 기준 좌상단 좌표 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우상단 좌표. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우 하단. 
	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// 원점 기준 좌 하단. 
	m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
}

void CPlayer::Key_Check()
{
	// 캐릭터 점프 중일 때 라인의 각도 보다 조금더 몸 세우고 내려오면서 다시 맵 각도에 맞게 몸 다시 눕힘
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		m_bJump = true;
		m_dwIdleTime = GetTickCount();
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.vSize.y = 25.f;
		Update_Size();
	}
	else
	{
		m_tInfo.vSize.y = 40.f;
		Update_Size();
	}
}
void CPlayer::Jump()
{
	float fY = 0.f;
	D3DXVECTOR3 vBottomPoint = { (m_vPoint[2].x + m_vPoint[3].x) * 0.5f, (m_vPoint[2].y + m_vPoint[3].y) * 0.5f, 0.f };
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(vBottomPoint.x, &fY, int(vBottomPoint.y), &m_fAngle);

	// 플레이어가 회전했을 때 줄어든 바닥에서 플레이어 중심까지의 거리
	m_fRotHeight = (m_tInfo.vSize.y * 0.5f) * cosf(D3DXToRadian(m_fAngle));

	if (m_bJump)
	{
		m_fSpeed += 0.06f;
		m_tInfo.vPos.y -= m_fJumpPower * m_fJumpAccel - 5.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;
		m_fJumpAccel += 0.1f;

		if (bLineCol && fY + 10.f < vBottomPoint.y)
		{
			m_bJump = false;
			m_fJumpAccel = 0.f;
			m_tInfo.vPos.y = fY - m_fRotHeight;
		}
	}
	else
	{ // 점프상태 아닐 때 스키 뒤쪽으로 이펙트 생성
		GET_INSTANCE(CObjMgr)->Add_Object(OBJID::EFFECT, CAbstractFactory<CEffect>::Create(m_vPoint[3].x - 15, m_vPoint[3].y - (rand()%10 + 15)));
	}
}

void CPlayer::Fall()
{
	float fY = 0.f;
	D3DXVECTOR3 vBottomPoint = { (m_vPoint[2].x + m_vPoint[3].x) * 0.5f, (m_vPoint[2].y + m_vPoint[3].y) * 0.5f, 0.f };
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(vBottomPoint.x, &fY, int(vBottomPoint.y), &m_fAngle);
	
	// 플레이어가 회전했을 때 줄어든 바닥에서 플레이어 중심까지의 거리
	m_fRotHeight = (m_tInfo.vSize.y * 0.5f) * cosf(D3DXToRadian(m_fAngle));

	// 조건 맞으면 떨어지지말고 그냥 바로 라인 위로 올라타게 수정
	if (!m_bJump && bLineCol)
	{
		m_tInfo.vPos.y = fY - m_fRotHeight;
	}
}

