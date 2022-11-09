#include "stdafx.h"
#include "Intro.h"

#include "Mouse.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

CIntro::CIntro()
{
}


CIntro::~CIntro()
{
	Release();
}

void CIntro::Initialize()
{
	// 비디오 생성
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Texture/Intro/Intro.wmv");
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	MCIWndPlay(m_hVideo);
}

int CIntro::Update()
{
	CObjMgr::GetInstance()->Update();

	if (CKeyMgr::GetInstance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_LOGO);
		CSoundMgr::GetInstance()->MyPlaySound(L"MouseDown.wav", CSoundMgr::UI);
	}
	return 0;
}

void CIntro::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CIntro::Render()
{
	CObjMgr::GetInstance()->Render();
}

void CIntro::Release()
{
	MCIWndClose(m_hVideo);
}
