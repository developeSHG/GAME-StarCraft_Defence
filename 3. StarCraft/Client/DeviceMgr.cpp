#include "stdafx.h"
#include "DeviceMgr.h"

IMPLEMENT_SINGLETON(CDeviceMgr)

CDeviceMgr::CDeviceMgr()
{
}


CDeviceMgr::~CDeviceMgr()
{
	Release();
}

LPDIRECT3DDEVICE9 CDeviceMgr::GetDevice() const
{
	return m_pGraphicDev;
}

LPD3DXSPRITE CDeviceMgr::GetSprite() const
{
	return m_pSprite;
}

HRESULT CDeviceMgr::InitDevice(
	HWND hWnd, const DWORD& dwWinCX,
	const DWORD& dwWinCY, MODE eMode)
{
	HRESULT hr = 0;

	// ��ġ�ʱ�ȭ
	// 1. IDirect3D9 ����	
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	// 2. ��ġ ���� (���� �׷��� ī���� ��� �� �������� ����)

	// HAL (Hardware Abstraction Layer)
	// �ϵ���� �߻� ����

	D3DCAPS9 Caps;
	ZeroMemory(&Caps, sizeof(D3DCAPS9));

	// ���� �׷��� ī���� ������ �˾Ƴ��� �ִ�.
	hr = m_pSDK->GetDeviceCaps(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps);
	FAILED_CHECK_MSG_RETURN(hr, L"GetDeviceCaps Failed", E_FAIL);

	// ���ؽ� ���μ��� ���� ����.
	// - ���� �׷��� ī�忡�� ���ؽ� ���μ����� �����ϴ°�
	// - ���ؽ� ���μ���: ������ȯ + ������
	DWORD vp = 0;

	if (Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//// �÷��� ����
	//DWORD ���� = 0x0001;
	//DWORD �̼� = 0x0002;
	//DWORD ���� = 0x0004;
	//DWORD ���� = 0x0008;

	//DWORD ������� = ���� | ����;

	//if (������� & ����)
	//	���ݷ� ����;
	//if (������� & �̼�)
	//	�̵��� ����;
	//if (������� & ����)
	//	������� ����;
	//if (������� & ����)
	//	������� ����;


	// 3. IDirect3DDevice9 ����

	// ������ ȯ�� ����.
	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = dwWinCX;	// �ĸ���� ����ũ��
	d3dpp.BackBufferHeight = dwWinCY;	// �ĸ���� ����ũ��
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // �ĸ���� �ȼ�����
	d3dpp.BackBufferCount = 1;	// �ĸ���� ����

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; // ��Ƽ���ø� �Ⱦ�.
	d3dpp.MultiSampleQuality = 0;

	// ������ ���
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // ����ü�� ���.
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = eMode;	// TRUE â���, FALSE ��üȭ����.
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = m_pSDK->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, vp, &d3dpp, &m_pGraphicDev);
	//FAILED_CHECK_MSG_RETURN(hr, L"CreateDevice Failed", E_FAIL);

	// ID3DXSprite ����
	hr = D3DXCreateSprite(m_pGraphicDev, &m_pSprite);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateSprite Failed", E_FAIL);

	return S_OK;
}

void CDeviceMgr::Render_Begin()
{
	// ������ ����.
	// 1. �ĸ���۸� ����.
	m_pGraphicDev->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	// 2. �ĸ���ۿ� �׸��� �����Ѵ�.
	m_pGraphicDev->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDeviceMgr::Render_End()
{
	// 3. �ĸ���ۿ� �׸��⸦ ����ģ��.
	m_pSprite->End();
	m_pGraphicDev->EndScene();

	// 4. �ĸ���۸� ������۷� ��ü�Ͽ� �������Ѵ�.
	m_pGraphicDev->Present(nullptr, nullptr, nullptr, nullptr);
}

void CDeviceMgr::Release()
{
	//// Release ���� ����!
	if (SafeRelease(m_pSprite))
		MessageBox(g_hWnd, L"m_pSprite Release Failed",L"m_pSprite Release Failed", MB_YESNO);
		ERR_MSG(L"m_pSprite Release Failed");

	if (SafeRelease(m_pGraphicDev))
		MessageBox(g_hWnd, L"m_pGraphicDev Release Failed", L"m_pGraphicDev Release Failed", MB_YESNO);

	if (SafeRelease(m_pSDK))
		ERR_MSG(L"m_pSDK Release Failed");
}
