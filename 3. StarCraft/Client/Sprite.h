#pragma once
#include "Obj.h"
class CSprite :
	public CObj
{
public:
	CSprite();
	virtual ~CSprite();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void Set_CenterView() { m_bCenterView = true; }
	void Set_ScroolFalse() { m_bScroolCheck = false; }

private:
	bool m_bCenterView;			// ����� �߽����� ����� üũ
	bool m_bScroolCheck;		// ��ũ���� �����Ұ��� üũ
};

