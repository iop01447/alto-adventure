#include "stdafx.h"
#include "BackgroundMgr.h"
#include "BmpMgr.h"
#include "TextureMgr.h"
#include "Mountain.h"
#include "SkyGradient.h"
#include "ObjMgr.h"
#include "Cloud.h"

IMPLEMENT_SINGLETON(CBackgroundMgr);


CBackgroundMgr::CBackgroundMgr()
{
	Initialize();
}


CBackgroundMgr::~CBackgroundMgr()
{
	Release();
}

void CBackgroundMgr::Initialize()
{
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Image/cloud/%d.png", L"Cloud", L"Idle", 23);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Image/star.png", L"Star");
	for(int i=0; i<5; ++i)
		CObjMgr::Get_Instance()->Add_Object(OBJID::CLOUD, CAbstractFactory<CCloud>::Create());

	int size[] = { 3,4,7 };

	// Mountain
	// 맨 앞에서 맨 뒤 순으로 배치
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < size[i]; ++j) {
			float fSizeX = WINCX / float(size[i] - 1);

			float fScaleX = fSizeX + rand() % 50;
			float fScaleY = fSizeX * 0.3f;
			fScaleX *= 2.3f;
			fScaleY *= 2.3f;

			float fPosX = j * (fSizeX - 50) + 50 + rand() % 100;
			float fPosY = float((WINCY - 200) - (i * 100) - rand() % 10);

			float fSpeed = (3 - i)*1.f;

			m_vecMountain[i].push_back(new CMountain(D3DXVECTOR3(fPosX, fPosY, 0.f),
				D3DXVECTOR3(fScaleX, fScaleY, 1.f), fSpeed));
		}
		random_shuffle(m_vecMountain[i].begin(), m_vecMountain[i].end());
	}

	for (int i = 0; i < 3; ++i) {
		m_MountainCnt += m_vecMountain[i].size();
	}
	m_vecVertices.resize(m_MountainCnt * 3);

	// 2. 정점 버퍼를 생성하고 이에 대한 포인터를 가져온다
	if (FAILED(GET_INSTANCE(CDevice)->Get_Device()->CreateVertexBuffer(m_vecVertices.size() * sizeof(CUSTOMVERTEX), 0, D3DFMT_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		assert(false && "정점 버퍼 생성 실패");
	}

	Init_SkyGradient();

	Update_Color();
	m_vPreColor = m_vNextColor;
}

void CBackgroundMgr::Update()
{
	for (int i = 0; i < 3; ++i) {
		for (auto mountain : m_vecMountain[i]) {
			mountain->Update();
		}
	}

	Update_Color();
	InitVB();
}

void CBackgroundMgr::Render()
{
	GET_INSTANCE(CDevice)->Get_Device()->SetFVF(D3DFMT_CUSTOMVERTEX);

	// 사각형 그리기
	m_vecSkyGradient[m_iPreSkyID]->Render();
	m_vecSkyGradient[m_iNextSkyID]->Render();

	// 별 그리기
	Render_Stars();

	// 산들 그리기
	GET_INSTANCE(CDevice)->Get_Device()->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
	GET_INSTANCE(CDevice)->Get_Device()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_MountainCnt);
}

void CBackgroundMgr::Release()
{
	if (m_pVB)
		m_pVB->Release();

	for (int i = 0; i < 3; ++i) {
		for_each(m_vecMountain[i].begin(), m_vecMountain[i].end(), Safe_Delete<CMountain*>);
		m_vecMountain[i].clear();
		m_vecMountain[i].shrink_to_fit();
	}
}

void CBackgroundMgr::Render_Forward(float a)
{
	GET_INSTANCE(CDevice)->Get_Device()->SetFVF(D3DFMT_CUSTOMVERTEX);
	m_vecSkyGradient[m_iPreSkyID]->Render_Alpha(a);
	m_vecSkyGradient[m_iNextSkyID]->Render_Alpha(a);
}

void CBackgroundMgr::Init_SkyGradient()
{
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff00000c, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff020111, 0.85f), GRADIENT(0xff191621, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff020111, 0.6f), GRADIENT(0xff20202c, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff020111, 0.1f), GRADIENT(0xff3a3a52, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff20202c, 0.f), GRADIENT(0xff515175, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff40405c, 0.f), GRADIENT(0xff6f71aa, 0.8f), GRADIENT(0xff8a76ab, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff4a4969, 0.f), GRADIENT(0xff7072ab, 0.5f), GRADIENT(0xffcd82a0, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff757abf, 0.f), GRADIENT(0xff8583be, 0.6f), GRADIENT(0xffeab0d1, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff82addb, 0.f), GRADIENT(0xffebb2b1, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff94c5f8, 0.1f), GRADIENT(0xffa6e6ff, 0.7f), GRADIENT(0xffb1b5ea, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xffb7eaff, 0.f), GRADIENT(0xff94dfff, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff9be2fe, 0.f), GRADIENT(0xff38a3d1, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff90dffe, 0.f), GRADIENT(0xff38a3d1, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff57c1eb, 0.f), GRADIENT(0xff246fa8, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff2d91c2, 0.f), GRADIENT(0xff1e528e, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff2473ab, 0.f), GRADIENT(0xff1e528e, 0.7f), GRADIENT(0xff5b7983, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff1e528e, 0.f), GRADIENT(0xff265889, 0.5f), GRADIENT(0xff9da671, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff1e528e, 0.f), GRADIENT(0xff728a7c, 0.5f), GRADIENT(0xffe9ce5d, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff154277, 0.f), GRADIENT(0xff576e71, 0.3f), GRADIENT(0xffe1c45e, 0.7f), GRADIENT(0xffb26339, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff163C52, 0.f), GRADIENT(0xff4F4F47, 0.3f), GRADIENT(0xffC5752D, 0.6f), GRADIENT(0xffB7490F, 0.8f), GRADIENT(0xff2F1107, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff071B26, 0.f), GRADIENT(0xff071B26, 0.3f), GRADIENT(0xff8A3B12, 0.8f), GRADIENT(0xff240E03, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff010A10, 0.3f), GRADIENT(0xff59230B, 0.8f), GRADIENT(0xff2F1107, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff090401, 0.5f), GRADIENT(0xff4B1D06, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff00000c, 0.5f), GRADIENT(0xff150800, 1.f) }));
	m_vecSkyGradient.push_back(new CSkyGradient({ GRADIENT(0xff00000c, 1.f) }));
}

void CBackgroundMgr::Update_Color()
{
	float d = (GetTickCount() - m_dwLastColorChange) / (float)m_dwColorChange;
	d = max(0, min(1, d));

	for (int i = 0; i < 3; ++i) {
		float r = m_vPreColor.r * (1 - d) + m_vNextColor.r * d;
		float g = m_vPreColor.g * (1 - d) + m_vNextColor.g * d;
		float b = m_vPreColor.b * (1 - d) + m_vNextColor.b * d;
		m_vColor = D3DCOLOR_ARGB(255, int(r * 255), int(g * 255), int(b * 255));
	}

	m_vecSkyGradient[m_iNextSkyID]->Set_Alpha(d);

	if (d == 1) {
		m_dwLastColorChange = GetTickCount();

		m_iPreSkyID = m_iNextSkyID;
		m_iNextSkyID = (m_iNextSkyID + 1) % m_vecSkyGradient.size();

		m_vecSkyGradient[m_iPreSkyID]->Set_Alpha(1);
		m_vecSkyGradient[m_iNextSkyID]->Set_Alpha(0);

		m_vPreColor = m_vNextColor;

		m_vNextColor.r = float((m_vecSkyGradient[m_iNextSkyID]->Get_Color() & D3DCOLOR_ARGB(0, 255, 0, 0)) >> 16);
		m_vNextColor.r /= 255.f;
		m_vNextColor.g = float((m_vecSkyGradient[m_iNextSkyID]->Get_Color() & D3DCOLOR_ARGB(0, 0, 255, 0)) >> 8);
		m_vNextColor.g /= 255.f;
		m_vNextColor.b = float(m_vecSkyGradient[m_iNextSkyID]->Get_Color() & D3DCOLOR_ARGB(0, 0, 0, 255));
		m_vNextColor.b /= 255.f;
	}
}

void CBackgroundMgr::Render_Stars()
{
	float fAlpha{ 0 };
	
	// MaxAlpha 값 구하기
	float d = (GetTickCount() - m_dwLastColorChange) / (float)m_dwColorChange;
	d = max(0, min(1, d));
	d /= 6.f;

	if (m_iPreSkyID < 6)
	{
		d += m_iPreSkyID / 6.f;
	}
	else if (m_iPreSkyID >= int(m_vecSkyGradient.size() - 6))
	{
		d = (m_vecSkyGradient.size() - m_iPreSkyID) / 6.f - d;
	}
	else
		return;

	fAlpha = 1 * (1 - d) + 0 * d;

	// 그리기
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Star");
	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
			D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.f);
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0));
			D3DXMatrixTranslation(&matTrans, j * pTexInfo->tImageInfo.Width * 0.5f,
				i * pTexInfo->tImageInfo.Height * 0.5f, 0.f);

			matWorld = matScale * matRotZ * matTrans;
			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
				nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				nullptr,
				D3DCOLOR_ARGB(int(fAlpha*255.f), 255, 255, 255));
		}
	}
}

HRESULT CBackgroundMgr::InitVB()
{
	int i = 0;

	for (int k = 2; k >=0; --k) {
		for (auto pTriangle : m_vecMountain[k]) {
			D3DXMATRIX matScale, matTrans, matWorld;
			D3DXMatrixScaling(&matScale, pTriangle->m_tInfo.vSize.x, pTriangle->m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, pTriangle->m_tInfo.vPos.x, pTriangle->m_tInfo.vPos.y, 0.f);

			matWorld = matScale * matTrans;

			// 1. 정점에 대한 정보를 정의한다

			for (int j = 0; j < 3; ++j) {
				D3DXVec3TransformCoord(&pTriangle->m_vPoint[j], &pTriangle->m_vOrigin[j], &matWorld);
			}

			m_vecVertices[i] = { pTriangle->m_vPoint[0].x, pTriangle->m_vPoint[0].y, pTriangle->m_vPoint[0].z, 1.f, m_vColor }; // 위쪽
			m_vecVertices[i + 1] = { pTriangle->m_vPoint[1].x, pTriangle->m_vPoint[1].y, pTriangle->m_vPoint[1].z, 1.f, m_vColor & D3DCOLOR_ARGB(0,255,255,255) }; // 오른쪽 
			m_vecVertices[i + 2] = { pTriangle->m_vPoint[2].x, pTriangle->m_vPoint[2].y, pTriangle->m_vPoint[2].z, 1.f, m_vColor & D3DCOLOR_ARGB(0,255,255,255) }; // 왼쪽

			i += 3;
		}
	}

	// 3. 정점 버퍼에 대한 포인터를 가지고 현재 정의된 정점의 데이터를 버퍼에 써넣는다.
	VOID* pVertices{ NULL };
	if (FAILED(m_pVB->Lock(0, m_vecVertices.size() * sizeof(CUSTOMVERTEX), (void**)&pVertices, 0)))
	{
		assert(false && "정점 버퍼 락 실패");
		return E_FAIL;
	}

	memcpy(pVertices, m_vecVertices.data(), m_vecVertices.size() * sizeof(CUSTOMVERTEX));

	m_pVB->Unlock();

	return S_OK;
}

// http://blog.naver.com/PostView.nhn?blogId=swryu02&logNo=220680527175

/* =====================================
H는 [0,360) 범위, S,V값은 각각 [0,1]범위를 갖는다.
R,G,B는 각각 [0,1]값을 갖는다.
===================================== */
void CBackgroundMgr::HSL_To_RGB(float h, float sl, float l, float *r, float *g, float *b)
{
	float v;

	v = (l <= 0.5f) ? (l * (1.0f + sl)) : (l + sl - l * sl);
	if (v <= 0) {
		*r = *g = *b = 0.0;
	}
	else
	{
		float m;
		float sv;
		int sextant;
		float fract, vsf, mid1, mid2;

		m = l + l - v;
		sv = (v - m) / v;
		h /= 60.0f;
		sextant = (int)h;
		fract = h - sextant;
		vsf = v * sv * fract;
		mid1 = m + vsf;
		mid2 = v - vsf;

		switch (sextant) {
		case 0: *r = v;    *g = mid1; *b = m; break;
		case 1: *r = mid2; *g = v;    *b = m; break;
		case 2: *r = m;    *g = v;    *b = mid1; break;
		case 3: *r = m;    *g = mid2; *b = v; break;
		case 4: *r = mid1; *g = m;    *b = v; break;
		case 5: *r = v;    *g = m;    *b = mid2; break;
		}
	}
}