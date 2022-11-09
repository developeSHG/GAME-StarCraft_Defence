#pragma once

class CObj
{
public:
	explicit CObj();
	virtual ~CObj();

public:
	virtual void Initialize() abstract;
	virtual int Update() abstract;
	virtual void LateUpdate() abstract;
	virtual void Render() abstract;
	virtual void Release() abstract;

public:
	virtual void LateInit();
	virtual void FrameCheck() {};

public:
	// Get
	const INFO& Get_Info() const { return m_tInfo; }
	const bool& Get_Dead() const { return m_bIsDead; }
	const RECT& Get_Rect() const { return m_tInfo.rcRect; }

public:
	// Set
	void Set_Pos(float _x, float _y)
	{
		m_tInfo.vPos.x = _x;
		m_tInfo.vPos.y = _y;
	}
	void Set_Dead() { m_bIsDead = OBJ_DEAD; }
	void Set_ImageKey(const wstring& _wsImageKey) { m_wsImageKey = _wsImageKey; }
	void Set_StateKey(const wstring& _wsStateKey) { m_wstStateKey = _wsStateKey; }
	void Set_Size(float _x, float _y) 
	{ 
		m_tInfo.vSize.x = _x;
		m_tInfo.vSize.y = _y;
	}
	void Set_FrameEnd(int _iFrameEnd) { m_tFrame.iFrameEnd = _iFrameEnd; }
	void Set_ViewRect() { m_bViewRect = true; }

public:
	void UpdateRect();
	void MoveFrame();
	void MoveFrame(int _iFrameStart);
	void ViewRect();

protected:
	INFO m_tInfo;
	wstring m_wsImageKey;
	wstring m_wstStateKey;
	FRAME m_tFrame;

protected:
	bool m_bIsDead;	
	bool m_bIsInit;				// 한번만 실행시킬지 결정할 데이터
	bool m_bViewRect;			// 충돌렉트를 볼지 체크할 데이터

};

