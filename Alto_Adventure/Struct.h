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

#endif // !__STRUCT_H__
