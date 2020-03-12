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
	void Initialize();	// 초기화
	void Update();		// 매 프레임마다 갱신(구동)
	void Late_Update();
	void Render();		// 매 프레임마다 출력함수
	void Release();		// 메모리 해제 함수

private:
	HDC				m_DC;	// 그림을 그리기 위한 도화지

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];
};


#endif // !__MAINGAME_H__
