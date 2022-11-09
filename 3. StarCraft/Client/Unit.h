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
		char	szName[16];			//�̸�
		int		iAtt;				//���ݷ�
		int		iAtt_UpGradeNum;	//���ݷ� ���� Ƚ��
		int		iArm;				//����
		int		iArm_UpGradeNum;	//���� ���� Ƚ��
		float	fHp;				//����ü��
		int		iMaxHp;				//�ִ�ü��
		int		iAttRange;			//��Ÿ�
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
	int m_iCurLook;								// ���� �ٶ󺸴� ��
	int m_iNextLook;							// ���� �ٶ� ��
	wstring m_wsUnitStateKey[STATE::END];		// State �� �ִϸ��̼� Ű��
	bool m_bSelect;								// �����ȰǸ� ������ üũ ������
	D3DXVECTOR3 m_vPoint;						// ���콺 ����Ʈ ���� �� �̵��� �Ÿ�
	float m_fSpeed;
	float m_fCos;								// vDir, vLook�� ���� Cos�� ���� �� �������
	int m_iStateCurFrame[STATE::END];			// State �� �ִϸ��̼� ������ Start,End�� �ֽ�ȭ
	DIR m_eDir;
	UNIT_INFO m_tUnitInfo;						// ���� Info
	bool m_bTileCheckX;
	bool m_bTileCheckY;
	bool m_bSelectFinishWork;
	bool m_bDeadState;
	DWORD m_bHpCoolTime;
	DWORD m_bBulletCoolTime;
};

