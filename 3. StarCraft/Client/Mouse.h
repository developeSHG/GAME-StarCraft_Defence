#pragma once
#include "Obj.h"

class CMouse :
	public CObj
{
public:
	CMouse();
	virtual ~CMouse();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void FrameCheck();

public:
	void KeyInput();

private:
	enum STATE
	{
		NORMAL, UNITON, CLICK
	};

private:
	STATE m_eCurState;
	STATE m_eNextState;
	bool m_bClickCheck;
};

