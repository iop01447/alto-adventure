#pragma once

class CTriangle;
class CBackgroundMgr
{
	DECLARE_SINGLETON(CBackgroundMgr)
private:
	CBackgroundMgr();
	~CBackgroundMgr();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

private:
	HRESULT InitVB();

private:
	vector<CTriangle*> m_vecMountain[3];
	int m_MountainCnt{ 0 };

	LPDIRECT3DVERTEXBUFFER9 m_pVB{ NULL };
	vector<CUSTOMVERTEX> m_vecVertices;
};

