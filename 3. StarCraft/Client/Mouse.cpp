#include "stdafx.h"
#include "Mouse.h"

#include "ObjMgr.h"
#include "Unit.h"

CMouse::CMouse()
{
}


CMouse::~CMouse()
{

}

void CMouse::Initialize()
{
	// CObj ��Ӻ��� (�ʱ�ȭ ���� �ʿ�� �ڵ�)
	m_wsImageKey = L"Mouse";
	m_wstStateKey = L"Normal";
	m_tInfo.vSize.x = 18.f;
	m_tInfo.vSize.y = 19.f;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	// CMouse �������� (�ʱ�ȭ ���� �ʿ�� �ڵ�)
	m_eCurState = STATE::NORMAL;
	m_eNextState = STATE::NORMAL;
	m_bClickCheck = false;
}

int CMouse::Update()
{
	if (true == m_bIsDead)
		return OBJ_DEAD;

	POINT pt = {};
	ShowCursor(false);// ���콺 Ŀ���� �׸��� ������ �ִ� �Լ�. 
	GetCursorPos(&pt);					// ���콺�� ��ǥ�� ������ �Լ�. �ִ� ��ũ�� ���� ��ǥ�� ���´�. 
	ScreenToClient(g_hWnd, &pt);		//��ũ�� ��ǥ���� Ŭ���̾�Ʈ ��ǥ�� ��ȯ �����ش�. 

	m_tInfo.vPos.x = float(pt.x);
	m_tInfo.vPos.y = float(pt.y);

	// Ű �̺�Ʈ (����)
	KeyInput();
	// Ű �̺�Ʈ (��)

	// Ŭ�� State üũ (����)
	if (STATE::CLICK == m_eCurState)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_wstStateKey = L"Normal";
			m_eNextState = STATE::NORMAL;
			m_bClickCheck = false;
		}
	}
	// Ŭ�� State üũ (��)

	return OBJ_LIVE;
}

void CMouse::LateUpdate()
{					   
	// �÷��̾� ���� Ŭ�� ���� (����)
	list<CObj*> listObj = CObjMgr::GetInstance()->Get_Obj(OBJID::PLAYER);
	bool bCheckOn = false;
	for (auto& pObj : listObj)
	{
		RECT rc = {};
		if (IntersectRect(&rc, &m_tInfo.rcRect, &pObj->Get_Rect()))
		{
			m_wstStateKey = L"UnitOn";
			m_eNextState = STATE::UNITON;
			m_bClickCheck = false;
			bCheckOn = true;

			if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
			{
				list<CObj*> listObj2 = CObjMgr::GetInstance()->Get_Obj(OBJID::PLAYER);
				for (auto& pObj2 : listObj2)
				{
					if (SCAST<CUnit*>(pObj2)->WORK != SCAST<CUnit*>(pObj2)->Get_State())
						SCAST<CUnit*>(pObj2)->Set_Select(false);
					if (SCAST<CUnit*>(pObj2)->WORK == SCAST<CUnit*>(pObj2)->Get_State()
						&& true == SCAST<CUnit*>(pObj2)->Get_Select())
						SCAST<CUnit*>(pObj2)->Set_SelectFinishWork();
				}
				CSoundMgr::GetInstance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				SCAST<CUnit*>(pObj)->Set_Select(true);
				SCAST<CUnit*>(pObj)->Set_SelectFinishWorkFalse();		
			}
		}
	}
	if(false == m_bClickCheck && false == bCheckOn)
	{
		m_wstStateKey = L"Normal";
		m_eNextState = STATE::NORMAL;
	}
	// �÷��̾� ���� Ŭ�� ���� (��)

	FrameCheck();						// State üũ
	CObj::UpdateRect();					// �浹Rect �ʱ�ȭ
	CObj::MoveFrame(); 					// �ش� State�� Frame ����

	//int iScrollX = CScrollMgr::Get_ScrollX();
	//int iScrollY = CScrollMgr::Get_ScrollY();
	//m_tInfo.rcRect.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x * 0.5f) + iScrollX);
	//m_tInfo.rcRect.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y * 0.5f) + iScrollY);
	//m_tInfo.rcRect.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x * 0.5f) + iScrollX);
	//m_tInfo.rcRect.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.y * 0.5f) + iScrollY);
}

void CMouse::Render()
{
	// �浹Rect ���� (����)
	if (GetAsyncKeyState('Q') & 0x8000)
		CObj::ViewRect();
	else
		m_bViewRect = false;
	// �浹Rect ���� (��)

	const TEX_INFO* test = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wstStateKey, m_tFrame.iFrameStart);

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;

	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, m_wstStateKey, m_tFrame.iFrameStart)->pTexture,
		nullptr,																						/* Rect�� ������, �׸� ���� */
		&D3DXVECTOR3(test->tImgInfo.Width * 0.57f, test->tImgInfo.Height * 0.58f, 0.0f),				/* ��� �߽��� */
		nullptr,																						/* ��� ��ġ */
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

}

void CMouse::Release()
{
}

void CMouse::FrameCheck()
{
	if (m_eCurState == m_eNextState)
		return;

	m_eCurState = m_eNextState;

	switch (m_eCurState)
	{
	case STATE::NORMAL:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::UNITON:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 13;			
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STATE::CLICK:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;			
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	}
}

void CMouse::KeyInput()
{
	//if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON) && STATE::UNITON == m_eNextState)
	//{
	//	//CSoundMgr::GetInstance()->MyPlaySound(L"MouseDown.wav", CSoundMgr::UI);
	//	//CSoundMgr::GetInstance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
	//}
	if (CKeyMgr::GetInstance()->KeyUp(VK_RBUTTON))
	{
		m_wstStateKey = L"Click";
		m_eNextState = STATE::CLICK;
		m_bClickCheck = true;
	}
}
