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
	// �̹��� ����
}

void CBackgroundMgr::Update()
{

}

void CBackgroundMgr::Render(HDC _DC)
{

}
