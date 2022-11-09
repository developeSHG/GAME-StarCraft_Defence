#include "stdafx.h"
#include "Marine.h"


CMarine::CMarine()
{
}


CMarine::~CMarine()
{
}

void CMarine::Initialize()
{
	// CObj 상속변수 (초기화 변경 필요시 코딩)
	m_tInfo.vPos = { 200.f, 200.f, 0.f };
	m_tInfo.vSize = { 20.f, 20.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_wsImageKey = L"Marine";
	m_wstStateKey = L"None";

	// CUnit, CMarine 고유변수 (초기화 변경 필요시 코딩)
	m_eCurState = STATE::NONE;
	m_wsUnitStateKey[STATE::NONE] = L"None";
	m_wsUnitStateKey[STATE::WORK] = L"Work";
	m_wsUnitStateKey[STATE::ATTACK] = L"Attack";
	m_fSpeed = 3.0f;
}

int CMarine::Update()
{
	if (true == m_bIsDead)
		return OBJ_DEAD;
	
	// 마우스 포인트 이동 (시작)
	CUnit::MovePoint(m_tInfo);
	// 마우스 포인트 이동 (끝)	

	// 범위연산 공격 (시작)
	CUnit::AttackRange();
	// 범위연산 공격 (끝)

	return OBJ_LIVE;
}

void CMarine::LateUpdate()
{
	StateCurFrameCheck();										// 해당 State의 Frame 체크
	FrameCheck();												// State 체크
	CObj::UpdateRect();											// 충돌Rect 초기화
	CObj::MoveFrame(m_iStateCurFrame[m_eCurState]);				// 해당 State의 Frame 연산
}

void CMarine::Render()
{
	// 충돌Rect 보기 (시작)
	if (GetAsyncKeyState('Q') & 0x8000)
		CObj::ViewRect();
	else
		m_bViewRect = false;
	// 충돌Rect 보기 (끝)

	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsUnitStateKey[m_eCurState], m_tFrame.iFrameStart);

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	float fCenterX = TextureInfo->tImgInfo.Width * 0.5f;
	float fCenterY = TextureInfo->tImgInfo.Height * 0.5f;

	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.vPos.x -= 7;
	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.vPos.x += 7;
	if (GetAsyncKeyState(VK_UP))
		m_tInfo.vPos.y += 7;
	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.vPos.y -= 7;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	if (true == m_bSelect && false == m_bSelectFinishWork)
	{
		TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Select_0");
		CDeviceMgr::GetInstance()->GetSprite()->Draw(
			TextureInfo->pTexture,
			nullptr,											/* Rect의 포인터, 그릴 영역 */
			&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.2f, 0.0f),				/* 출력 중심점 */
			nullptr,											/* 출력 위치 */
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}

	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsUnitStateKey[m_eCurState], m_tFrame.iFrameStart)->pTexture,
		nullptr,																							/* Rect의 포인터, 그릴 영역 */
		&D3DXVECTOR3(fCenterX, fCenterY, 0.0f),																/* 출력 중심점 */
		nullptr,																							/* 출력 위치 */
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	if (STATE::ATTACK == m_eCurState)
	{
		CDeviceMgr::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wsUnitStateKey[m_eCurState], m_tFrame.iFrameStart)->pTexture,
			nullptr,																							/* Rect의 포인터, 그릴 영역 */
			&D3DXVECTOR3(fCenterX, fCenterY, 0.0f),																/* 출력 중심점 */
			nullptr,																							/* 출력 위치 */
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
}

void CMarine::Release()
{
}

void CMarine::StateCurFrameCheck()
{
	switch (m_eDir)
	{
	case DIR::LEFT:
		D3DXMatrixScaling(&m_tInfo.matScale, -1.f, 1.f, 0.f);
		break;
	case DIR::RIGHT:
		D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 0.f);
		break;
	}

	if (1.f >= m_fCos && 0.78f <= m_fCos)
	{
		m_iStateCurFrame[STATE::NONE] = 0;
		m_iStateCurFrame[STATE::WORK] = 0;
		m_iStateCurFrame[STATE::ATTACK] = 0;
		m_iNextLook = 0;
	}
	else if (0.78f > m_fCos && 0.56f <= m_fCos)
	{
		m_iStateCurFrame[STATE::NONE] = 1;
		m_iStateCurFrame[STATE::WORK] = 18;
		m_iStateCurFrame[STATE::ATTACK] = 6;
		m_iNextLook = 1;
	}
	else if (0.56f > m_fCos && 0.34f <= m_fCos)
	{
		m_iStateCurFrame[STATE::NONE] = 2;
		m_iStateCurFrame[STATE::WORK] = 36;
		m_iStateCurFrame[STATE::ATTACK] = 12;
		m_iNextLook = 2;
	}
	else if (0.34f > m_fCos && 0.12f <= m_fCos)
	{
		m_iStateCurFrame[STATE::NONE] = 3;
		m_iStateCurFrame[STATE::WORK] = 54;
		m_iStateCurFrame[STATE::ATTACK] = 18;
		m_iNextLook = 3;
	}
	else if (0.12f > m_fCos && -0.1f <= m_fCos)
	{
		m_iStateCurFrame[STATE::NONE] = 4;
		m_iStateCurFrame[STATE::WORK] = 72;
		m_iStateCurFrame[STATE::ATTACK] = 24;
		m_iNextLook = 4;
	}
	else if (-0.1f > m_fCos && -0.32f <= m_fCos)
	{
		m_iStateCurFrame[STATE::NONE] = 5;
		m_iStateCurFrame[STATE::WORK] = 90;
		m_iStateCurFrame[STATE::ATTACK] = 30;
		m_iNextLook = 5;
	}
	else if (-0.32f > m_fCos && -0.54f <= m_fCos)
	{
		m_iStateCurFrame[STATE::NONE] = 6;
		m_iStateCurFrame[STATE::WORK] = 108;
		m_iStateCurFrame[STATE::ATTACK] = 36;
		m_iNextLook = 6;
	}
	else if (-0.54f > m_fCos && -0.76f <= m_fCos)
	{
		m_iStateCurFrame[STATE::NONE] = 7;
		m_iStateCurFrame[STATE::WORK] = 126;
		m_iStateCurFrame[STATE::ATTACK] = 42;
		m_iNextLook = 7;
	}
	else if (-0.76f > m_fCos && -1.f <= m_fCos)
	{
		m_iStateCurFrame[STATE::NONE] = 8;
		m_iStateCurFrame[STATE::WORK] = 144;
		m_iStateCurFrame[STATE::ATTACK] = 48;
		m_iNextLook = 8;
	}
}

void CMarine::FrameCheck()
{
	if (m_eCurState == m_eNextState && m_iCurLook == m_iNextLook)
		return;

	m_eCurState = m_eNextState;
	m_iCurLook = m_iNextLook;

	switch (m_eCurState)
	{
	case STATE::NONE:
		m_tFrame.iFrameStart = m_iStateCurFrame[STATE::NONE];
		m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::NONE];					// 8
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 45;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::WORK:
		m_tFrame.iFrameStart = m_iStateCurFrame[STATE::WORK];
		m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::WORK] + 17;			// 152
		if(8 == m_iCurLook)
			m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::WORK] + 8;			
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 45;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::ATTACK:
		m_tFrame.iFrameStart = m_iStateCurFrame[STATE::ATTACK];
		m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::ATTACK] + 5;			// 50
		if (8 == m_iCurLook)
			m_tFrame.iFrameEnd = m_iStateCurFrame[STATE::ATTACK] + 2;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 45;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	}
}
