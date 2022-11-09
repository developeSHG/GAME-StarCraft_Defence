#pragma once
#include "SingleTexture.h"
#include "Scene.h"
class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void KeyInput();
	void MouseInput();
	void Create_Enemy();

private:
	int WholeTime;
	int NowTime;
	int dTime;
	int EnemyCount;
	ID3DXFont* Font;
	bool m_bIsStart;
};

