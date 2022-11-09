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
	// CObj ��Ӻ��� (�ʱ�ȭ ���� �ʿ�� �ڵ�)
	m_wstStateKey = L"Normal";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	// CAniSprite �������� (�ʱ�ȭ ���� �ʿ�� �ڵ�)
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

	CObj::UpdateRect();				// �浹Rect �ʱ�ȭ
	CObj::MoveFrame();				// �ش� State�� Frame ����
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
		nullptr,																							/* Rect�� ������, �׸� ���� */
		&D3DXVECTOR3(fCenterX, fCenterY, 0.0f),		/* ��� �߽��� */
		nullptr,																							/* ��� ��ġ */
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	// �浹Rect ���� (����)
	if (GetAsyncKeyState('Q') & 0x8000)
		CObj::ViewRect();
	else
		m_bViewRect = false;
	// �浹Rect ���� (��)
}

void CAniSprite::Release()
{
}
