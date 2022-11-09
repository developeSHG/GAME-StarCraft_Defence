#pragma once
#include "Unit.h"
class CBattleCr :
	public CUnit
{
public:
	CBattleCr();
	virtual ~CBattleCr();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void FrameCheck() override;
	virtual void StateCurFrameCheck() override;
};

