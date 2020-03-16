#pragma once
class CDevice
{
public:
	static CDevice* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CDevice; 

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
private:
	CDevice();
	~CDevice();
	CDevice(CDevice& rDevice) {}; 
	void operator=(CDevice& rDevice) {}
public:
	LPDIRECT3DDEVICE9 Get_Device()
	{
		return m_pDevice; 
	}
	LPD3DXSPRITE Get_Sprite()
	{
		return m_pSprite; 
	}
	LPD3DXFONT Get_Font()
	{
		return m_pFont;
	}
public:
	HRESULT InitDevice(); 
	void Release(); 

public:
	void Render_Begin();
	void Render_End(); 

private:
	static CDevice* m_pInstance; 
	LPDIRECT3D9 m_p3D;
	// IDirect3D9 의 포인터 형식이다. 이 객체가 하는 역할은 장치의 지원 수준을 조사하고 장치를 생성하는 역할을 하는 com 객체. 
	LPD3DXSPRITE m_pSprite; 
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXFONT m_pFont;

};

