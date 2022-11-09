#pragma once
#include "Unit.h"
class CBattleCr :
	public CUnit
{
public:
	CBattleCr();
	virtual ~CBattleCr();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void FrameCheck() override;
	virtual void StateCurFrameCheck() override;
};

