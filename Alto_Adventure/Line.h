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
	void Initialize(); // ���� ���
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
	float			m_fAngle;	// Line�� ����
	float			m_fSpeedX;	// X ���� ���� �ӵ�
	float			m_fSpeedY;  // Y ���� ���� �ӵ� 
};


#endif // !__LINE_H__
