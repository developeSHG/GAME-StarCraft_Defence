#include "stdafx.h"
#include "AniSprite.h"


CAniSprite::CAniSprite()
{
}


CAniSprite::~CAniSprite()
{
}

void CAniSprite::Initialize()
{
	// CObj 상속변수 (초기화 변경 필요시 코딩)
	m_wstStateKey = L"Normal";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	// CAniSprite 고유변수 (초기화 변경 필요시 코딩)
	m_bScroolCheck = true;
}

int CAniSprite::Update()
{
	if (true == m_bIsDead)
		return OBJ_DEAD;

	return OBJ_LIVE;
}

void CAniSprite::LateUpdate()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tInfo.rcRect, pt))
	{
		if (L"Single" == m_wsImageKey)
			m_tFrame.iFrameEnd = 59;
		else if (L"Editor" == m_wsImageKey)
			m_tFrame.iFrameEnd = 19;
		else if (L"Exit" == m_wsImageKey)
			m_tFrame.iFrameEnd = 29;
		m_wstStateKey = L"On";
	}
	else
	{
		if (L"Single" == m_wsImageKey)
			m_tFrame.iFrameEnd = 34;
		else if (L"Editor" == m_wsImageKey)
			m_tFrame.iFrameEnd = 84;
		else if (L"Exit" == m_wsImageKey)
			m_tFrame.iFrameEnd = 49;
		m_wstStateKey = L"Normal";
	}

	CObj::UpdateRect();				// 충돌Rect 초기화
	CObj::MoveFrame();				// 해당 State의 Frame 연산
}

void CAniSprite::Render()
{
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wstStateKey, m_tFrame.iFrameStart);

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	float fCenterX = TextureInfo->tImgInfo.Width * 0.5f;
	float fCenterY = TextureInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + iScrollX, m_tInfo.vPos.y + iScrollY, 0.f);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wstStateKey, m_tFrame.iFrameStart)->pTexture,
		nullptr,																							/* Rect의 포인터, 그릴 영역 */
		&D3DXVECTOR3(fCenterX, fCenterY, 0.0f),		/* 출력 중심점 */
		nullptr,																							/* 출력 위치 */
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	// 충돌Rect 보기 (시작)
	if (GetAsyncKeyState('Q') & 0x8000)
		CObj::ViewRect();
	else
		m_bViewRect = false;
	// 충돌Rect 보기 (끝)
}

void CAniSprite::Release()
{
}
