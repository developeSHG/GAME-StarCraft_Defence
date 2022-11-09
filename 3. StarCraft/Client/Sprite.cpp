#include "stdafx.h"
#include "Sprite.h"

CSprite::CSprite()
{
}


CSprite::~CSprite()
{
}

void CSprite::Initialize()
{
	// CObj 상속변수 (초기화 변경 필요시 코딩)

	// CSprite 고유변수 (초기화 변경 필요시 코딩)
	m_bCenterView = false;
	m_bScroolCheck = true;
}

int CSprite::Update()
{
	if (true == m_bIsDead)
		return OBJ_DEAD;

	return OBJ_LIVE;
}

void CSprite::LateUpdate()
{
	CObj::UpdateRect();				// 충돌Rect 초기화
}									

void CSprite::Render()
{
	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey);

	float fCenterX = 0.f;
	float fCenterY = 0.f;
	int iScrollX = 0;
	int iScrollY = 0;

	if (true == m_bCenterView)
	{
		fCenterX = TextureInfo->tImgInfo.Width * 0.5f;
		fCenterY = TextureInfo->tImgInfo.Height * 0.5f;
	}

	if (true == m_bScroolCheck)
	{
		iScrollX = CScrollMgr::Get_ScrollX();
		iScrollY = CScrollMgr::Get_ScrollY();
	}

	D3DXMatrixTranslation(&m_tInfo.matTrans, 0.f + iScrollX, 0.f + iScrollY, 0.f);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		TextureInfo->pTexture,
		nullptr,											/* Rect의 포인터, 그릴 영역 */
		&D3DXVECTOR3(fCenterX, fCenterY, 0.0f),				/* 출력 중심점 */
		nullptr,											/* 출력 위치 */
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CSprite::Release()
{
}
