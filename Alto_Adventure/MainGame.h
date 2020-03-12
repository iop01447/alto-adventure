#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();	// �ʱ�ȭ
	void Update();		// �� �����Ӹ��� ����(����)
	void Late_Update();
	void Render();		// �� �����Ӹ��� ����Լ�
	void Release();		// �޸� ���� �Լ�

private:
	HDC				m_DC;	// �׸��� �׸��� ���� ��ȭ��

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];
};


#endif // !__MAINGAME_H__
