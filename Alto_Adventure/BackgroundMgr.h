#pragma once
class CBackgroundMgr
{
private:
	CBackgroundMgr();
	~CBackgroundMgr();

public:
	void Initialize();
	void Update();
	void Render(HDC _DC);

public:
	static CBackgroundMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CBackgroundMgr;
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = nullptr;
	}

private:
	static CBackgroundMgr* m_pInstance;
};

