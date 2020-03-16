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
	LPD3DXFONT m_pFont{ NULL };

	int m_iCoin;
};

