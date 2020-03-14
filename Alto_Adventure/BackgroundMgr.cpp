#include "stdafx.h"
#include "BackgroundMgr.h"
#include "BmpMgr.h"
#include "TextureMgr.h"
#include "Triangle.h"

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

	int size[] = { 3,4,7 };

	// �� �տ��� �� �� ������ ��ġ
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < size[i]; ++j) {
			float fSizeX = WINCX / float(size[i] - 1);

			float fScaleX = fSizeX + rand() % 50;
			float fScaleY = fSizeX*0.3f;
			fScaleX *= 2.3f;
			fScaleY *= 2.3f;

			float fPosX = j * (fSizeX - 50) + 50 + rand() % 100;
			float fPosY = float((WINCY - 200) - (i * 100) - rand() % 10);

			float fSpeed = (3 - i)*1.f;

			m_vecMountain[i].push_back(new CTriangle(D3DXVECTOR3(fPosX, fPosY, 0.f),
				D3DXVECTOR3(fScaleX, fScaleY, 1.f), fSpeed));
		}
		random_shuffle(m_vecMountain[i].begin(), m_vecMountain[i].end());
	}

	for (int i = 0; i < 3; ++i) {
		m_MountainCnt += m_vecMountain[i].size();
	}
	m_vecVertices.resize(m_MountainCnt * 3);

	// 2. ���� ���۸� �����ϰ� �̿� ���� �����͸� �����´�
	if (FAILED(GET_INSTANCE(CDevice)->Get_Device()->CreateVertexBuffer(m_vecVertices.size() * sizeof(CUSTOMVERTEX), 0, D3DFMT_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		assert(false && "���� ���� ���� ����");
	}

	Update_Color();
	for (int i = 0; i < 3; ++i)
		m_vPreColor[i] = m_vNextColor[i];
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
	GET_INSTANCE(CDevice)->Get_Sprite()->End();
	GET_INSTANCE(CDevice)->Get_Device()->SetFVF(D3DFMT_CUSTOMVERTEX);

	// �簢�� �׸���
	CUSTOMVERTEX vert[4] = {
		{ 0.f, 0.f, 0.f, 1.f, m_vColor[1] },
		{ WINCX, 0.f, 0.f, 1.f, m_vColor[1] },
		{ 0.f, WINCY, 0.f, 1.f, m_vColor[2] },
		{ WINCX, WINCY, 0.f, 1.f, m_vColor[2] }
	};
	HRESULT hr = GET_INSTANCE(CDevice)->Get_Device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vert, sizeof(CUSTOMVERTEX)); // D3DPT_TRIANGLESTRIP
	assert(!FAILED(hr));
	GET_INSTANCE(CDevice)->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

	// ��� �׸���
	GET_INSTANCE(CDevice)->Get_Device()->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
	GET_INSTANCE(CDevice)->Get_Device()->SetFVF(D3DFMT_CUSTOMVERTEX);
	GET_INSTANCE(CDevice)->Get_Device()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_MountainCnt);
}

void CBackgroundMgr::Release()
{
	if (m_pVB)
		m_pVB->Release();

	for (int i = 0; i < 3; ++i) {
		for_each(m_vecMountain[i].begin(), m_vecMountain[i].end(), Safe_Delete<CTriangle*>);
		m_vecMountain[i].clear();
		m_vecMountain[i].shrink_to_fit();
	}
}

void CBackgroundMgr::Update_Color()
{
	float d = (GetTickCount() - m_dwLastColorChange) / (float)m_dwColorChange;
	d = max(0, min(1, d));

	for (int i = 0; i < 3; ++i) {
		float r = m_vPreColor[i].r * (1 - d) + m_vNextColor[i].r * d;
		float g = m_vPreColor[i].g * (1 - d) + m_vNextColor[i].g * d;
		float b = m_vPreColor[i].b * (1 - d) + m_vNextColor[i].b * d;
		m_vColor[i] = D3DCOLOR_ARGB(255, int(r * 255), int(g * 255), int(b * 255));
	}

	if (d == 1) {

		m_dwLastColorChange = GetTickCount();

		float r{ 0 }, g{ 0 }, b{ 0 };
		float h = float(rand() % 360);
		float s = 0.4f + (rand() % 30) / 100.f;

		for (int i = 0; i < 3; ++i)
			m_vPreColor[i] = m_vNextColor[i];

		// �� ����
		HSL_To_RGB(h, s + 0.2f, 0.4f, &m_vNextColor[0].r, &m_vNextColor[0].g, &m_vNextColor[0].b);
		// �� ��
		HSL_To_RGB(h, s, 0.2f + 0.2f, &m_vNextColor[1].r, &m_vNextColor[1].g, &m_vNextColor[1].b);
		// �� �ٴ� & �� �ٴ�
		HSL_To_RGB(h, s, 0.2f + 0.6f, &m_vNextColor[2].r, &m_vNextColor[2].g, &m_vNextColor[2].b);
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

			// 1. ������ ���� ������ �����Ѵ�

			for (int j = 0; j < 3; ++j) {
				D3DXVec3TransformCoord(&pTriangle->m_vPoint[j], &pTriangle->m_vOrigin[j], &matWorld);
			}

			m_vecVertices[i] = { pTriangle->m_vPoint[0].x, pTriangle->m_vPoint[0].y, pTriangle->m_vPoint[0].z, 1.f, m_vColor[0] }; // ����
			m_vecVertices[i + 1] = { pTriangle->m_vPoint[1].x, pTriangle->m_vPoint[1].y, pTriangle->m_vPoint[1].z, 1.f, m_vColor[2] & D3DCOLOR_ARGB(0,255,255,255) }; // ������ 
			m_vecVertices[i + 2] = { pTriangle->m_vPoint[2].x, pTriangle->m_vPoint[2].y, pTriangle->m_vPoint[2].z, 1.f, m_vColor[2] & D3DCOLOR_ARGB(0,255,255,255) }; // ����
			i += 3;
		}
	}

	// 3. ���� ���ۿ� ���� �����͸� ������ ���� ���ǵ� ������ �����͸� ���ۿ� ��ִ´�.
	VOID* pVertices{ NULL };
	if (FAILED(m_pVB->Lock(0, m_vecVertices.size() * sizeof(CUSTOMVERTEX), (void**)&pVertices, 0)))
	{
		assert(false && "���� ���� �� ����");
		return E_FAIL;
	}

	memcpy(pVertices, m_vecVertices.data(), m_vecVertices.size() * sizeof(CUSTOMVERTEX));

	m_pVB->Unlock();

	return S_OK;
}

// http://blog.naver.com/PostView.nhn?blogId=swryu02&logNo=220680527175

/* =====================================
H�� [0,360) ����, S,V���� ���� [0,1]������ ���´�.
R,G,B�� ���� [0,1]���� ���´�.
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