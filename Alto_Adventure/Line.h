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
	void Render(HDC _DC);

public:
	const LINEINFO& Get_Info() const { return m_tInfo; }

private:
	LINEINFO		m_tInfo;
};


#endif // !__LINE_H__
