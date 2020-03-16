#include "stdafx.h"
#include "Stage.h"

#include "Player.h"

#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "SoundMgr.h"
#include "BackgroundMgr.h"


CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	D3DXCreateLine(GET_INSTANCE(CDevice)->Get_Device(), &g_pLine);
	g_pLine->SetWidth(5);

	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());

	//�׽�Ʈ�� ����
	CLineMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlayBGM(L"bgm.mp3");
}

void CStage::Update()
{
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Key_Update();
	GET_INSTANCE(CBackgroundMgr)->Update();
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();
}

void CStage::Render()
{
	GET_INSTANCE(CBackgroundMgr)->Render();
	CObjMgr::Get_Instance()->Render();
	CLineMgr::Get_Instance()->Render();
}

void CStage::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Delete_ID(OBJID::EFFECT);
}