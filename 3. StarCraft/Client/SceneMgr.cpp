#include "stdafx.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Intro.h"
#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	, m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SCENEID eSceneID)
{
	// State 패턴 
	//FSM을 기반으로 하는 객체의 상태를 표현 
	/*
	유한 상태 기계는 자신이 취할수 있는 유한한 갯수를 가진다.
	그리고 그중 반드시 하나만 취한다.
	현재 상태는 특정 조건이 되면 다른 상태로 변할 수 있다.

	FSM과 상속과 다형성으로 더욱 확장한 디자인 패턴
	*/
	m_eNextScene = eSceneID;
	if (m_eCurScene != m_eNextScene)
	{
		if (m_pScene)
		{
			delete m_pScene;
			m_pScene = nullptr;
		}
		switch (m_eNextScene)
		{
		case SCENEID::SCENE_INTRO:
			m_pScene = new CIntro;
			break;
		case SCENEID::SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case SCENEID::SCENE_MENU:
			m_pScene = new CMyMenu;
			break;
		case SCENEID::SCENE_STAGE:
			m_pScene = new CStage;
			break;
		case SCENEID::SCENE_END:
			break;
		}
		m_pScene->Initialize();
		m_eCurScene = m_eNextScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render()
{
	m_pScene->Render();
}

void CSceneMgr::Release()
{
	if (m_pScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
}
