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
	enum SCENEID { SCENE_MENU, SCENE_STAGE, SCENE_END };

public:
	void Update();
	void Late_Update();
	void Render();
	void Release();

public:
	SCENEID Get_Scene() { return m_eCurScene; }

public:
	void Scene_Change(SCENEID _eScene);

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

	SCENEID				m_ePreScene;
	SCENEID				m_eCurScene;

};


#endif // !__SCENEMGR_H__
