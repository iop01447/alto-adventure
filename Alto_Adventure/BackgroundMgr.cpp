#include "stdafx.h"
#include "BackgroundMgr.h"
#include "BmpMgr.h"

CBackgroundMgr* CBackgroundMgr::m_pInstance = nullptr;


CBackgroundMgr::CBackgroundMgr()
{
	Initialize();
}


CBackgroundMgr::~CBackgroundMgr()
{
}

void CBackgroundMgr::Initialize()
{
	// 이미지 삽입
}

void CBackgroundMgr::Update()
{

}

void CBackgroundMgr::Render(HDC _DC)
{

}
