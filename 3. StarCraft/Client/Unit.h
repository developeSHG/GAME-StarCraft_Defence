#pragma once

#include "Obj.h"
class CUnit : 
	public CObj
{
public:
	CUnit();
	virtual ~CUnit();

public:
	virtual void StateCurFrameCheck() {};

public:
	enum STATE
	{
		NONE, WORK, ATTACK, DEAD, END
	};
	enum DIR
	{
		LEFT, RIGHT, UP, DOWN
	};
	//enum DIR
	//{
	//	DOWN, RIGHT, UP, LEFT
	//};
	typedef struct tagUnitInfo
	{
		char	szName[16];			//이름
		int		iAtt;				//공격력
		int		iAtt_UpGradeNum;	//공격력 업글 횟수
		int		iArm;				//방어력
		int		iArm_UpGradeNum;	//방어력 업글 횟수
		float	fHp;				//현재체력
		int		iMaxHp;				//최대체력
		int		iAttRange;			//사거리
	}UNIT_INFO;

public:
	const bool& Get_Select() const { return m_bSelect; }
	const STATE& Get_State() const { return m_eCurState; }
	UNIT_INFO* Get_UnitInfo() { return &m_tUnitInfo; }

public:
	void MovePoint(INFO& _tInfo);
	void AttackRange();

public:
	void Set_Select(const bool& _bSelect) { m_bSelect = _bSelect; }
	void Set_Dir(DIR _eDir) { m_eDir = _eDir; }
	void Set_SelectFinishWorkFalse() { m_bSelectFinishWork = false; }
	void Set_SelectFinishWork() { m_bSelectFinishWork = true; }
	void Set_DeadState() { m_bDeadState = true; }

protected:
	STATE m_eCurState;
	STATE m_eNextState;
	int m_iCurLook;								// 현재 바라보는 곳
	int m_iNextLook;							// 다음 바라볼 곳
	wstring m_wsUnitStateKey[STATE::END];		// State 별 애니메이션 키값
	bool m_bSelect;								// 셀렉된건만 움직일 체크 데이터
	D3DXVECTOR3 m_vPoint;						// 마우스 포인트 찍은 후 이동할 거리
	float m_fSpeed;
	float m_fCos;								// vDir, vLook의 내적 Cos값 연산 후 각도계산
	int m_iStateCurFrame[STATE::END];			// State 별 애니메이션 프레임 Start,End값 최신화
	DIR m_eDir;
	UNIT_INFO m_tUnitInfo;						// 유닛 Info
	bool m_bTileCheckX;
	bool m_bTileCheckY;
	bool m_bSelectFinishWork;
	bool m_bDeadState;
	DWORD m_bHpCoolTime;
	DWORD m_bBulletCoolTime;
};

