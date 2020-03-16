#pragma once
class CUIMgr
{
	DECLARE_SINGLETON(CUIMgr);

private:
	CUIMgr();
	~CUIMgr();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

private:
	void Render_Coin();
	void Render_HP();
	void Render_Distance();
	void Render_MagnetItem();
	void Render_PowerUpItem();

private:
	LPD3DXFONT m_pSmallFont{ NULL };
	LPD3DXFONT m_pBigFont{ NULL };

	int m_iCoin;
	int m_iHP{ 3 };
	float m_fDistance{ 0 };
};

