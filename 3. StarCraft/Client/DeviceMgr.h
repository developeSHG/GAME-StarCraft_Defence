#pragma once
class CDeviceMgr
{
	DECLARE_SINGLETON(CDeviceMgr)

public:
	enum MODE { MODE_FULL, MODE_WIN };

private:
	CDeviceMgr();
	~CDeviceMgr();

public:
	LPDIRECT3DDEVICE9 GetDevice() const;
	LPD3DXSPRITE GetSprite() const;

public:
	HRESULT InitDevice(
		HWND hWnd, const DWORD& dwWinCX,
		const DWORD& dwWinCY, MODE eMode);
	void Render_Begin();
	void Render_End();
	void Release();

private:
	// ��ġ������ �ʿ��� Com��ü. (IDirect3D9)
	// LPDIRECT3DDEVICE9�� ������ �ô´�.
	LPDIRECT3D9			m_pSDK;

	// �׷��� ��ġ�� ������ Com��ü.
	LPDIRECT3DDEVICE9	m_pGraphicDev;

	// �̹��� ������ Com��ü.
	LPD3DXSPRITE		m_pSprite;

	// COM (Component Object Model)
};

