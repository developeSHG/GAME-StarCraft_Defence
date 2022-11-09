#pragma once
#include "Obj.h"
class CAniSprite :
	public CObj
{
public:
	CAniSprite();
	virtual ~CAniSprite();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void Set_ScroolFalse() { m_bScroolCheck = false; }

private:
	bool m_bScroolCheck;		// ��ũ���� �����Ұ��� üũ
};

