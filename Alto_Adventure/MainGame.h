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
};


#endif // !__MAINGAME_H__
