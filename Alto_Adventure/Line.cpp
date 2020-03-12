#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
{
}

CLine::CLine(LINEPOS& _tLeft, LINEPOS& _tRight)
	: m_tInfo(_tLeft, _tRight)
{
}

CLine::CLine(LINEINFO& _tLine)
	: m_tInfo(_tLine)
{

}

CLine::~CLine()
{
}

void CLine::Initialize()
{
	// ���� ���� ���
	D3DXVECTOR3 vLineVec = m_tInfo.tRightPos.vPoint - m_tInfo.tLeftPos.vPoint;
	D3DXVec3Normalize(&vLineVec, &vLineVec);

	// �ٶ󺸴� ����
	m_tInfo.vLook = { 1.f, 0.f, 0.f };		

	float fRadian = acosf(D3DXVec3Dot(&m_tInfo.vLook, &vLineVec));
	m_fAngle = D3DXToDegree(fRadian);

	if (m_tInfo.tRightPos.vPoint.y < m_tInfo.tLeftPos.vPoint.y)
		m_fAngle = -m_fAngle;
}

void CLine::Update()
{
	// ���� ������ ���� ���� �ӵ� �ٸ���
	m_tInfo.tLeftPos.vPoint.x -= 2.f;
	m_tInfo.tRightPos.vPoint.x -= 2.f;

	m_tInfo.tLeftPos.vPoint.y -= 1.5f;
	m_tInfo.tRightPos.vPoint.y -= 1.5f;
}

void CLine::Render(HDC _DC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(_DC, (int)(m_tInfo.tLeftPos.vPoint.x + fScrollX), (int)(m_tInfo.tLeftPos.vPoint.y + fScrollY), nullptr);
	LineTo(_DC, (int)(m_tInfo.tRightPos.vPoint.x + fScrollX), (int)(m_tInfo.tRightPos.vPoint.y + fScrollY));
}
