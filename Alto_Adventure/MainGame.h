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
};


#endif // !__MAINGAME_H__
