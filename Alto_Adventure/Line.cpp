#include "stdafx.h"
#include "Line.h"

#include "ScrollMgr.h"
#include "ObjMgr.h"

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
	// 라인 각도 계산
	D3DXVECTOR3 vLineVec = m_tInfo.tRightPos.vPoint - m_tInfo.tLeftPos.vPoint;
	D3DXVec3Normalize(&vLineVec, &vLineVec);

	// 바라보는 방향
	m_tInfo.vLook = { 1.f, 0.f, 0.f };		

	float fRadian = acosf(D3DXVec3Dot(&m_tInfo.vLook, &vLineVec));
	m_fAngle = D3DXToDegree(fRadian);

	if (m_tInfo.tRightPos.vPoint.y < m_tInfo.tLeftPos.vPoint.y)
		m_fAngle = -m_fAngle;

	m_fSpeedX = 0;
	m_fSpeedY = 1.5f;
}

void CLine::Update()
{
	m_tInfo.tLeftPos.vPoint.x -= m_fSpeedX;
	m_tInfo.tRightPos.vPoint.x -= m_fSpeedX;

	if (200.f > CObjMgr::Get_Instance()->Get_Top())
	{
		m_fSpeedY = -1.f;
	}
	else if(500.f < CObjMgr::Get_Instance()->Get_Top())
	{
		m_fSpeedY = 1.5f;
	}
	m_tInfo.tLeftPos.vPoint.y -= m_fSpeedY;
	m_tInfo.tRightPos.vPoint.y -= m_fSpeedY;
}

void CLine::Render(HDC _DC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(_DC, (int)(m_tInfo.tLeftPos.vPoint.x + fScrollX), (int)(m_tInfo.tLeftPos.vPoint.y + fScrollY), nullptr);
	LineTo(_DC, (int)(m_tInfo.tRightPos.vPoint.x + fScrollX), (int)(m_tInfo.tRightPos.vPoint.y + fScrollY));
}
