#pragma once
#include "Obj.h"
class CCollRect :
	public CObj
{
public:
	CCollRect();
	virtual ~CCollRect();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	enum DIR
	{
		LEFT, RIGHT, UP, DOWN
	};

public:
	const DIR& Get_Dir() const { return m_eDir; }

public:
	void Set_Dir(DIR _eDir) { m_eDir = _eDir; }

private:
	DIR	m_eDir;

};

