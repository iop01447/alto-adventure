#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:m_fAngle(0)
	, m_fSpeed(0)
	, m_bDead(false)
{
}

CObj::~CObj()
{
}

void CObj::Set_Pos(float _x, float _y)
{
	m_tInfo.vPos = { _x, _y, 0.f };
}
