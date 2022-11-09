#include "stdafx.h"
#include "MainGame.h"

#include "ObjMgr.h"
#include "SceneMgr.h"
#include "Mouse.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	HRESULT hr = 0;
	hr = CDeviceMgr::GetInstance()->InitDevice(g_hWnd, WINCX, WINCY, CDeviceMgr::MODE_WIN);
	FAILED_CHECK_MSG(hr, L"InitDevice Failed");
	CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENEID::SCENE_INTRO);

	CSoundMgr::GetInstance()->Initialize();

	// 텍스쳐 삽입
	TextureInsert_LOGO();
	TextureInsert_MENU();
	TextureInsert_STAGE();

	// 마우스 생성
	CObj* pObj = CAbstractFactory<CMouse>::Create();
	CObjMgr::GetInstance()->AddObject(OBJID::MOUSE, pObj);
}

void CMainGame::Update()
{
	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
	CKeyMgr::GetInstance()->KeyUpdate();
}

void CMainGame::Render()
{
	if (CSceneMgr::SCENE_INTRO != CSceneMgr::GetInstance()->Get_SceneID())
	{
		CDeviceMgr::GetInstance()->Render_Begin();
		CSceneMgr::GetInstance()->Render();
		CDeviceMgr::GetInstance()->Render_End();
	}
	else
		CSceneMgr::GetInstance()->Render();
	//Render_Fps(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CKeyMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();
	CDeviceMgr::GetInstance()->DestroyInstance();
}

void CMainGame::Render_Fps(HDC _hDC)
{
	static UINT oldTime = GetTickCount();
	static float FrameCount;
	static float Fps = 0;

	int nowTime, delTime;
	TCHAR szFps[12];
	memset(szFps, 0, sizeof(szFps));

	nowTime = GetTickCount();
	delTime = nowTime - oldTime;
	++FrameCount;

	if (delTime > 999)
	{
		FrameCount = (FrameCount * 1000) / delTime;
		oldTime = nowTime;
		Fps = FrameCount;
		FrameCount = 0;
	}

	TCHAR info[32] = L"";
	swprintf_s(info, L"%f", Fps);
	TextOut(_hDC, 0, 0, info, lstrlen(info));
}

void CMainGame::TextureInsert_LOGO()
{
	// 백그라운드
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Logo/BackGround.png", L"Logo_BackGround");
	
	// 마우스
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Mouse/Normal/Normal.png", L"Mouse", L"Normal", 5);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Mouse/Click/Click.png", L"Mouse", L"Click", 5);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Mouse/UnitOn/UnitOn.png", L"Mouse", L"UnitOn", 14);

	// 충돌Rect
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Rect.png", L"Rect");
}

void CMainGame::TextureInsert_MENU()
{
	// 백그라운드
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/BackGround.png", L"Menu_BackGround");

	// 싱글 플레이 이미지
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/MainMenu/SinglePlay/single.png", L"Single", L"Normal", 35);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/MainMenu/SinglePlay/MouseOn/Single_On.png", L"Single", L"On", 60);
	// 싱글 플레이 버튼 이미지
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/MainMenu/SinglePlay/Button/single_player.png", L"Button_Single", L"Normal", 2);

	// 맵 에디터 이미지
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/MainMenu/Editor/editor.png", L"Editor", L"Normal", 85);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/MainMenu/Editor/MouseOn/Editor_On.png", L"Editor", L"On", 20);
	// 맵 에디터 버튼 이미지
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/MainMenu/Editor/Button/editor_button.png", L"Button_Editor", L"Normal", 2);

	// 종료 이미지 (블랙홀)
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/MainMenu/Exit/exit.png", L"Exit", L"Normal", 50);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/MainMenu/Exit/MouseOn/Exit_On.png", L"Exit", L"On", 30);
	// 종료 버튼 이미지
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Menu/MainMenu/Exit/Button/exit_button.png", L"Button_Exit", L"Normal", 2);
}

void CMainGame::TextureInsert_STAGE()
{
	// 백그라운드
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Ui/BackGround.png", L"Stage_BackGround");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Ui/MainUi.png", L"Stage_MainUi");

	// 타일
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Ui/Tile.png", L"Stage_Tile");

	// 유닛 Select
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_0.png", L"Select_0");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_1.png", L"Select_1");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_2.png", L"Select_2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_3.png", L"Select_3");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_4.png", L"Select_4");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_5.png", L"Select_5");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_6.png", L"Select_6");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_7.png", L"Select_7");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_8.png", L"Select_8");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Select/Select_9.png", L"Select_9");

	// 마린
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Marine/None/Marine_None.png", L"Marine", L"None", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Marine/Work/Marine_Work.png", L"Marine", L"Work", 153);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Marine/Attack/Marine_Attack.png", L"Marine", L"Attack", 51);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Marine/Bullet/Bullet.png", L"Marine", L"Bullet", 8);

	// 오버로드
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Overload/Work/Overload_Work.png", L"Unit_Overload", L"Work", 16);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Overload/Dead/Blood.png", L"Unit_Overload", L"Dead", 15);

	// 아비터
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Arbiter/Work/Arbiter_Work.png", L"Unit_Arbiter", L"Work", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Arbiter/Explosion_M/ExploM.png", L"Unit_Arbiter", L"Dead", 10);

	// 레이스
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Wraith/Work/Wraith_Work.png", L"Unit_Wraith", L"Work", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Wraith/Bang/Bang.png", L"Unit_Wraith", L"Dead", 9);

	// 발키리
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Bomber/Work/Bomber_Work.png", L"Unit_Bomber", L"Work", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Bomber/Bang/Bang.png", L"Unit_Bomber", L"Dead", 9);

	// 캐리어
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Carrier/Work/Carrier_Work.png", L"Unit_Carrier", L"Work", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Carrier/Explosion_L/ExploL.png", L"Unit_Carrier", L"Dead", 14);

	// 배틀크루져
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/BattleCr/Work/Battlecr_Work.png", L"Unit_BattleCr", L"Work", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/BattleCr/Bang/Bang.png", L"Unit_BattleCr", L"Dead", 9);

	// 엔지니어링 베이
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Unit/Structure/weaponpl.png", L"Structure_Weaponpl", L"NONE", 1);

	//업그레이드 무기
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/CmdIcon/UpgradeUI/Weapon_0.png", L"Upgrade_Weapon");
	
	// 업그레이드 방어구
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/CmdIcon/UpgradeUI/Armor_0.png", L"Upgrade_Armor");

}
