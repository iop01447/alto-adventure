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

			m_vecMountain[i].push_back(new CTriangle(D3DXVECTOR3(fPosX, fPosY, 0.f),
				D3DXVECTOR3(fScaleX, fScaleY, 1.f), fSpeed));
		}
		random_shuffle(m_vecMountain[i].begin(), m_vecMountain[i].end());
	}

	for (int i = 0; i < 3; ++i) {
		m_MountainCnt += m_vecMountain[i].size();
	}
	m_vecVertices.resize(m_MountainCnt * 3);

	/*m_vecMountain.push_back(new CTriangle(D3DXVECTOR3(400.f, 300.f, 0.f),
		D3DXVECTOR3(200.f, 200.f, 1.f)));*/

		// 2. 정점 버퍼를 생성하고 이에 대한 포인터를 가져온다
	if (FAILED(GET_INSTANCE(CDevice)->Get_Device()->CreateVertexBuffer(m_vecVertices.size() * sizeof(CUSTOMVERTEX), 0, D3DFMT_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		assert(false && "정점 버퍼 생성 실패");
	}

	// InitVB();

}

void CBackgroundMgr::Update()
{
	for (int i = 0; i < 3; ++i) {
		//for_each(m_vecMountain[i].begin(), m_vecMountain[i].end(), [](CTriangle* pMountain) {pMountain->Update(); });
		for (auto mountain : m_vecMountain[i]) {
			mountain->Update();
		}
	}

	InitVB();
}

void CBackgroundMgr::Render()
{
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

HRESULT CBackgroundMgr::InitVB()
{
	int i = 0;

	for (int k = 2; k >=0; --k) {
		for (auto pTriangle : m_vecMountain[k]) {
			D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
			D3DXMatrixScaling(&matScale, pTriangle->m_tInfo.vSize.x, pTriangle->m_tInfo.vSize.y, 0.f);
			//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0));
			D3DXMatrixTranslation(&matTrans, pTriangle->m_tInfo.vPos.x, pTriangle->m_tInfo.vPos.y, 0.f);

			matWorld = matScale * matTrans;

			// 1. 정점에 대한 정보를 정의한다

			DWORD color = (DWORD)255 | ((DWORD)255 << 8) | ((DWORD)255 << 16)
				| ((DWORD)125 << 24);

			for (int j = 0; j < 3; ++j) {
				D3DXVec3TransformCoord(&pTriangle->m_vPoint[j], &pTriangle->m_vOrigin[j], &matWorld);
			}

			m_vecVertices[i] = { pTriangle->m_vPoint[0].x, pTriangle->m_vPoint[0].y, pTriangle->m_vPoint[0].z, 1.f,ARGB(255, 255, 0, 0) };// 0xAfff0000 },
			m_vecVertices[i + 1] = { pTriangle->m_vPoint[1].x, pTriangle->m_vPoint[1].y, pTriangle->m_vPoint[1].z, 1.f,ARGB(255, 0, 255, 0) };// 0xAf00ff00 },
			m_vecVertices[i + 2] = { pTriangle->m_vPoint[2].x, pTriangle->m_vPoint[2].y, pTriangle->m_vPoint[2].z, 1.f,ARGB(255, 0, 0, 255) };// 0xAf00ffff }
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