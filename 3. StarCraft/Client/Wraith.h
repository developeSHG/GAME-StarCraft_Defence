#pragma once
#include "Unit.h"
class CWraith : public CUnit
{
public:
	CWraith();
	virtual ~CWraith();
public:
	// CUnit을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual void FrameCheck() override;
	virtual void StateCurFrameCheck() override;
private:

};

