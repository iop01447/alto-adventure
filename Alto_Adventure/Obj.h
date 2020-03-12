#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	// 상태 판단 용 함수
	// Update보다 늦게 진행되어 이동 후 결과를 판단하기 위해 사용한다.
	virtual void Late_Update() = 0;		
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

protected:
	INFO m_tInfo;

	float m_fAngle;
	float m_fSpeed;
};

#endif // !__OBJ_H__