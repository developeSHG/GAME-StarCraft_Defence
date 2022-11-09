#pragma once
#include "Obj.h"
class CMyButton :
	public CObj
{
public:
	CMyButton();
	virtual ~CMyButton();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

};

