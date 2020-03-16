#include "stdafx.h"
#include "LineMgr.h"

#include "Line.h"
#include "ObjMgr.h"

#include "AbstractFactory.h"
#include "TextureMgr.h"
#include "Rock.h"
#include "Tree.h"
#include "BigTree.h"
#include "Coin.h"
#include "Magnet.h"
#include "Heart.h"
#include "PowerUp.h"
#include "WaterFall.h"



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
	CTextureMgr::Get_Instance()->InsertTexture(CTextureMgr::MULTITEX, L"../Image/rock/%d.png", L"Rock", L"Idle", 2);
	CTextureMgr::Get_Instance()->InsertTexture(CTextureMgr::MULTITEX, L"../Image/tree/%d.png", L"Tree", L"Idle", 3);
	CTextureMgr::Get_Instance()->InsertTexture(CTextureMgr::SINGLETEX, L"../Image/big-tree.png", L"BigTree");
	CTextureMgr::Get_Instance()->InsertTexture(CTextureMgr::SINGLETEX, L"../Image/coin.png", L"Coin");
	CTextureMgr::Get_Instance()->InsertTexture(CTextureMgr::SINGLETEX, L"../Image/Magnet.png", L"Magnet");
	CTextureMgr::Get_Instance()->InsertTexture(CTextureMgr::SINGLETEX, L"../Image/heart.png", L"Heart");
	CTextureMgr::Get_Instance()->InsertTexture(CTextureMgr::SINGLETEX, L"../Image/PowerUp.png", L"PowerUp");
	m_dwLastBackObjCreate = GetTickCount();

	//CObj* pObj = CAbstractFactory<CWaterFall>::Create(WINCX / 2, WINCY / 2);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::WATERFALL, pObj);

//////////////test맵 생성///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	D3DXVECTOR3 vLine0 = { -(WINCX >> 1), 250.f, 0.f };
	m_vecLinePoint.emplace_back(vLine0);

	// 랜덤으로 WINCX >> 1 만큼 떨어진 포인트 생성 후 m_vecLinePoint 에 저장(직선 데이터)
	for (int i = 1; i < 6; ++i)
	{
		D3DXVECTOR3 vLinePoint = { float(m_vecLinePoint[i - 1].x + (WINCX >> 1)), float(m_vecLinePoint[i - 1].y + (rand() % 100) + 100) , 0.f };
		m_vecLinePoint.emplace_back(vLinePoint);
	}

	// m_vecLinePoint의 포인트들을 곡선으로 만들고 라인으로 만들 수 있게 list<CLine*> m_listLine 에 저장 (한 직선 사이의 곡선 데이터)
	for (size_t i = 0; i < m_vecLinePoint.size()-3; ++i)
	{
		for (int j = 0; j < (WINCX >> 1)-1; j+=3)
		{
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
			D3DXVECTOR3 vPoint1, vPoint2;
			D3DXVec3CatmullRom(&vPoint1, &m_vecLinePoint[i], &m_vecLinePoint[i + 1], &m_vecLinePoint[i + 2], &m_vecLinePoint[i + 3], (float(j) / (WINCX>>1)));
			D3DXVec3CatmullRom(&vPoint2, &m_vecLinePoint[i], &m_vecLinePoint[i + 1], &m_vecLinePoint[i + 2], &m_vecLinePoint[i + 3], (float(j+3) / (WINCX >> 1)));

			m_listLine.emplace_back(new CLine(LINEPOS(vPoint1.x, vPoint1.y), LINEPOS(vPoint2.x, vPoint2.y)));
		}
	}

	//g_pLine의 Draw함수를 쓰기위해 D3DXVECTOR2 배열로 포인트들을 옮기는 작업
	for (auto& pLine : m_listLine)
	{
		pLine->Initialize();
		D3DXVECTOR2 vPoint = { pLine->Get_Info().tLeftPos.vPoint.x, pLine->Get_Info().tLeftPos.vPoint.y };
		m_vecPointList.emplace_back(vPoint) ;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void CLineMgr::Update()
{
	// 플레이어가 위치한 부분의 직선의 각도 + 플레이어의 상태에 따라 속도를 더함
	for (auto& pLine : m_listLine)
		pLine->Update();
	
	GET_INSTANCE(CLineMgr)->Set_LinePoint(m_listLine.front()->Get_SpeedX() + GET_INSTANCE(CObjMgr)->Get_Speed(), m_listLine.front()->Get_SpeedY());

	// 업데이트된 포인트들의 위치 갱신
	m_vecPointList.clear();
	for (auto& pLine : m_listLine)
	{
		D3DXVECTOR2 vPoint = { pLine->Get_Info().tLeftPos.vPoint.x, pLine->Get_Info().tLeftPos.vPoint.y };
		m_vecPointList.emplace_back(vPoint);
	}
}

void CLineMgr::Late_Update()
{
	// 맵을 넘어간 포인트들은 삭제하고 새로운 맵을 랜덤으로 생성해 추가

	// 저장해 두었던 직선의 세번째 포인트가 0보다 작아지면
	if ( 0 > m_vecLinePoint[2].x )
	{
		// 첫번째 포인트 삭제
		m_vecLinePoint.erase(m_vecLinePoint.begin());

		// 새로운 직선 포인트를 직선 포인트들을 모은 변수에 추가
		D3DXVECTOR3 vLinePoint = { float(m_vecLinePoint[m_vecLinePoint.size() - 1].x + (WINCX >> 1)), float(m_vecLinePoint[m_vecLinePoint.size() - 1].y + (rand() % 100) + 100) , 0.f };
		m_vecLinePoint.emplace_back(vLinePoint);

		// 기존에 있던 직선 포인트들과 새로 들어온 직선 포인트 사이의 곡선 포인트들을 갱신
		for_each(m_listLine.begin(), m_listLine.end(), Safe_Delete<CLine*>);
		m_listLine.clear();

		for (size_t i = 0; i < m_vecLinePoint.size() - 3; ++i)
		{
			for (int j = 0; j < (WINCX >> 1) - 1; j += 3)
			{
				D3DXVECTOR3 vPoint1, vPoint2;
				D3DXVec3CatmullRom(&vPoint1, &m_vecLinePoint[i], &m_vecLinePoint[i+1], &m_vecLinePoint[i+2], &m_vecLinePoint[i+3], (float(j) / (WINCX >> 1)));
				D3DXVec3CatmullRom(&vPoint2, &m_vecLinePoint[i], &m_vecLinePoint[i+1], &m_vecLinePoint[i+2], &m_vecLinePoint[i+3], (float(j + 3) / (WINCX >> 1)));

				m_listLine.emplace_back(new CLine(LINEPOS(vPoint1.x, vPoint1.y), LINEPOS(vPoint2.x, vPoint2.y)));
			}
		}

		m_vecPointList.clear();
		for (auto& pLine : m_listLine)
		{
			pLine->Initialize();
			D3DXVECTOR2 vPoint = { pLine->Get_Info().tLeftPos.vPoint.x, pLine->Get_Info().tLeftPos.vPoint.y };
			m_vecPointList.emplace_back(vPoint);
		}
	}

	Create_Object();
	Create_BackObject();
}

void CLineMgr::Render()
{
	g_pLine->Begin();

	// X축 라인 색칠
	D3DXVECTOR2* pPoint = nullptr;
	pPoint = new D3DXVECTOR2[m_vecPointList.size()];

	for (size_t i = 0; i < m_vecPointList.size(); ++i)
		pPoint[i] = m_vecPointList[i];
	g_pLine->Draw(pPoint, m_vecPointList.size(), D3DCOLOR_ARGB(255, 255, 255, 255)); 

	// Y축 라인 색칠
	for (auto& pLine : m_listLine) 
		pLine->Render(); 

	g_pLine->End();

	delete[] pPoint;
	pPoint = nullptr;
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

 CLine * CLineMgr::Collision_Line(float _x)
 {
	 if (m_listLine.empty())
		 return false;

	 CLine* pTargetLine = nullptr;

	 for (auto& pLine : m_listLine)
	 {
		 if (_x >= pLine->Get_Info().tLeftPos.vPoint.x
			 && _x <= pLine->Get_Info().tRightPos.vPoint.x)
		 {
			 pTargetLine = pLine;
		 }
	 }

	 return pTargetLine;
 }

void CLineMgr::Set_LinePoint(float _x, float _y)
{
	for (auto& point : m_vecLinePoint)
	{
		point.x -= _x;
		point.y -= _y;
	}
}

void CLineMgr::Create_Object()
{
	static int obj_id{ 0 };
	static vector<OBJID::ID> obj_list = { OBJID::ROCK, OBJID::COIN, OBJID::MAGNET, OBJID::POWERUP, OBJID::HEART };

	if (GetTickCount() - m_dwLastObjCreate < m_dwObjCreate) return;
	m_dwLastObjCreate = GetTickCount();

	obj_id = rand() % obj_list.size();
	if (rand() % 3)
		obj_id = 0; // 3분의 1의 확률로 ROCK

	CObj* pObj = nullptr;
	switch (obj_list[obj_id])
	{
	case OBJID::ROCK:
		pObj = CAbstractFactory<CRock>::Create(WINCX + 100, 0, BYTE(0));
		CObjMgr::Get_Instance()->Add_Object(OBJID::ROCK, pObj);
		break;
	case OBJID::COIN:
		for (int i = 0; i < 5; ++i) {
			pObj = CAbstractFactory<CCoin>::Create(WINCX + 10.f + i*50.f, 0);
			CObjMgr::Get_Instance()->Add_Object(OBJID::COIN, pObj);
		}
		break;
	case OBJID::MAGNET:
		GET_INSTANCE(CObjMgr)->Add_Object(OBJID::MAGNET, CAbstractFactory<CMagnet>::Create(WINCX + 100, 0));
		break;
	case OBJID::POWERUP:
		GET_INSTANCE(CObjMgr)->Add_Object(OBJID::POWERUP, CAbstractFactory<CPowerUp>::Create(WINCX + 100, 0));
		break;
	case OBJID::HEART:
		GET_INSTANCE(CObjMgr)->Add_Object(OBJID::HEART, CAbstractFactory<CHeart>::Create(WINCX + 100, 0));
		break;
	}

	m_dwObjCreate = 2000 + rand() % 2000;
}

void CLineMgr::Create_BackObject()
{
	static int obj_id{ 0 };
	static vector<OBJID::ID> back_obj_list = { OBJID::TREE, OBJID::BIGTREE, OBJID::END };

	if (GetTickCount() - m_dwLastBackObjIDChange > m_dwBackObjIDChange)
	{
		obj_id = rand() % back_obj_list.size();
		m_dwLastBackObjIDChange = GetTickCount();
	}

	if (GetTickCount() - m_dwLastBackObjCreate < m_dwBackObjCreate) return;
	m_dwLastBackObjCreate = GetTickCount();

	CObj* pObj = nullptr;
	switch (back_obj_list[obj_id])
	{
	case OBJID::TREE:
		pObj = CAbstractFactory<CTree>::Create(WINCX + 100, 0);
		CObjMgr::Get_Instance()->Add_Object(OBJID::TREE, pObj);
		break;
	case OBJID::BIGTREE:
		pObj = CAbstractFactory<CBigTree>::Create(WINCX + 100, 0);
		CObjMgr::Get_Instance()->Add_Object(OBJID::BIGTREE, pObj);
		break;
	case OBJID::END:
		break;
	}
}
