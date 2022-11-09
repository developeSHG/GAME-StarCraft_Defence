#include "stdafx.h"
#include "Bomber.h"

#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CBomber::CBomber()
{
}


CBomber::~CBomber()
{
}

void CBomber::Initialize()
{
	// CObj 상속변수 (초기화 변경 필요시 코딩)
	m_tInfo.vPos = { 50.f, 40.f, 0.f };
	m_tInfo.vSize = { 20.f, 20.f, 0.f };
	m_wsImageKey = L"Unit_Bomber";
	m_wstStateKey = L"Work";

	// CUnit, COverload 고유변수 (초기화 변경 필요시 코딩)
	m_eCurState = STATE::END;
	m_eNextState = STATE::WORK;
	m_wsUnitStateKey[STATE::NONE] = L"None";
	m_wsUnitStateKey[STATE::WORK] = L"Work";
	m_wsUnitStateKey[STATE::ATTACK] = L"Attack";
	m_wsUnitStateKey[STATE::DEAD] = L"Dead";
	m_fSpeed = 3.0f;
	m_eDir = DIR::DOWN;

	// UnitInfo
	//strcpy_s(m_tUnitInfo.szName, 16, "Overload");
	//m_tUnitInfo.iAtt = 0;
	//m_tUnitInfo.iAtt_UpGradeNum = 0;
	//m_tUnitInfo.iArm = 1;
	//m_tUnitInfo.iArm_UpGradeNum = 0;
	//m_tUnitInfo.iHp = 200;
	//m_tUnitInfo.iMaxHp = 200;
	//m_tUnitInfo.iAttRange = 0;
	m_tUnitInfo.fHp = 600;
	m_eCurState = STATE::WORK;
}

int CBomber::Update()
{
	if (m_bIsDead == true)
		return OBJ_DEAD;

	if (true == m_bDeadState)
	{
		m_eNextState = STATE::DEAD;
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + CScrollMgr::Get_ScrollX(), m_tInfo.vPos.y + CScrollMgr::Get_ScrollY(), 0.f);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;
		return 0;
	}

	static UINT OldTime = GetTickCount();

	int NowTime;
	int dTime;

	NowTime = GetTickCount();		//시간 받아오기
	dTime = NowTime - OldTime;

	if (dTime > rand() % 700 + 300)
	{
		CCollisionMgr::EnemyCollTile(CObjMgr::GetInstance()->Get_Obj(OBJID::ENEMY), CObjMgr::GetInstance()->Get_Obj(OBJID::COLLUI));
		OldTime = NowTime;
	}

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	int	iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	//반전 
	if (m_eDir == CUnit::LEFT)
		D3DXMatrixScaling(&m_tInfo.matScale, -1.0f, 1.0f, 0.0f);
	if (m_eDir == CUnit::RIGHT)
		D3DXMatrixScaling(&m_tInfo.matScale, 1.0f, 1.0f, 0.0f);
	// 이동행렬
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + iScrollX, m_tInfo.vPos.y + iScrollY, 0.f);
	// 월드행렬 = 스 * 자 * 이 * 공 * 부
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	return OBJ_LIVE;
}

void CBomber::LateUpdate()
{
	StateCurFrameCheck();
	FrameCheck();												// State 체크
	CObj::UpdateRect();											// 충돌Rect 초기화
	CObj::MoveFrame(m_iStateCurFrame[m_eCurState]);

	if (STATE::DEAD == m_eCurState)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			CSoundMgr::GetInstance()->MyPlaySound(L"psibolt.wav", CSoundMgr::UI);
			m_bIsDead = true;
		}
	}
}

void CBomber::Render()
{
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	const TEX_INFO* test = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsUnitStateKey[m_eCurState], m_tFrame.iFrameStart);

	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsUnitStateKey[m_eCurState], m_tFrame.iFrameStart)->pTexture,
		nullptr,																						/* Rect의 포인터, 그릴 영역 */
		&D3DXVECTOR3(test->tImgInfo.Width * 0.5f, test->tImgInfo.Height * 0.5f, 0.0f),					/* 출력 중심점 */
		nullptr,																						/* 출력 위치 */
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	// 충돌Rect 보기 (시작)
	if (GetAsyncKeyState('Q') & 0x8000)
		CObj::ViewRect();
	else
		m_bViewRect = false;
	// 충돌Rect 보기 (끝)
}

void CBomber::Release()
{
	
}

void CBomber::FrameCheck()
{
	if (m_eCurState == m_eNextState && m_iCurLook == m_iNextLook)
		return;

	m_eCurState = m_eNextState;
	m_iCurLook = m_iNextLook;

	switch (m_eCurState)
	{
	case STATE::NONE:
		m_tFrame.iFrameStart = m_iStateCurFrame[STATE::NONE];
		m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::NONE];
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 45;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::WORK:
		m_tFrame.iFrameStart = m_iStateCurFrame[STATE::WORK];
		m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::WORK];
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 60;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::ATTACK:
		m_tFrame.iFrameStart = m_iStateCurFrame[STATE::ATTACK];
		m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::ATTACK] + 5;
		if (8 == m_iCurLook)
			m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::ATTACK] + 3;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 45;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::DEAD:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 8;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 45;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	}
}

void CBomber::StateCurFrameCheck()
{
	switch (m_eDir)
	{
	case CUnit::LEFT:
		m_tInfo.vDir = { -1.0f, 0.0f, 0.0f };
		m_iStateCurFrame[STATE::WORK] = 1;
		m_iNextLook = 0;
		break;
	case CUnit::RIGHT:
		m_tInfo.vDir = { 1.0f, 0.0f, 0.0f };
		m_iStateCurFrame[STATE::WORK] = 1;
		m_iNextLook = 1;
		break;
	case CUnit::UP:
		m_tInfo.vDir = { 0.0f, -1.0f, 0.0f };
		m_iStateCurFrame[STATE::WORK] = 0;
		m_iNextLook = 2;
		break;
	case CUnit::DOWN:
		m_tInfo.vDir = { 0.0f, 1.0f, 0.0f };
		m_iStateCurFrame[STATE::WORK] = 2;
		m_iNextLook = 3;
		break;
	default:
		break;
	}
}
