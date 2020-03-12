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
	LINEPOS tLine[4] = { {0.f, 450.f}, {300.f, 450.f}, {500.f, 250.f}, {float(WINCX), 250.f} };
	m_listLine.emplace_back(new CLine(tLine[0], tLine[1]));
	m_listLine.emplace_back(new CLine(tLine[1], tLine[2]));
	m_listLine.emplace_back(new CLine(tLine[2], tLine[3]));
//	Load_Line();

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

bool CLineMgr::Collision_Line(float _x, float* _y, int _PlayerBottom)
{
	if (m_listLine.empty())
		return false;

	CLine* pTargetLine = nullptr;

	float fDis = 55555.f;

	for (auto& pLine : m_listLine)
	{
		if (_x >= pLine->Get_Info().tLeftPos.fX
			&& _x <= pLine->Get_Info().tRightPos.fX)
		{
			float y = pLine->Get_Info().tLeftPos.fY;

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

	float x1 = pTargetLine->Get_Info().tLeftPos.fX;
	float y1 = pTargetLine->Get_Info().tLeftPos.fY;
	float x2 = pTargetLine->Get_Info().tRightPos.fX;
	float y2 = pTargetLine->Get_Info().tRightPos.fY;

	*_y = ((y2 - y1) / (x2 - x1)) * (_x - x1) + y1;

	return true;
}

void CLineMgr::Load_Line()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat"
		, GENERIC_READ, NULL, NULL
		, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load Fail", __T("Fail"), MB_OK);
		return;
	}

	LINEINFO	tInfo = {};
	DWORD		dwByte = 0;
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_listLine.emplace_back(new CLine(tInfo));
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Load Success", L"Success", MB_OKCANCEL);
}
