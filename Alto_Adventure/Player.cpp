#include "stdafx.h"
#include "Player.h"

#include "KeyMgr.h"
#include "LineMgr.h"
#include "TextureMgr.h"


CPlayer::CPlayer()
	:m_bJump(false), m_bFall(true)
{
	ZeroMemory(&m_vPoint, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_vOrigin, sizeof(D3DXVECTOR3) * 4);
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	//GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Image/player.png", L"Cube");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Image/player/%d.png", L"Player", L"Idle", 1);

	m_tInfo.vPos = { 100.f, 300.f, 0.f };
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
	m_fSpeed = 5.f;

	m_fJumpPower = 20.f;
	m_fJumpAccel = 0.f;
}

int CPlayer::Update()
{
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

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	MoveToEx(_DC, int(m_vPoint[1].x),int( m_vPoint[1].y), nullptr);

	for (int i = 2; i < 4; ++i)
		LineTo(_DC, int(m_vPoint[i].x), int(m_vPoint[i].y));
	LineTo(_DC, int(m_vPoint[0].x), int(m_vPoint[0].y));

	HPEN Brush, oldBrush;

	Brush = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	oldBrush = (HPEN)SelectObject(_DC, Brush);

	LineTo(_DC, int(m_vPoint[1].x), int(m_vPoint[1].y));

	SelectObject(_DC, oldBrush);
	DeleteObject(Brush);

	//////////////

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Player", L"Idle", 0);

	float fCenterX = pTexInfo->tImageInfo.Width / 2.f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0));
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	matWorld = matScale * matRotZ * matTrans;
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release()
{
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
	if (!m_bFall)
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
			m_fAngle -= 7.5f;

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
			m_fAngle += 7.5f;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		m_bJump = true;

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
			m_tInfo.vPos.y -= m_fJumpPower * m_fJumpAccel - 9.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;
 			m_fJumpAccel += 0.2f;

 			if (bLineCol && fY + 2.f < vBottomPoint.y)
			{
				m_bJump = false;
				m_fJumpAccel = 0.f;
				m_tInfo.vPos.y = fY - m_fRotHeight;
			}
		}
}

void CPlayer::Fall()
{
	float fY = 0.f;
	D3DXVECTOR3 vBottomPoint = { (m_vPoint[2].x + m_vPoint[3].x) * 0.5f, (m_vPoint[2].y + m_vPoint[3].y) * 0.5f, 0.f };
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(vBottomPoint.x, &fY, int(vBottomPoint.y), &m_fAngle);
	
	// 플레이어가 회전했을 때 줄어든 바닥에서 플레이어 중심까지의 거리
	m_fRotHeight = (m_tInfo.vSize.y * 0.5f) * cosf(D3DXToRadian(m_fAngle));

	if (!m_bJump && bLineCol)
	{
		if (/*소수점 때문에 일어나는 떨림 방지*/  
			vBottomPoint.y + 3.f < fY 
		) 
			m_bFall = true;
	
		if (m_bFall)
		{
			m_tInfo.vPos.y = m_tInfo.vPos.y - ( -5.8f * m_fJumpAccel * m_fJumpAccel * 0.5f ) ;
			m_fJumpAccel += 0.2f;

			if (vBottomPoint.y >= fY)
			{
				m_fJumpAccel = 0.f;
				m_tInfo.vPos.y = fY - m_fRotHeight;
				m_bFall = false;
			}
		}
		else
		{
			m_tInfo.vPos.y = fY - m_fRotHeight;
			m_bFall = false;
		}
	}
}

