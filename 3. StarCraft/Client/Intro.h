#pragma once
#include "Scene.h"
class CIntro :
	public CScene
{
public:
	CIntro();
	virtual ~CIntro();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	HWND m_hVideo;
};

