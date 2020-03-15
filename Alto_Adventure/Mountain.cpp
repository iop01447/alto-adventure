#include "stdafx.h"
#include "Mountain.h"


CMountain::CMountain(const D3DXVECTOR3 & _vPos, const D3DXVECTOR3 & _vSize, float _fSpeed)
	:m_fSpeed(_fSpeed)
{
	Initialize();

	m_tInfo.vPos = _vPos;
	m_tInfo.vSize = _vSize;
}

CMountain::CMountain()
{
	Initialize();
}


CMountain::~CMountain()
{
	Release();
}

void CMountain::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_vPoint, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_vOrigin, sizeof(D3DXVECTOR3) * 4);

	m_vOrigin[0] = { 0.f, -0.5f, 0.f };
	m_vOrigin[1] = { 0.5f, 0.5f, 0.f };
	m_vOrigin[2] = { -0.5f, 0.5f, 0.f };
}

void CMountain::Update()
{
	m_tInfo.vPos.x -= m_fSpeed;
	if (m_tInfo.vPos.x + m_tInfo.vSize.x / 2 < 0)
		m_tInfo.vPos.x = WINCX + m_tInfo.vSize.x / 2;
}

void CMountain::Render()
{
}

void CMountain::Release()
{
}