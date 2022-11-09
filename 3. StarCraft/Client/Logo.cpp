#include "stdafx.h"
#include "Logo.h"

#include "ObjMgr.h"
#include "SceneMgr.h"
#include "Sprite.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CSoundMgr::GetInstance()->PlayBGM(L"LogoSound.mp3");

	// 백그라운드 생성
	CObj* pObj = CAbstractFactory<CSprite>::Create();
	pObj->Set_ImageKey(L"Logo_BackGround");
	CObjMgr::GetInstance()->AddObject(OBJID::LOGOUI, pObj);
}

int CLogo::Update()
{
	CObjMgr::GetInstance()->Update();
	if (CKeyMgr::GetInstance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_MENU);
		CSoundMgr::GetInstance()->MyPlaySound(L"MouseDown.wav", CSoundMgr::UI);
	}

	return 0;
}

void CLogo::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CLogo::Render()
{
	CObjMgr::GetInstance()->Render();
}

void CLogo::Release()
{
	CObjMgr::GetInstance()->DeleteID(OBJID::LOGOUI);
}
