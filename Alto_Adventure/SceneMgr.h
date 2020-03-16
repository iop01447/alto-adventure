#pragma once

#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__

class CScene;
class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void Update();
	void Late_Update();
	void Render();
	void Release();

public:
	SCENE::ID Get_Scene() { return m_eCurScene; }

public:
	void Scene_Change(SCENE::ID _eScene);

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CSceneMgr*	m_pInstance;
	CScene*				m_pScene;

	SCENE::ID				m_ePreScene;
	SCENE::ID				m_eCurScene;

};


#endif // !__SCENEMGR_H__
