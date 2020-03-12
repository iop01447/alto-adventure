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
	const LINEINFO& Get_Info() const { return m_tInfo; }
	const float& Get_Angle() const { return m_fAngle; }

private:
	LINEINFO		m_tInfo;
	float			m_fAngle; // Line의 각도 
};


#endif // !__LINE_H__
