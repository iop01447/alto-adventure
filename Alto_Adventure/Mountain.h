#pragma once
class CMountain
{
public:
	CMountain();
	CMountain(const D3DXVECTOR3& _vPos, const D3DXVECTOR3& _vSize, float _fSpeed);
	~CMountain();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

public:
	D3DXVECTOR3 m_vPoint[3]{};
	D3DXVECTOR3 m_vOrigin[3]{};

	INFO m_tInfo{};

	float m_fSpeed;
};

