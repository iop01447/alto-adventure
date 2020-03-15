#pragma once

#ifndef __LINEMGR_H__
#define __LINEMGR_H__

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

public:
	bool Collision_Line(float _x, float* _y, int _PlayerBottom, float* _fAngle);
	CLine* Collision_Line(float _x);

public:
	const float& Get_SpeedY() const { return m_listLine.front()->Get_SpeedY(); }

public:
	void Set_LinePoint(float _x, float _y);

private:
	void Create_RockObj();
	void Create_Object();

public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	list<CLine*>		m_listLine;
	vector<D3DXVECTOR3> m_vecLinePoint;

	vector<D3DXVECTOR2> m_vecPointList;

	static CLineMgr*	m_pInstance;

	DWORD m_dwLastObjCreate{ 0 };
	DWORD m_dwObjCreate{ 500 };
	DWORD m_dwLastObjIDChange{ 0 };
	DWORD m_dwObjIDChange{ 10000 };

	DWORD m_dwLastRockCreate{ 0 };
	DWORD m_dwRockCreate{ 3000 };
};


#endif // !__LINEMGR_H__
