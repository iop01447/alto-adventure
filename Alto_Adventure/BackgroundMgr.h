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
	// Update
	void Update_Color();

private:
	HRESULT InitVB();
	void HSL_To_RGB(float h, float sl, float l, float *r, float *g, float *b);

private:
	vector<CTriangle*> m_vecMountain[3];
	int m_MountainCnt{ 0 };

	LPDIRECT3DVERTEXBUFFER9 m_pVB{ NULL };
	vector<CUSTOMVERTEX> m_vecVertices;

	D3DCOLOR m_vColor[3];
	D3DCOLORVALUE m_vPreColor[3]; // rgba
	D3DCOLORVALUE m_vNextColor[3];

	DWORD m_dwLastColorChange{ 0 };
	DWORD m_dwColorChange{ 5000 };
};

