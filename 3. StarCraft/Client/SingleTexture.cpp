#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

const TEX_INFO* CSingleTexture::GetTexInfo(
	const wstring & wstrStateKey,
	const int & iIndex)
{
	return m_pTexInfo;
}

HRESULT CSingleTexture::LoadTexture(
	const wstring & wstrFilePath,
	const wstring & wstrStateKey /*= L""*/,
	const int & iCount/* = 0*/)
{
	m_pTexInfo = new TEX_INFO;
	ZeroMemory(m_pTexInfo, sizeof(TEX_INFO));

	HRESULT hr = 0;
	hr = D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTexInfo->tImgInfo);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXGetImageInfoFromFile Failed", E_FAIL);

	// IDIRECT3DTEXTURE9 ����
	hr = D3DXCreateTextureFromFileEx(
		CDeviceMgr::GetInstance()->GetDevice(), /* ��ġ */
		wstrFilePath.c_str(), /* �̹��� ��� */
		m_pTexInfo->tImgInfo.Width, /* �̹��� ����ũ�� */
		m_pTexInfo->tImgInfo.Height, /* �̹��� ����ũ�� */
		m_pTexInfo->tImgInfo.MipLevels, /* mip level */
		0,
		m_pTexInfo->tImgInfo.Format, /* �̹��� �ȼ� ���� */
		D3DPOOL_MANAGED, /* �޸� ����� */
		D3DX_DEFAULT,	/* �̹��� �׵θ� ǥ��(����) */
		D3DX_DEFAULT,	/* Mip Filter */
		0, /* Color key ������ ���� */
		nullptr, /* D3DXIMAGE_INFO�� ������ */
		nullptr, /* �̹��� �ȷ�Ʈ */
		&m_pTexInfo->pTexture);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateTextureFromFileEx Failed", E_FAIL)

	return S_OK;
}

void CSingleTexture::Release()
{
	if (SafeRelease(m_pTexInfo->pTexture))
		ERR_MSG(L"m_pTexInfo->pTexture Release Failed")

	SafeDelete(m_pTexInfo);
}
