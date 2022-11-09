#pragma once
#include "Obj.h"
class CSprite :
	public CObj
{
public:
	CSprite();
	virtual ~CSprite();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void Set_CenterView() { m_bCenterView = true; }
	void Set_ScroolFalse() { m_bScroolCheck = false; }

private:
	bool m_bCenterView;			// 출력을 중심점에 놀건지 체크
	bool m_bScroolCheck;		// 스크롤을 적용할건지 체크
};

