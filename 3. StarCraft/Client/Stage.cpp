#include "stdafx.h"
#include "Stage.h"

#include "Sprite.h"
#include "ObjMgr.h"
#include "CollRect.h"
#include "Marine.h"
#include "Overload.h"
#include "Arbiter.h"
#include "Wraith.h"
#include "Bomber.h"
#include "Carrier.h"
#include "BattleCr.h"
#include "Weaponpl.h"

CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CSoundMgr::GetInstance()->PlayBGM(L"StageSound.mp3");
	CSoundMgr::GetInstance()->MyPlaySound(L"StageInit.wav", CSoundMgr::UI);

	// 타일 생성
	CObj* pObj = CAbstractFactory<CSprite>::Create();
	pObj->Set_ImageKey(L"Stage_Tile");
	CObjMgr::GetInstance()->AddObject(OBJID::TILE, pObj);

	// 메인UI창 생성
	pObj = CAbstractFactory<CSprite>::Create();
	pObj->Set_ImageKey(L"Stage_MainUi");
	SCAST<CSprite*>(pObj)->Set_ScroolFalse();
	CObjMgr::GetInstance()->AddObject(OBJID::STAGEUI, pObj);

	// 마린 생성
	pObj = CAbstractFactory<CMarine>::Create(250.f, 200.f);
	CObjMgr::GetInstance()->AddObject(OBJID::PLAYER, pObj);
	pObj = CAbstractFactory<CMarine>::Create(300.f, 200.f);
	CObjMgr::GetInstance()->AddObject(OBJID::PLAYER, pObj);
	pObj = CAbstractFactory<CMarine>::Create(350.f, 200.f);
	CObjMgr::GetInstance()->AddObject(OBJID::PLAYER, pObj);
	pObj = CAbstractFactory<CMarine>::Create(400.f, 200.f);
	CObjMgr::GetInstance()->AddObject(OBJID::PLAYER, pObj);
	pObj = CAbstractFactory<CMarine>::Create(450.f, 200.f);
	CObjMgr::GetInstance()->AddObject(OBJID::PLAYER, pObj);

	// 엔지니어링 베이 생성
	pObj = CAbstractFactory<CWeaponpl>::Create();
	pObj->Set_FrameEnd(0);
	CObjMgr::GetInstance()->AddObject(OBJID::STRUCTURE, pObj);

	//충돌 영역(11시) 생성
	pObj = CAbstractFactory<CCollRect>::Create(35, 30);
	SCAST<CCollRect*>(pObj)->Set_Dir(SCAST<CCollRect*>(pObj)->DOWN);
	CObjMgr::GetInstance()->AddObject(OBJID::COLLUI, pObj);

	//충돌 영역(7시) 생성
	pObj = CAbstractFactory<CCollRect>::Create(35, 750);
	SCAST<CCollRect*>(pObj)->Set_Dir(SCAST<CCollRect*>(pObj)->RIGHT);
	CObjMgr::GetInstance()->AddObject(OBJID::COLLUI, pObj);

	//충돌 영역(5시) 생성
	pObj = CAbstractFactory<CCollRect>::Create(960, 750);
	SCAST<CCollRect*>(pObj)->Set_Dir(SCAST<CCollRect*>(pObj)->UP);
	CObjMgr::GetInstance()->AddObject(OBJID::COLLUI, pObj);

	//충돌 영역(1시) 생성
	pObj = CAbstractFactory<CCollRect>::Create(960, 30);
	SCAST<CCollRect*>(pObj)->Set_Dir(SCAST<CCollRect*>(pObj)->LEFT);
	CObjMgr::GetInstance()->AddObject(OBJID::COLLUI, pObj);

	EnemyCount = 0;

	// 폰트 초기화
	D3DXCreateFont(
		CDeviceMgr::GetInstance()->GetDevice(),
		20,
		0,
		FW_NORMAL,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Arial",
		&Font
	);
	m_bIsStart = false;
}

int CStage::Update()
{
	if (CKeyMgr::GetInstance()->KeyDown('W'))
	{
		CObj* pObj = CAbstractFactory<CMarine>::Create(500.f+CScrollMgr::Get_ScrollX(), 400.f + CScrollMgr::Get_ScrollY());
		CObjMgr::GetInstance()->AddObject(OBJID::PLAYER, pObj);
		CSoundMgr::GetInstance()->MyPlaySound(L"CrateMarine.wav", CSoundMgr::UI);
	}

	if (CKeyMgr::GetInstance()->KeyDown('E'))
	{
		m_bIsStart = true;
	}

	if (m_bIsStart)
	{
		// 몬스터 생성
		Create_Enemy();
	}

	CObjMgr::GetInstance()->Update();
	// 키보드 스크롤 조작
	KeyInput();

	// 마우스 스크롤 조작
	//MouseInput();

	return 0;
}

void CStage::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CStage::Render()
{
	//const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Stage_BackGround");

	//int iScrollX = CScrollMgr::Get_ScrollX();
	//int iScrollY = CScrollMgr::Get_ScrollY();

	//D3DXMATRIX matWorld;
	//D3DXMatrixTranslation(&matWorld, 0.f + iScrollX, 0.f + iScrollY, 0.f);
	//CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&matWorld);
	//CDeviceMgr::GetInstance()->GetSprite()->Draw(
	//	TextureInfo->pTexture,
	//	nullptr,											/* Rect의 포인터, 그릴 영역 */
	//	&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.35f, TextureInfo->tImgInfo.Height * 0.35f, 0.0f),				/* 출력 중심점 */
	//	nullptr,											/* 출력 위치 */
	//	D3DCOLOR_ARGB(255, 255, 255, 255)
	//);

	CObjMgr::GetInstance()->Render();

	RECT rt;
	char str[64];
	SetRect(&rt, 360, 10, 0, 0);	//위치
	sprintf_s(str, "현재 적 수: %d ", CObjMgr::GetInstance()->Get_Obj(OBJID::ENEMY).size());
	Font->DrawTextA(NULL, str, -1, &rt, DT_NOCLIP, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

}

void CStage::Release()
{
	CObjMgr::GetInstance()->DeleteID(OBJID::STAGEUI);
	CSoundMgr::GetInstance()->StopAll();
}

void CStage::KeyInput()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		CScrollMgr::Set_ScrollX(int(-7));
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		CScrollMgr::Set_ScrollX(int(+7));
	}
	if (GetAsyncKeyState(VK_UP))
	{
		CScrollMgr::Set_ScrollY(int(+7));
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		CScrollMgr::Set_ScrollY(int(-7));
	}
}

void CStage::MouseInput()
{
	//마우스 좌표 -> 수정할 것

	if (CObjMgr::GetInstance()->Get_Obj(OBJID::MOUSE).front()->Get_Info().vPos.x <= 30)
	{
		CScrollMgr::Set_ScrollX(int(+7));
	}
	if (CObjMgr::GetInstance()->Get_Obj(OBJID::MOUSE).front()->Get_Info().vPos.x >= 770)
	{
		CScrollMgr::Set_ScrollX(int(-7));
	}
	if (CObjMgr::GetInstance()->Get_Obj(OBJID::MOUSE).front()->Get_Info().vPos.y <= 30)
	{
		CScrollMgr::Set_ScrollY(int(+7));
	}
	if (CObjMgr::GetInstance()->Get_Obj(OBJID::MOUSE).front()->Get_Info().vPos.y >= 570)
	{
		CScrollMgr::Set_ScrollY(int(-7));
	}
}

void CStage::Create_Enemy()
{
	static UINT OldTime = GetTickCount();
	NowTime = GetTickCount();
	dTime = NowTime - OldTime;

	if (dTime >999)
	{
		if (EnemyCount <= 19)
		{
			//오버로드 생성
			CObj* pObj = CAbstractFactory<COverload>::Create();
			pObj->Set_FrameEnd(0);
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY, pObj);
			OldTime = NowTime;
			++EnemyCount;
		}
		else if (EnemyCount <= 39 && 19 < EnemyCount)
		{
			//아비터 생성
			CObj* pObj = CAbstractFactory<CArbiter>::Create();
			pObj->Set_FrameEnd(0);
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY, pObj);
			OldTime = NowTime;
			++EnemyCount;
		}
		else if (EnemyCount <= 59 && 39 < EnemyCount)
		{
			//레이스
			CObj* pObj = CAbstractFactory<CWraith>::Create();
			pObj->Set_FrameEnd(0);
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY, pObj);
			OldTime = NowTime;
			++EnemyCount;
		}
		else if (EnemyCount <= 79 && 59 < EnemyCount)
		{
			//발키리
			CObj* pObj = CAbstractFactory<CBomber>::Create();
			pObj->Set_FrameEnd(0);
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY, pObj);
			OldTime = NowTime;
			++EnemyCount;
		}
		else if (EnemyCount <= 99 && 79 < EnemyCount)
		{
			//캐리어
			CObj* pObj = CAbstractFactory<CCarrier>::Create();
			pObj->Set_FrameEnd(0);
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY, pObj);
			OldTime = NowTime;
			++EnemyCount;
		}
		else if (EnemyCount <= 119 && 99 < EnemyCount)
		{
			//배틀크루져
			CObj* pObj = CAbstractFactory<CBattleCr>::Create();
			pObj->Set_FrameEnd(0);
			CObjMgr::GetInstance()->AddObject(OBJID::ENEMY, pObj);
			OldTime = NowTime;
			++EnemyCount;
		}
	}
}
