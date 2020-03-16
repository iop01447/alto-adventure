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

public:
	void Set_SceneID(SCENE::ID _id) { m_eSceneID = _id; }

private:
	void Render_Coin();
	void Render_HP();
	void Render_Distance();
	void Render_UnDeadMode();
	void Render_MagnetItem();
	void Render_PowerUpItem();

	void Render_EndScene();

private:
	LPD3DXFONT m_pSmallFont{ NULL };
	LPD3DXFONT m_pBigFont{ NULL };

	int m_iCoin;
	int m_iHP{ 3 };
	float m_fDistance{ 0 };
	SCENE::ID m_eSceneID{ SCENE::SCENE_STAGE };
	bool m_bUnDeadMode{ false };
	BYTE m_byMagnetAlphaValue;
	BYTE m_byPowerUpAlphaValue;
};

