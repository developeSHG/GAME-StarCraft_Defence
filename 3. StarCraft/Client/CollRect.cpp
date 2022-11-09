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
	// CObj ��Ӻ��� (�ʱ�ȭ ���� �ʿ�� �ڵ�)
	m_tInfo.vSize = { 50.f, 50.f, 0.f };
	m_wsImageKey = L"Rect";

	// CCollRect �������� (�ʱ�ȭ ���� �ʿ�� �ڵ�)

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
	// �浹Rect ���� (����)
	if (GetAsyncKeyState('Q') & 0x8000)
		CObj::ViewRect();
	else
		m_bViewRect = false;
	// �浹Rect ���� (��)

	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
}

void CCollRect::Release()
{
}
