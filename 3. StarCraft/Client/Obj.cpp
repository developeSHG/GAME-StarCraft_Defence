#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_wsImageKey(L"Logo_BackGround")
	, m_wstStateKey(L"Normal")
	,m_bIsDead(OBJ_LIVE)
	, m_bIsInit(FALSE)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matRotate);
	D3DXMatrixIdentity(&m_tInfo.matScale);
	D3DXMatrixIdentity(&m_tInfo.matTrans);
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::~CObj()
{
}

void CObj::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}

void CObj::UpdateRect()
{
	//int iScrollX = CScrollMgr::Get_ScrollX();
	//int iScrollY = CScrollMgr::Get_ScrollY();
	//D3DXVECTOR3 vRect = m_tInfo.vPos;
	//vRect.x += iScrollX;
	//vRect.y += iScrollY;

	m_tInfo.rcRect.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x * 0.5f));
	m_tInfo.rcRect.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y * 0.5f));
	m_tInfo.rcRect.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x * 0.5f));
	m_tInfo.rcRect.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.y * 0.5f));
}

void CObj::MoveFrame()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = 0;
}

void CObj::MoveFrame(int _iFrameStart)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = _iFrameStart;
}

void CObj::ViewRect()
{
	m_bViewRect = true;
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(L"Rect");

	D3DXMatrixScaling(&m_tInfo.matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(L"Rect")->pTexture,
		nullptr,																						/* Rect의 포인터, 그릴 영역 */
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),	/* 출력 중심점 */
		nullptr,																						/* 출력 위치 */
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	D3DXMatrixIdentity(&m_tInfo.matScale);
}
