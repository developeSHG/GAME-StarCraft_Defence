#include "stdafx.h"
#include "ScrollMgr.h"

int CScrollMgr::m_iScrollX = 0;
int CScrollMgr::m_iScrollY = 0;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::ScrollLock()
{
	if (m_iScrollX > 0)
		m_iScrollX = 0;
	if (m_iScrollY > 0)
		m_iScrollY = 0;

	//if (WINCX - TILECX * TILEX > m_iScrollX)
	//	m_iScrollX = WINCX - TILECX * TILEX;
	//if (WINCY - TILECY * TILEY > m_iScrollY)
	//	m_iScrollY = WINCY - TILECY * TILEY;
	// -1110, -1315
}
