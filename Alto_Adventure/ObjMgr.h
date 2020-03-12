#pragma once

#ifndef __OBJMGR_H__
#define __OBJMGR_H__

#include "Obj.h"
class CObjMgr
{
	// �ܺο��� ��ü ������ �����ϱ� ���ؼ�
private:
	CObjMgr();
	~CObjMgr();

public:
	void Add_Object(OBJID::ID _eID, CObj* _pObj);
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	CObj* Get_Target(CObj* _pObj, OBJID::ID _eID);
	CObj* Get_Obj(OBJID::ID _eID) { return m_listObj[_eID].front() ; }
	float Get_Top() { return  m_listObj[OBJID::PLAYER].front()->Get_Top() ; }
public:
	void Delete_ID(OBJID::ID _eID);

	// �̱��� ����
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