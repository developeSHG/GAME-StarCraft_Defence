#include "stdafx.h"
#include "MyMenu.h"

#include "ObjMgr.h"
#include "SceneMgr.h"
#include "Sprite.h"
#include "AniSprite.h"
#include "MyButton.h"

CMyMenu::CMyMenu()
{
}

CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	// 归弊扼款靛 积己
	CObj* pObj = CAbstractFactory<CSprite>::Create();
	pObj->Set_ImageKey(L"Menu_BackGround");
	CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);

	//UI_SINGLE_PLAY 积己
	pObj = CAbstractFactory<CAniSprite>::Create();
	pObj->Set_ImageKey(L"Single");
	pObj->Set_StateKey(L"Normal");
	pObj->Set_FrameEnd(34);
	pObj->Set_Pos(150, 110);
	pObj->Set_Size(220, 200);
	CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);

	//UI_SINGLE_PLAY 滚瓢 积己
	pObj = CAbstractFactory<CMyButton>::Create();
	pObj->Set_ImageKey(L"Button_Single");
	pObj->Set_FrameEnd(0);
	pObj->Set_Pos(150, 200);
	pObj->Set_Size(220, 20);
	CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);

	//UI_SINGLE_PLAY Trigger 积己
	//pObj = CAbstractFactory<CAniSprite>::Create();
	//pObj->Set_ImageKey(L"Single");
	//pObj->Set_StateKey(L"On");
	//pObj->Set_FrameEnd(59);
	//pObj->Set_Pos(150, 100);
	//CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);

	//UI_MAP_EDITOR 积己
	pObj = CAbstractFactory<CAniSprite>::Create();
	pObj->Set_ImageKey(L"Editor");
	pObj->Set_StateKey(L"Normal");
	pObj->Set_FrameEnd(84);
	pObj->Set_Pos(600, 150);
	pObj->Set_Size(180, 220);
	CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);

	//UI_MAP_EDITOR 滚瓢 积己
	pObj = CAbstractFactory<CMyButton>::Create();
	pObj->Set_ImageKey(L"Button_Editor");
	pObj->Set_FrameEnd(0);
	pObj->Set_Pos(600, 250);
	pObj->Set_Size(175, 20);
	CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);

	//UI_MAP_EDITOR Trigger 积己
	//pObj = CAbstractFactory<CAniSprite>::Create();
	//pObj->Set_ImageKey(L"Editor");
	//pObj->Set_StateKey(L"On");
	//pObj->Set_FrameEnd(19);
	//pObj->Set_Pos(600, 150);
	//CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);

	//UI_EXIT 积己
	pObj = CAbstractFactory<CAniSprite>::Create();
	pObj->Set_ImageKey(L"Exit");
	pObj->Set_StateKey(L"Normal");
	pObj->Set_FrameEnd(49);
	pObj->Set_Pos(620, 450);
	pObj->Set_Size(100, 220);
	CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);

	//UI_EXIT 滚瓢 积己
	pObj = CAbstractFactory<CMyButton>::Create();
	pObj->Set_ImageKey(L"Button_Exit");
	pObj->Set_FrameEnd(0);
	pObj->Set_Pos(620, 550);
	pObj->Set_Size(50, 20);
	CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);

	//UI_EXIT Trigger 积己
	//pObj = CAbstractFactory<CAniSprite>::Create();
	//pObj->Set_ImageKey(L"Exit");
	//pObj->Set_StateKey(L"On");
	//pObj->Set_FrameEnd(29);
	//pObj->Set_Pos(620, 450);
	//pObj->Set_Size(100, 220);
	//CObjMgr::GetInstance()->AddObject(OBJID::MENUUI, pObj);
}

int CMyMenu::Update()
{
	CObjMgr::GetInstance()->Update();
	if (CKeyMgr::GetInstance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE);
		CSoundMgr::GetInstance()->MyPlaySound(L"MouseDown.wav", CSoundMgr::UI);
	}

	return 0;
}

void CMyMenu::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CMyMenu::Render()
{
	CObjMgr::GetInstance()->Render();
}

void CMyMenu::Release()
{
	CObjMgr::GetInstance()->DeleteID(OBJID::MENUUI);
	CSoundMgr::GetInstance()->StopAll();
}
