#include "stdafx.h"
#include "CollRect.h"

#include "ScrollMgr.h"

CCollRect::CCollRect()
{

}

CCollRect::~CCollRect()
{

}

void CCollRect::Initialize()
{
	// CObj 상속변수 (초기화 변경 필요시 코딩)
	m_tInfo.vSize = { 50.f, 50.f, 0.f };
	m_wsImageKey = L"Rect";

	// CCollRect 고유변수 (초기화 변경 필요시 코딩)

}

int CCollRect::Update()
{
	float	iScrollX = CScrollMgr::Get_ScrollX();
	float 	iScrollY = CScrollMgr::Get_ScrollY();

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + iScrollX, m_tInfo.vPos.y + iScrollY, 0.f);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;

	return 0;
}

void CCollRect::LateUpdate()
{
	CObj::UpdateRect();
}

void CCollRect::Render()
{
	// 충돌Rect 보기 (시작)
	if (GetAsyncKeyState('Q') & 0x8000)
		CObj::ViewRect();
	else
		m_bViewRect = false;
	// 충돌Rect 보기 (끝)

	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
}

void CCollRect::Release()
{
}
