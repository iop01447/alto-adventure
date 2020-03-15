#include "stdafx.h"
#include "SkyGradient.h"


CSkyGradient::CSkyGradient(initializer_list<GRADIENT> lst)
{
	m_vecColorData.reserve(lst.size());
	copy(lst.begin(), lst.end(), back_inserter(m_vecColorData));

	if (m_vecColorData.front().percent - 0.f > EPSILON) {
		m_vecVertex.emplace_back(0.f, 0.f, 0.f, 1.f, m_vecColorData.front().color);
		m_vecVertex.emplace_back(WINCX, 0.f, 0.f, 1.f, m_vecColorData.front().color);
	}

	for (GRADIENT& gradient : m_vecColorData)
	{
		float fY = gradient.percent * WINCY;
		m_vecVertex.emplace_back(0.f, fY, 0.f, 1.f, gradient.color);
		m_vecVertex.emplace_back(WINCX, fY, 0.f, 1.f, gradient.color);
	}
	D3DCOLORVALUE;
}

CSkyGradient::~CSkyGradient()
{
}

void CSkyGradient::Render()
{
	// 사각형 그리기
	HRESULT hr = GET_INSTANCE(CDevice)->Get_Device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, m_vecVertex.size() - 2, m_vecVertex.data(), sizeof(CUSTOMVERTEX)); // D3DPT_TRIANGLESTRIP
	assert(!FAILED(hr));
}

void CSkyGradient::Render_Alpha(float a)
{
	vector<CUSTOMVERTEX> tmp = m_vecVertex;
	for (auto& vertex : tmp)
	{
		vertex.color &= D3DCOLOR_ARGB(0, 255, 255, 255);
		vertex.color |= D3DCOLOR_ARGB(int(a * 255.f), 0, 0, 0);
	}
	HRESULT hr = GET_INSTANCE(CDevice)->Get_Device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, tmp.size() - 2, tmp.data(), sizeof(CUSTOMVERTEX)); // D3DPT_TRIANGLESTRIP
	assert(!FAILED(hr));
}

void CSkyGradient::Set_Alpha(float a)
{
	for (auto& vertex : m_vecVertex)
	{
		vertex.color &= D3DCOLOR_ARGB(0, 255, 255, 255);
		vertex.color |= D3DCOLOR_ARGB(int(a * 255.f), 0, 0, 0);
	}
}
