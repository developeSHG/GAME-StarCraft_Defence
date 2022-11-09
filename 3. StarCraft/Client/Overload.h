#pragma once
#include "Unit.h"
class COverload : public CUnit
{
public:
	COverload();
	virtual ~COverload();

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

