#include "stdafx.h"
#include "Weaponpl.h"

#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CWeaponpl::CWeaponpl()
{
}


CWeaponpl::~CWeaponpl()
{
}

void CWeaponpl::Initialize()
{

	// CObj 상속변수 (초기화 변경 필요시 코딩)
	m_tInfo.vPos = { 1200.f, 100.f, 0.f };
	m_tInfo.vSize = { 100.f, 100.f, 0.f };
	m_wsImageKey = L"Structure_Weaponpl";
	m_wstStateKey = L"NONE";

	// CUnit, COverload 고유변수 (초기화 변경 필요시 코딩)
	m_eCurState = STATE::END;
	m_eNextState = STATE::WORK;
	m_wsUnitStateKey[STATE::NONE] = L"None";
	m_wsUnitStateKey[STATE::WORK] = L"Work";
	m_wsUnitStateKey[STATE::ATTACK] = L"Attack";
	m_fSpeed = 2.0f;
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
}

int CWeaponpl::Update()
{
	if (m_bIsDead == true)
		return OBJ_DEAD;

	int	iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	// 이동행렬
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + iScrollX, m_tInfo.vPos.y + iScrollY, 0.f);
	// 월드행렬 = 스 * 자 * 이 * 공 * 부
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	return OBJ_LIVE;
}

void CWeaponpl::LateUpdate()
{
	//StateCurFrameCheck();
	FrameCheck();												// State 체크
	CObj::UpdateRect();											// 충돌Rect 초기화
	CObj::MoveFrame(m_iStateCurFrame[m_eCurState]);
}

void CWeaponpl::Render()
{
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	const TEX_INFO* test = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wstStateKey, m_tFrame.iFrameStart);

	if (true == m_bSelect)
	{
		//test = CTextureMgr::GetInstance()->FindTexture(L"Select_8");
		//CDeviceMgr::GetInstance()->GetSprite()->Draw(
		//	test->pTexture,
		//	nullptr,											/* Rect의 포인터, 그릴 영역 */
		//	&D3DXVECTOR3(test->tImgInfo.Width * 0.5f, test->tImgInfo.Height * 0.5f, 0.0f),				/* 출력 중심점 */
		//	nullptr,											/* 출력 위치 */
		//	D3DCOLOR_ARGB(255, 255, 255, 255)
		//);


	}

	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wstStateKey, m_tFrame.iFrameStart)->pTexture,
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

void CWeaponpl::Release()
{
}

void CWeaponpl::FrameCheck()
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
		m_tFrame.dwFrameSpeed = 60;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::WORK:
		m_tFrame.iFrameStart = m_iStateCurFrame[STATE::WORK];
		m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::WORK];
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 60;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	}
}

void CWeaponpl::StateCurFrameCheck()
{

}
