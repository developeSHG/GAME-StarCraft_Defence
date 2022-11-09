#pragma once
#include "Unit.h"
class CCarrier :
	public CUnit
{
public:
	CCarrier();
	virtual ~CCarrier();

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

