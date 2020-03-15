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
	// 예전에 썼던 hBitmap 역할을 할 com 객체, 그림 한 장을 관리 제어 하기 위해 사용된다. 

	D3DXIMAGE_INFO tImageInfo;
	// 그림의 정보를 가지고 있을 구조체. 
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
	float percent; // 0~1 사이

	GRADIENT(D3DCOLOR _color, float _percent)
		: color(_color), percent(_percent) {}
};

#endif // !__STRUCT_H__
