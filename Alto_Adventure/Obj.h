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
	virtual void Render() = 0;
	virtual void Release() = 0;

public:
	const INFO& Get_Info() const { return m_tInfo; }
	const float& Get_Angle() const { return m_fAngle; }
	const float& Get_Speed() const { return m_fSpeed; }
	const float& Get_Top() const 
	{ 
		if (m_vPoint[0].y > m_vPoint[1].y) 
			return m_vPoint[1].y;
		return m_vPoint[0].y;
	}

public:
	void Set_Pos(float _x, float _y);

protected:
	bool			m_bDead;
	INFO			m_tInfo;

	D3DXVECTOR3		m_vPoint[4]; // Q
	D3DXVECTOR3		m_vOrigin[4]; // P

	float m_fAngle;
	float m_fSpeed;
};

#endif // !__OBJ_H__