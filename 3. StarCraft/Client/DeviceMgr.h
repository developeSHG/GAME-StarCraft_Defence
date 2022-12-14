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
	// 장치검증에 필요한 Com객체. (IDirect3D9)
	// LPDIRECT3DDEVICE9의 생성도 맡는다.
	LPDIRECT3D9			m_pSDK;

	// 그래픽 장치를 제어할 Com객체.
	LPDIRECT3DDEVICE9	m_pGraphicDev;

	// 이미지 렌더링 Com객체.
	LPD3DXSPRITE		m_pSprite;

	// COM (Component Object Model)
};

