#include "stdafx.h"
#include "Player.h"

#include "Effect.h"

#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "TextureMgr.h"


CPlayer::CPlayer()
	:m_bJump(false)
	, m_bFall(true)
	, m_dwIdleTime(GetTickCount())
	, m_iFrameNum(0)
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
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Image/player/%d.png", L"Player", L"Idle", 2);   // 0.�Ͼ �ڼ� 1.Ȱ�� �ڼ�
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Image/White%d.png", L"SnowEffect", L"Snow", 1);

	m_tInfo.vPos = { 150.f, 300.f, 0.f };
	m_tInfo.vSize = { 20.f, 40.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//���� ���� �»�� ��ǥ 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//���� ���� ���� ��ǥ. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//���� ���� �� �ϴ�. 
	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// ���� ���� �� �ϴ�. 
	m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_fAngle = 0.f;
	m_fSpeed = 1.f;

	m_fJumpPower = 12.f;
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
	if (m_dwIdleTime + 2500 < GetTickCount())
	{
		m_iFrameNum = 1;
		m_fSpeed = 5.f;
	}
	else
	{
		m_iFrameNum = 0;
		m_fSpeed = 1.f;
	}
}

void CPlayer::Render()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Player", L"Idle", m_iFrameNum);

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

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
	// �ɾ��� �� �Ͼ�� �� ũ�� ����
	//���� ���� �»�� ��ǥ 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//���� ���� ���� ��ǥ. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//���� ���� �� �ϴ�. 
	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// ���� ���� �� �ϴ�. 
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
	// if( �÷��̾� ���� �� && �����̽��� Pressing )
	//		ĳ���� ȸ��


	// ĳ���� ���� ���� �� ������ ���� ���� ���ݴ� �� ����� �������鼭 �ٽ� �� ������ �°� �� �ٽ� ����
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
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

	// �÷��̾ ȸ������ �� �پ�� �ٴڿ��� �÷��̾� �߽ɱ����� �Ÿ�
	m_fRotHeight = (m_tInfo.vSize.y * 0.5f) * cosf(D3DXToRadian(m_fAngle));

	if (m_bJump)
	{
		m_tInfo.vPos.y -= m_fJumpPower * m_fJumpAccel - 6.8f * m_fJumpAccel * m_fJumpAccel * 0.5f;
		m_fJumpAccel += 0.1f;

		if (bLineCol && fY + 5.f < vBottomPoint.y)
		{
			m_bJump = false;
			m_fJumpAccel = 0.f;
			m_tInfo.vPos.y = fY - m_fRotHeight;
		}
	}
	else
	{ // �������� �ƴ� �� ��Ű �������� ����Ʈ ����
		GET_INSTANCE(CObjMgr)->Add_Object(OBJID::EFFECT, CAbstractFactory<CEffect>::Create(m_vPoint[3].x - 25, m_vPoint[3].y - 15));
	}
}

void CPlayer::Fall()
{
	float fY = 0.f;
	D3DXVECTOR3 vBottomPoint = { (m_vPoint[2].x + m_vPoint[3].x) * 0.5f, (m_vPoint[2].y + m_vPoint[3].y) * 0.5f, 0.f };
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(vBottomPoint.x, &fY, int(vBottomPoint.y), &m_fAngle);
	
	// �÷��̾ ȸ������ �� �پ�� �ٴڿ��� �÷��̾� �߽ɱ����� �Ÿ�
	m_fRotHeight = (m_tInfo.vSize.y * 0.5f) * cosf(D3DXToRadian(m_fAngle));

	// ���� ������ ������������ �׳� �ٷ� ���� ���� �ö�Ÿ�� ����
	if (!m_bJump && bLineCol)
	{
		m_tInfo.vPos.y = fY - m_fRotHeight;
	}
}

