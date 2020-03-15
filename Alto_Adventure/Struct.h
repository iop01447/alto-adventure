#pragma once

#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vSize;
	D3DXVECTOR3 vLook;
	D3DXMATRIX matWorld;

}INFO;

typedef struct tagLinePos
{
	tagLinePos() { ZeroMemory(this, sizeof(D3DXVECTOR3)); }
	tagLinePos(float _x, float _y) 
	{
		vPoint = { _x, _y, 0.f };
	}

	D3DXVECTOR3 vPoint;

	//float	fX;
	//float	fY;
}LINEPOS;

typedef struct tagLineInfo
{
	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& _tLeft, LINEPOS& _tRight)
		: tLeftPos(_tLeft), tRightPos(_tRight) {}

	LINEPOS			tLeftPos;
	LINEPOS			tRightPos;

	D3DXVECTOR3		vLook;

}LINEINFO;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture;
	// ������ ��� hBitmap ������ �� com ��ü, �׸� �� ���� ���� ���� �ϱ� ���� ���ȴ�. 

	D3DXIMAGE_INFO tImageInfo;
	// �׸��� ������ ������ ���� ����ü. 
}TEXINFO;

struct CUSTOMVERTEX
{
	float x, y, z, rhw;
	D3DCOLOR color;

	CUSTOMVERTEX(){}
	CUSTOMVERTEX(float _x, float _y, float _z, float _w, D3DCOLOR _color)
		:x(_x), y(_y), z(_z), rhw(_w), color(_color) {}
};

struct GRADIENT
{
	D3DCOLOR color;
	float percent; // 0~1 ����

	GRADIENT(D3DCOLOR _color, float _percent)
		: color(_color), percent(_percent) {}
};

#endif // !__STRUCT_H__
