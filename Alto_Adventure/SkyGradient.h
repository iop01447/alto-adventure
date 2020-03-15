#pragma once
class CSkyGradient
{
public:
	CSkyGradient(initializer_list<GRADIENT> lst);
	~CSkyGradient();

public:
	void Render();
	void Render_Alpha(float a);
	void Set_Alpha(float a);
	D3DCOLOR Get_Color() { return m_vecVertex.front().color; }

private:
	vector<GRADIENT> m_vecColorData;
	vector<CUSTOMVERTEX> m_vecVertex;
};

