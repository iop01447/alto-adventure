#include "stdafx.h"
#include "ObjMgr.h"

#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID::ID _eID, CObj * _pObj)
{
	_pObj->Set_ObjID(_eID);
	m_listObj[_eID].emplace_back(_pObj);
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto& iter = m_listObj[i].begin();
		for (; iter != m_listObj[i].end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->Late_Update();
			if (m_listObj[i].empty())
				break;

			GROUPID::ID		eID = pObj->Get_GroupID();
			m_listRender[eID].emplace_back(pObj);
		}
	}

	CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::ROCK]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::COIN]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MAGNET]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::HEART]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::POWERUP]);
}

void CObjMgr::Render()
{
	//for (int i = 0; i < OBJID::END; ++i)
	//{
	//	for (auto& pObj : m_listObj[i])
	//	{
	//		pObj->Render();
	//	}
	//}

	for (int i = 0; i < GROUPID::END; ++i)
	{
		for (auto& pObj : m_listRender[i])
		{
			if (m_listRender[i].empty())
				break;
			pObj->Render();
		}
		m_listRender[i].clear();
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

CObj* CObjMgr::Get_Target(CObj* _pObj, OBJID::ID _eID)
{
	if (m_listObj[_eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;
	float	fDis = 0.f;

	for (auto& pNode : m_listObj[_eID])
	{
		//if(pNode->Get_Dead())
		//	continue;

		//float fX = abs(_pObj->Get_Info().fX - pNode->Get_Info().fX);
		//float fY = abs(_pObj->Get_Info().fY - pNode->Get_Info().fY);
		//float fDis2 = sqrtf(fX * fX + fY * fY);

		//if (!pTarget || fDis > fDis2)
		//{
		//	pTarget = pNode;
		//	fDis = fDis2;
		//}
	}
	return pTarget;
}

void CObjMgr::Delete_ID(OBJID::ID _eID)
{
	for (auto& pObj : m_listObj[_eID])
		Safe_Delete(pObj);

	m_listObj[_eID].clear();
}
