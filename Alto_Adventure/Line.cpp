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

void CLine::Render(HDC _DC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(_DC, (int)(m_tInfo.tLeftPos.fX + fScrollX), (int)(m_tInfo.tLeftPos.fY + fScrollY), nullptr);
	LineTo(_DC, (int)(m_tInfo.tRightPos.fX + fScrollX), (int)(m_tInfo.tRightPos.fY + fScrollY));
}
