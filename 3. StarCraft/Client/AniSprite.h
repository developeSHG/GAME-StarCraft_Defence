#pragma once
#include "Obj.h"
class CAniSprite :
	public CObj
{
public:
	CAniSprite();
	virtual ~CAniSprite();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void Set_ScroolFalse() { m_bScroolCheck = false; }

private:
	bool m_bScroolCheck;		// 스크롤을 적용할건지 체크
};

