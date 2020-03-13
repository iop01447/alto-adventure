#include "stdafx.h"
#include "BackgroundMgr.h"
#include "BmpMgr.h"
#include "TextureMgr.h"

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
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Image/cloud/%d.png", L"Cloud", L"Idle", 23);
}

void CBackgroundMgr::Update()
{

}

void CBackgroundMgr::Render()
{

}
