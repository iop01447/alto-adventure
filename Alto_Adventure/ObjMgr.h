#pragma once

#ifndef __OBJMGR_H__
#define __OBJMGR_H__

#include "Obj.h"
class CObjMgr
{
	// 외부에서 객체 생성을 제한하기 위해서
private:
	CObjMgr();
	~CObjMgr();

public:
	void Add_Object(OBJID::ID _eID, CObj* _pObj);
	void Update();
	void Late_Update();
	void Render();
	void Release();

public:
	CObj* Get_Target(CObj* _pObj, OBJID::ID _eID);
	CObj* Get_Obj(OBJID::ID _eID) { return m_listObj[_eID].front() ; }
	float Get_Top() { return  m_listObj[OBJID::PLAYER].front()->Get_Top() ; }
	float Get_Speed() {	return m_listObj[OBJID::PLAYER].front()->Get_Speed();	}
public:
	void Delete_ID(OBJID::ID _eID);

	// 싱글톤 패턴
public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	list<CObj*>			m_listObj[OBJID::END];
	static CObjMgr*		m_pInstance;
	list<CObj*>			m_listRender[GROUPID::END];
};


#endif // !__OBJMGR_H__
