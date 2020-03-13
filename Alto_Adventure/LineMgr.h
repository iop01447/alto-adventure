#pragma once

#ifndef __LINEMGR_H__
#define __LINEMGR_H__

class CLine;
class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void Initialize();
	void Update();
	void Render(HDC _DC);
	void Release();

public:
	bool Collision_Line(float _x, float* _y, int _PlayerBottom, float* _fAngle);

public:
	const D3DXVECTOR2* Get_PointList() const { return m_vPointList; }
	const int& Get_PointCnt() const { return m_iPointCnt; }
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
	D3DXVECTOR2*        m_vPointList;
	int					m_iPointCnt;
	static CLineMgr*	m_pInstance;
};


#endif // !__LINEMGR_H__
