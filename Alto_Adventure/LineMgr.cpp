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

//////////////test�� ����///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	D3DXVECTOR3 vLine0 = { -(WINCX >> 1), 250.f, 0.f };
	m_vecLinePoint.emplace_back(vLine0);

	// �������� WINCX >> 1 ��ŭ ������ ����Ʈ ���� �� m_vecLinePoint �� ����(���� ������)
	for (int i = 1; i < 6; ++i)
	{
		D3DXVECTOR3 vLinePoint = { float(m_vecLinePoint[i - 1].x + (WINCX >> 1)), float(m_vecLinePoint[i - 1].y + (rand() % 100) + 100) , 0.f };
		m_vecLinePoint.emplace_back(vLinePoint);
	}

	// m_vecLinePoint�� ����Ʈ���� ����� ����� �������� ���� �� �ְ� list<CLine*> m_listLine �� ���� (�� ���� ������ � ������)
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

			���� 4���� �Է� �Ǵ� ���� �ֽ��ϴ�.
			pV1, pV2, pV3, pV4 ���⼭ ���߰�� s�� ���� 0 ~ 1.0f ������ ���� �ְ� �˴ϴ�.
			s���� 0�� �������� pV2�� ����� ���� ������ �Ǹ�,
			s���� 1�� �������� pV3�� ����� ���� ������ �˴ϴ�.

			�ٽ� ���ؼ�  pV1, pV4�� ���� pV2 ���� pV3�� ���� ��� �׸��µ� ������ �ְ� �˴ϴ�.
			������ ������ �������� ��� ������ pV2 ~ pV3 ��°� ���� ���ø� �˴ϴ�
			*/
			D3DXVECTOR3 vPoint1, vPoint2;
			D3DXVec3CatmullRom(&vPoint1, &m_vecLinePoint[i], &m_vecLinePoint[i + 1], &m_vecLinePoint[i + 2], &m_vecLinePoint[i + 3], (float(j) / (WINCX>>1)));
			D3DXVec3CatmullRom(&vPoint2, &m_vecLinePoint[i], &m_vecLinePoint[i + 1], &m_vecLinePoint[i + 2], &m_vecLinePoint[i + 3], (float(j+3) / (WINCX >> 1)));

			m_listLine.emplace_back(new CLine(LINEPOS(vPoint1.x, vPoint1.y), LINEPOS(vPoint2.x, vPoint2.y)));
		}
	}

	//g_pLine�� Draw�Լ��� �������� D3DXVECTOR2 �迭�� ����Ʈ���� �ű�� �۾�
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
	// �÷��̾ ��ġ�� �κ��� ������ ���� + �÷��̾��� ���¿� ���� �ӵ��� ����
	for (auto& pLine : m_listLine)
		pLine->Update();
	
	GET_INSTANCE(CLineMgr)->Set_LinePoint(m_listLine.front()->Get_SpeedX() + GET_INSTANCE(CObjMgr)->Get_Speed(), m_listLine.front()->Get_SpeedY());

	// ������Ʈ�� ����Ʈ���� ��ġ ����
	m_vecPointList.clear();
	for (auto& pLine : m_listLine)
	{
		D3DXVECTOR2 vPoint = { pLine->Get_Info().tLeftPos.vPoint.x, pLine->Get_Info().tLeftPos.vPoint.y };
		m_vecPointList.emplace_back(vPoint);
	}
}

void CLineMgr::Late_Update()
{
	// ���� �Ѿ ����Ʈ���� �����ϰ� ���ο� ���� �������� ������ �߰�

	// ������ �ξ��� ������ ����° ����Ʈ�� 0���� �۾�����
	if ( 0 > m_vecLinePoint[2].x )
	{
		// ù��° ����Ʈ ����
		m_vecLinePoint.erase(m_vecLinePoint.begin());

		// ���ο� ���� ����Ʈ�� ���� ����Ʈ���� ���� ������ �߰�
		D3DXVECTOR3 vLinePoint = { float(m_vecLinePoint[m_vecLinePoint.size() - 1].x + (WINCX >> 1)), float(m_vecLinePoint[m_vecLinePoint.size() - 1].y + (rand() % 100) + 100) , 0.f };
		m_vecLinePoint.emplace_back(vLinePoint);

		// ������ �ִ� ���� ����Ʈ��� ���� ���� ���� ����Ʈ ������ � ����Ʈ���� ����
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

	// X�� ���� ��ĥ
	D3DXVECTOR2* pPoint = nullptr;
	pPoint = new D3DXVECTOR2[m_vecPointList.size()];

	for (size_t i = 0; i < m_vecPointList.size(); ++i)
		pPoint[i] = m_vecPointList[i];
	g_pLine->Draw(pPoint, m_vecPointList.size(), D3DCOLOR_ARGB(255, 255, 255, 255)); 

	// Y�� ���� ��ĥ
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
		obj_id = 0; // 3���� 1�� Ȯ���� ROCK

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
