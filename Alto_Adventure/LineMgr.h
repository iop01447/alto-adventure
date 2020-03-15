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

public:
	const float& Get_SpeedY() const { return m_listLine.front()->Get_SpeedY(); }

public:
	void Set_LinePoint(float _x, float _y);

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

};


#endif // !__LINEMGR_H__
