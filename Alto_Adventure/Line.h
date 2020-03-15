#pragma once

#ifndef __LINE_H__
#define __LINE_H__


class CLine
{
public:
	CLine();
	CLine(LINEPOS& _tLeft, LINEPOS& _tRight);
	CLine(LINEINFO& _tLine);
	~CLine();

public:
	void Initialize(); // 각도 계산
	void Update();
	void Render(HDC _DC);

public:
	void Set_SpeedX(float _fSpeed) { m_fSpeedX = _fSpeed; }
	void Set_SpeedY() { m_fSpeedY = -m_fSpeedY; }

public:
	const LINEINFO& Get_Info() const { return m_tInfo; }
	const float& Get_Angle() const { return m_fAngle; }
	const float& Get_SpeedY() const { return m_fSpeedY; }

private:
	LINEINFO		m_tInfo;
	float			m_fAngle;	// Line의 각도
	float			m_fSpeedX;	// X 방향 진행 속도
	float			m_fSpeedY;  // Y 방향 진행 속도 
};


#endif // !__LINE_H__
