#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize() abstract;
	virtual int	 Update() abstract;
	virtual void LateUpdate() abstract;
	virtual void Render() abstract;
	virtual void Release() abstract;
};

