#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			//if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			//{
			//	Dst->Set_Dead();
			//	Src->Set_Dead();
			//}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				if (fX > fY)	// 상하
				{
					//if (Dst->Get_Info().fY < Src->Get_Info().fY)
					//	Src->Set_PosY(fY);
					//else
					//	Src->Set_PosY(-fY);
				}
				else			// 좌우
				{
					//if (Dst->Get_Info().fX < Src->Get_Info().fX)
					//	Src->Set_PosX(fX);
					//else
					//	Src->Set_PosX(-fX);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				//Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	// abs() : 절대값을 구해준다!
	// sqrtf() : 
	//float	fX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	//float	fY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);
	//float	fDistance = sqrtf(fX * fX + fY * fY);

	//float	fRadius = (float)((_Dst->Get_Info().iCX + _Src->Get_Info().iCX) >> 1);
	////float	fRadius = (_Dst->Get_Info().iCX + _Src->Get_Info().iCX) * 0.5f;
	////float	fRadius = (_Dst->Get_Info().iCX + _Src->Get_Info().iCX) / 2.f;

	//return fRadius > fDistance;
	return false;
}

bool CCollisionMgr::Check_Rect(CObj* _Dst, CObj* _Src, float* _fX, float* _fY)
{
	/*float	fX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float	fY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float	fCX = (float)((_Dst->Get_Info().iCX + _Src->Get_Info().iCX) >> 1);
	float	fCY = (float)((_Dst->Get_Info().iCY + _Src->Get_Info().iCY) >> 1);

	if (fCX > fX && fCY > fY)
	{
		*_fX = fCX - fX;
		*_fY = fCY - fY;

		return true;
	}*/

	return false;
}
