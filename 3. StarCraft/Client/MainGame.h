#pragma once
class CSingleTexture;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	void Render_Fps(HDC _hDC);

public:
	void TextureInsert_LOGO();
	void TextureInsert_MENU();
	void TextureInsert_STAGE();

private:
	HDC	m_hDC;
};

