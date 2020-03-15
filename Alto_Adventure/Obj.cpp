#include "stdafx.h"
#include "Obj.h"
#include "LineMgr.h"
#include "Line.h"


CObj::CObj()
	:m_fAngle(0)
	, m_fSpeed(0)
	, m_bDead(false)
	, m_iPlayerState(0)
{
}

CObj::~CObj()
{
}

void CObj::Set_Pos(float _x, float _y)
{
	m_tInfo.vPos = { _x, _y, 0.f };
}

void CObj::Fall()
{
	m_pLine = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.vPos.x);

	if (m_pLine)
	{
		m_tInfo.vPos.x = m_pLine->Get_Info().tRightPos.vPoint.x;
		m_tInfo.vPos.y = m_pLine->Get_Info().tRightPos.vPoint.y - m_tInfo.vSize.y / 4.f;
		return;
	}
}
