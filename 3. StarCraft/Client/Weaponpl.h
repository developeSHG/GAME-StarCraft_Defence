#pragma once
#include "Unit.h"
class CWeaponpl : public CUnit
{
public:
	CWeaponpl();
	virtual ~CWeaponpl();
public:
	// CUnit��(��) ���� ��ӵ�
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

