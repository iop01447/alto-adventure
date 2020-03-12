#include "stdafx.h"
#include "Player.h"

#include "KeyMgr.h"
#include "LineMgr.h"


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
	m_tInfo.vPos = { 200.f, 300.f, 0.f };
	m_tInfo.vSize = { 50.f, 100.f, 0.f };
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
}

void CPlayer::Release()
{
}

void CPlayer::Update_Size()
{
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
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_fAngle -= 7.5f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_fAngle += 7.5f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.vSize.y = 50.f;
		Update_Size();
	}
	else
	{
		m_tInfo.vSize.y = 100.f;
		Update_Size();
	}
}

void CPlayer::Jump()
{
	float fY = 0.f;
	D3DXVECTOR3 vBottomPoint = { (m_vPoint[2].x + m_vPoint[3].x)*0.5f, (m_vPoint[2].y + m_vPoint[3].y)*0.5f, 0.f };
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(vBottomPoint.x, &fY, vBottomPoint.y);

	if (bLineCol)
	{
		if (m_bJump)
		{
			//m_tInfo.fY -= m_fJumpPower * m_fJumpAccel
			//	- 9.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;

			//m_fJumpAccel += 0.2f;

			//if (bLineCol && fY < m_tInfo.fY + (m_tInfo.iCY >> 1))
			//{
			//	m_bJump = false;
			//	m_fJumpAccel = 0.f;
			//	m_tInfo.fY = fY - (m_tInfo.iCY >> 1);
			//}
		}
	}
}

void CPlayer::Fall()
{
	float fY = 0.f;
	D3DXVECTOR3 vBottomPoint = { (m_vPoint[2].x + m_vPoint[3].x)*0.5f, (m_vPoint[2].y + m_vPoint[3].y)*0.5f, 0.f };
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(vBottomPoint.x, &fY, vBottomPoint.y);

	if (bLineCol)
	{
		if (vBottomPoint.y < fY)
		{
			m_bFall = true;
		}

		if (m_bFall)
		{
			m_tInfo.vPos.y = m_tInfo.vPos.y - ( -5.8f * m_fJumpAccel * m_fJumpAccel * 0.5f ) ;
			m_fJumpAccel += 0.2f;

			if (vBottomPoint.y > fY)
			{
				m_fJumpAccel = 0.f;
				m_tInfo.vPos.y = fY - (m_tInfo.vSize.y *0.5f);
				m_bFall = false;
			}
		}
		else
		{
			m_tInfo.vPos.y = fY - (m_tInfo.vSize.y *0.5f);
			m_bFall = false;
		}
	}
	else
	{
		m_tInfo.vPos.y = fY - (m_tInfo.vSize.y *0.5f);
		m_bFall = false;
	}
}

