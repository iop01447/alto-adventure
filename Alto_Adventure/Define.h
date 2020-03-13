#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 1280
#define WINCY 720

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define PI 3.141592f

#define NOCOPY(ClassName)						\
private:										\
	ClassName(ClassName& rObj) {};				\
	void operator=(ClassName& rObj) {}

#define DECLARE_SINGLETON(ClassName)			\
public:											\
static ClassName* Get_Instance()				\
{												\
	if (nullptr == m_pInstance)					\
		m_pInstance = new ClassName;			\
	return m_pInstance;							\
}												\
static void Destroy_Instance()					\
{												\
	if (m_pInstance)							\
	{											\
		delete m_pInstance;						\
		m_pInstance = nullptr;					\
	}											\
}												\
NOCOPY(ClassName)								\
private:										\
	static ClassName* m_pInstance;				


#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;

#define GET_INSTANCE(ClassName)					\
ClassName::Get_Instance()

#define D3DFMT_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#define ARGB(a,r,g,b) ((DWORD)(b) | ((DWORD)(g) << 8) | ((DWORD)(r) << 16)| ((DWORD)(a) << 24))

#endif // !__DEFINE_H__
