#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();
public:
	static void Set_ScrollX(int iScrollX) { m_iScrollX += iScrollX; }
	static int Get_ScrollX() { return m_iScrollX; }

	static void Set_ScrollY(int iScrollY) { m_iScrollY += iScrollY; }
	static int Get_ScrollY() { return m_iScrollY; }

	static void ScrollLock();

private:
	static int m_iScrollX;
	static int m_iScrollY;
};