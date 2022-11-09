#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEX_INFO * CMultiTexture::GetTexInfo(const wstring & wstrStateKey, const int & iIndex)
{
	map<const wstring, vector<TEX_INFO*>*>::iterator iter = m_mapVecTexInfo.find(wstrStateKey);

	if (iter == m_mapVecTexInfo.end())
		return nullptr;

	return iter->second->at(iIndex);
}

HRESULT CMultiTexture::LoadTexture(const wstring & wstrFilePath, const wstring & wstrStateKey, const int & iCount)
{
	if (m_mapVecTexInfo.end() == m_mapVecTexInfo.find(wstrStateKey))
		FAILED_CHECK_MSG_RETURN(TRUE, L"D3DXGetImageInfoFromFile Failed", E_FAIL)

	vector<TEX_INFO*>* pVecTexInfo = new vector<TEX_INFO*>;
	pVecTexInfo->reserve(size_t(iCount));

	TEX_INFO* pTexInfo = nullptr;
	HRESULT hr = 0;
	for (int i = 0; i < iCount; ++i)
	{
		wstring TexturePath = wstrFilePath;
		TexturePath.insert(TexturePath.length() - 4, L"_" + to_wstring(i));

		pTexInfo = new TEX_INFO;
		ZeroMemory(pTexInfo, sizeof(TEX_INFO));
		hr = D3DXGetImageInfoFromFile(TexturePath.c_str(), &pTexInfo->tImgInfo);
		FAILED_CHECK_MSG_RETURN(hr, L"D3DXGetImageInfoFromFile Failed", E_FAIL);

		hr = D3DXCreateTextureFromFileEx(
			CDeviceMgr::GetInstance()->GetDevice(), /* ��ġ */
			TexturePath.c_str(), /* �̹��� ��� */
			pTexInfo->tImgInfo.Width, /* �̹��� ����ũ�� */
			pTexInfo->tImgInfo.Height, /* �̹��� ����ũ�� */
			pTexInfo->tImgInfo.MipLevels, /* mip level */
			0,
			pTexInfo->tImgInfo.Format, /* �̹��� �ȼ� ���� */
			D3DPOOL_MANAGED, /* �޸� ����� */
			D3DX_DEFAULT,	/* �̹��� �׵θ� ǥ��(����) */
			D3DX_DEFAULT,	/* Mip Filter */
			D3DCOLOR_ARGB(255, 0, 0, 0), /* Color key ������ ���� */
			nullptr, /* D3DXIMAGE_INFO�� ������ */
			nullptr, /* �̹��� �ȷ�Ʈ */
			&pTexInfo->pTexture);
		FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateTextureFromFileEx Failed", E_FAIL)

		pVecTexInfo->emplace_back(pTexInfo);
	}
	m_mapVecTexInfo.emplace(wstrStateKey, pVecTexInfo);
	return S_OK;
		
	return E_NOTIMPL;
}

void CMultiTexture::Release()
{

	for (map<const wstring, vector<TEX_INFO*>*>::iterator iter = m_mapVecTexInfo.begin(); m_mapVecTexInfo.end() != iter;)
	{
		for (size_t i = 0; i < iter->second->size(); ++i)
		{
			if (SafeRelease(iter->second->at(i)->pTexture))
				ERR_MSG(L"m_pTexInfo->pTexture Release Failed")
			SafeDelete(iter->second->at(i));
		}
		SafeDelete(iter->second);
		iter = m_mapVecTexInfo.erase(iter);
	}
	m_mapVecTexInfo.clear();
}
