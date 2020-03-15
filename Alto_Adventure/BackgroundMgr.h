#pragma once

class CMountain;
class CSkyGradient;
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

public:
	void Render_Forward(float a);

private:
	// Initialize
	void Init_SkyGradient();

	// Update
	void Update_Color();

	// Render
	void Render_Stars();

private:
	HRESULT InitVB();
	void HSL_To_RGB(float h, float sl, float l, float *r, float *g, float *b);

private:
	vector<CMountain*> m_vecMountain[3];
	int m_MountainCnt{ 0 };

	LPDIRECT3DVERTEXBUFFER9 m_pVB{ NULL };
	vector<CUSTOMVERTEX> m_vecVertices;

	D3DCOLOR m_vColor;
	D3DCOLORVALUE m_vPreColor;
	D3DCOLORVALUE m_vNextColor;

	vector<CSkyGradient*> m_vecSkyGradient;
	int m_iPreSkyID{ 0 };
	int m_iNextSkyID{ 0 };

	DWORD m_dwLastColorChange{ 0 };
	DWORD m_dwColorChange{ 1000 };

	DWORD m_dwLastStarSparkle{ 0 };
	DWORD m_dwStarSparkle{ 1000 };
};

