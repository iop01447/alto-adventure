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
//////////////test맵 생성///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	LINEPOS tLine[50] = { /*{0.f, 450.f}, {500.f, 750.f}, {800.f, 880.f}, {1000.f, 1100.f},{ 1500.f, 1300.f }*/ };

	tLine[0] = { -(WINCX >> 1), 250.f };
	for (int i = 1; i < 8; ++i)
	{
		tLine[i] = { float(tLine[i - 1].vPoint.x + (WINCX >> 1)), float(tLine[i - 1].vPoint.y + (rand() % 300) + 100) };
		//m_listLine.emplace_back(new CLine(tLine[i-1], tLine[i]));
	}

	D3DXVECTOR3 vPoint1, vPoint2;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < (WINCX >> 1)-1; j+=5)
		{
			D3DXVec3CatmullRom(&vPoint1, &tLine[i].vPoint, &tLine[i + 1].vPoint, &tLine[i + 2].vPoint, &tLine[i + 3].vPoint, (float(j) / (WINCX>>1)));
			D3DXVec3CatmullRom(&vPoint2, &tLine[i].vPoint, &tLine[i + 1].vPoint, &tLine[i + 2].vPoint, &tLine[i + 3].vPoint, (float(j+5) / (WINCX >> 1)));

			m_listLine.emplace_back(new CLine(LINEPOS(vPoint1.x, vPoint1.y), LINEPOS(vPoint2.x, vPoint2.y)));
		}
	}
	/*
	//D3DXVec3CatmullRom(
	//	D3DXVECTOR3* pOut,        // Result
	//	CONST D3DXVECTOR3* pV1,   
	//	CONST D3DXVECTOR3* pV2,
	//	CONST D3DXVECTOR3* pV3,
	//	CONST D3DXVECTOR3* pV4,
	//	FLOAT s
	//)

	위에 4개의 입력 되는 점이 있습니다.
	pV1, pV2, pV3, pV4 여기서 가중계수 s의 값은 0 ~ 1.0f 사이의 값을 넣게 됩니다.
	s값이 0에 가까울수록 pV2의 가까운 점이 나오게 되며,
	s값이 1에 가까울수록 pV3의 가까운 점이 나오게 됩니다.

	다시 말해서  pV1, pV4의 값은 pV2 에서 pV3의 사이 곡선을 그리는데 영향을 주게 됩니다.
	하지만 실제로 구해지는 곡선의 구간은 pV2 ~ pV3 라는걸 잊지 마시면 됩니다
	*/

	//생성된 라인들의 각도 계산 > 플레이어 속도에 적용
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