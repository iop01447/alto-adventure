#pragma once

#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__

class Scene;
class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	enum SCENEID { SCENE_LOGO, SCENE_MENU, SCENE_STAGE, SCENE_EDIT, SCENE_END };

public:
	void Update(DWORD time);
	void Late_Update();
	void Render(HDC _DC);
	void Release();

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
	Scene*				m_pScene;

	SCENEID				m_ePreScene;
	SCENEID				m_eCurScene;
};


#endif // !__SCENEMGR_H__
