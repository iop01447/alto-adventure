#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"


CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
//////////////test¸Ê »ý¼º///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	LINEPOS tLine[50] = { /*{0.f, 450.f}, {500.f, 750.f}, {800.f, 880.f}, {1000.f, 1100.f},{ 1500.f, 1300.f }*/ };

	tLine[0] = { 0.f, 450.f };
	for (int i = 1; i < 50; ++i)
	{
		tLine[i] = { float(tLine[i - 1].vPoint.x + (WINCX >> 1)), float(tLine[i - 1].vPoint.y + (rand() % 300) + 200) };
		m_listLine.emplace_back(new CLine(tLine[i-1], tLine[i]));
	}

	//m_listLine.emplace_back(new CLine(tLine[0], tLine[1]));
	//m_listLine.emplace_back(new CLine(tLine[1], tLine[2]));
	//m_listLine.emplace_back(new CLine(tLine[2], tLine[3]));
	//m_listLine.emplace_back(new CLine(tLine[3], tLine[4]));

	for (auto& pLine : m_listLine)
		pLine->Initialize();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void CLineMgr::Update()
{
	for (auto& pLine : m_listLine)
		pLine->Update();
}

void CLineMgr::Render(HDC _DC)
{
	for (auto& pLine : m_listLine)
		pLine->Render(_DC);
}

void CLineMgr::Release()
{
	for_each(m_listLine.begin(), m_listLine.end(), Safe_Delete<CLine*>);
	m_listLine.clear();
}

bool CLineMgr::Collision_Line(float _x, float* _y, int _PlayerBottom, float* _fAngle )
{
	if (m_listLine.empty())
		return false;

	CLine* pTargetLine = nullptr;

	float fDis = -1.f;

	for (auto& pLine : m_listLine)
	{
		if (_x >= pLine->Get_Info().tLeftPos.vPoint.x
			&& _x <= pLine->Get_Info().tRightPos.vPoint.x)
		{
			float y = pLine->Get_Info().tLeftPos.vPoint.y;

			if (0 > fDis)
			{
				pTargetLine = pLine;
				fDis = abs(_PlayerBottom - y);
			}

			if (_PlayerBottom <= y)
			{
				if (fDis > abs(_PlayerBottom - y))
				{
					pTargetLine = pLine;
					fDis = abs(_PlayerBottom - y);
				}
			}
		}
	}

	if (!pTargetLine)
		return false;

	float x1 = pTargetLine->Get_Info().tLeftPos.vPoint.x;
	float y1 = pTargetLine->Get_Info().tLeftPos.vPoint.y;
	float x2 = pTargetLine->Get_Info().tRightPos.vPoint.x;
	float y2 = pTargetLine->Get_Info().tRightPos.vPoint.y;

	*_y = ((y2 - y1) / (x2 - x1)) * (_x - x1) + y1;
	*_fAngle = pTargetLine->Get_Angle();

	for (auto& pLine : m_listLine)
		pLine->Set_SpeedX(pTargetLine->Get_Angle() / 15.f);

	return true;
}