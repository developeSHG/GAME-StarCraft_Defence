#include "stdafx.h"
#include "Unit.h"

#include "ObjMgr.h"

CUnit::CUnit()
{
	m_eCurState = STATE::END;
	m_eNextState = STATE::NONE;
	m_iCurLook = 1;
	m_iNextLook = 0;
	ZeroMemory(&m_vPoint, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_iStateCurFrame, sizeof(m_iStateCurFrame));
	m_bSelect = false;
	ZeroMemory(&m_tUnitInfo, sizeof(UNIT_INFO));
	m_bTileCheckX = false;
	m_bTileCheckY = false;
	m_bSelectFinishWork = false;
	m_bDeadState = false;
	m_bHpCoolTime = NULL;
	m_bBulletCoolTime = NULL;
}


CUnit::~CUnit()
{
}

void CUnit::MovePoint(INFO& _tInfo)
{
	if (false == m_bSelect)
		return;
	
	INFO& m_tInfo = _tInfo;

	POINT pt = {};
	GetCursorPos(&pt);					// 마우스의 좌표를 얻어오는 함수. 애는 스크린 기준 좌표를 얻어온다. 
	ScreenToClient(g_hWnd, &pt);		//스크린 좌표에서 클라이언트 좌표로 변환 시켜준다. 

	if (CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
	{
		CSoundMgr::GetInstance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
		//m_vPoint.x = float(pt.x - CScrollMgr::Get_ScrollX());
		//m_vPoint.y = float(pt.y - CScrollMgr::Get_ScrollY());

		if (false == m_bSelectFinishWork)
		{
			m_vPoint.x = float(pt.x);
			m_vPoint.y = float(pt.y);
			m_tInfo.vDir = m_vPoint - m_tInfo.vPos;
		}
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		m_eNextState = STATE::WORK;
		//m_fAngle = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);
		m_fCos = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

		m_bTileCheckX = false;
		m_bTileCheckY = false;
	}

	if (STATE::WORK == m_eCurState)
	{
		bool bArriveX = false;
		bool bArriveY = false;

		// 타일X축 충돌체크
		if (false == m_bTileCheckX && m_tInfo.vPos.x < 152 + CScrollMgr::Get_ScrollX())
		{
			bArriveX = true;
			m_bTileCheckX = true;
			m_tInfo.vPos.x = 152.f + CScrollMgr::Get_ScrollX();
		}
		else if (false == m_bTileCheckX &&  m_tInfo.vPos.x > 848 + CScrollMgr::Get_ScrollX())
		{
			bArriveX = true;
			m_bTileCheckX = true;
			m_tInfo.vPos.x = 848.f + CScrollMgr::Get_ScrollX();
		}
		// 타일Y축 충돌체크
		if (false == m_bTileCheckY && m_tInfo.vPos.y < 145 + CScrollMgr::Get_ScrollY())
		{
			bArriveY = true;
			m_bTileCheckY = true;
			m_tInfo.vPos.y = 145.f + CScrollMgr::Get_ScrollY();
		}
		else if (false == m_bTileCheckY && m_tInfo.vPos.y > 630 + CScrollMgr::Get_ScrollY())
		{
			bArriveY = true;
			m_bTileCheckY = true;
			m_tInfo.vPos.y = 630.f + CScrollMgr::Get_ScrollY();
		}

		if (m_tInfo.vDir.x > 0)  // 오른쪽 이동 
		{
			m_eDir = DIR::RIGHT;
			if (m_tInfo.vPos.x > m_vPoint.x)
				bArriveX = true;
		}
		else					 // 왼쪽 이동
		{
			m_eDir = DIR::LEFT;
			if (m_tInfo.vPos.x < m_vPoint.x)
				bArriveX = true;
		}

		if (m_tInfo.vDir.y > 0)  // 아래쪽 이동 
		{
			if (m_tInfo.vPos.y > m_vPoint.y)
				bArriveY = true;
		}
		else					 // 위쪽 이동
		{
			if (m_tInfo.vPos.y < m_vPoint.y)
				bArriveY = true;
		}

		if (false == bArriveX && false == m_bTileCheckX)
			m_tInfo.vPos.x += m_tInfo.vDir.x * m_fSpeed;
		if (false == bArriveY && false == m_bTileCheckY)
			m_tInfo.vPos.y += m_tInfo.vDir.y * m_fSpeed;

		if (m_bTileCheckX && bArriveY)
		{
			m_eNextState = STATE::NONE;
		}
		if (m_bTileCheckY && bArriveX)
		{
			m_eNextState = STATE::NONE;
		}
		if (bArriveX && bArriveY)
		{
			m_eNextState = STATE::NONE;
			if (m_bSelectFinishWork)
			{
				m_bSelectFinishWork = false;
				m_bSelect = false;
			}
		}
	}
}

void CUnit::AttackRange()
{
	list<CObj*> listObj = CObjMgr::GetInstance()->Get_Obj(OBJID::ENEMY);

	D3DXVECTOR3 vRange = { 0.f, 0.f, 0.f};
	float fRange = 200.f;
	
	for (auto& pObj : listObj)
	{
		//D3DXVECTOR3 
		D3DXVECTOR3 vObjPos = { pObj->Get_Info().vPos.x + CScrollMgr::Get_ScrollX(), pObj->Get_Info().vPos.y + CScrollMgr::Get_ScrollY(), 0.f };
		vRange = vObjPos - m_tInfo.vPos;

		if (fRange >= D3DXVec3Length(&vRange))
		{
			// 충돌Rect 보기 (시작)
			if(STATE::NONE == m_eCurState)
				m_eNextState = STATE::ATTACK;

			UNIT_INFO* tInfo = SCAST<CUnit*>(pObj)->Get_UnitInfo();
			if (m_bHpCoolTime + 80 < GetTickCount() && STATE::ATTACK == m_eCurState)
			{
				tInfo->fHp-=5.f;
				m_bHpCoolTime = GetTickCount();
			}
			if (m_bBulletCoolTime + 1000 < GetTickCount())
			{
				CSoundMgr::GetInstance()->MyPlaySound(L"Bullet.wav", CSoundMgr::UI);
				m_bBulletCoolTime = GetTickCount();
			}
			
			if(0 > tInfo->fHp)
				SCAST<CUnit*>(pObj)->Set_DeadState();

			D3DXVECTOR3 vDir;
			D3DXVec3Normalize(&vDir, &vRange);
			m_fCos = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

			CDeviceMgr::GetInstance()->GetSprite()->Draw(
				CTextureMgr::GetInstance()->FindTexture(L"Marine", L"Bullet", 0)->pTexture,
				nullptr,																							/* Rect의 포인터, 그릴 영역 */
				&D3DXVECTOR3(vRange.x, vRange.y, 0.0f),																/* 출력 중심점 */
				nullptr,																							/* 출력 위치 */
				D3DCOLOR_ARGB(255, 255, 255, 255)
			);
		}
		else
		{
			//if (STATE::ATTACK == m_eCurState)
				//m_eNextState = STATE::NONE;
		}
	}
}

