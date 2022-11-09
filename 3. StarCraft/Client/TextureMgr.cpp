#include "stdafx.h"
#include "TextureMgr.h"

#include "Texture.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}

CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEX_INFO * CTextureMgr::FindTexture(const wstring & rImageKey, const wstring & wstrStateKey, const int & iIndex)
{
	map<const wstring, CTexture*>::iterator iter = m_mapTexture.find(rImageKey);

	if (iter == m_mapTexture.end())
		return nullptr;
	if (0 == wstrStateKey.length())
		return iter->second->GetTexInfo();
	else
		return iter->second->GetTexInfo(wstrStateKey, iIndex);

}

void CTextureMgr::InsertTexture(const wstring & rFilePath, const wstring & rImageKey, const wstring & wstrStateKey, const int & iCount)
{
	map<const wstring, CTexture*>::iterator iter = m_mapTexture.find(rImageKey);

	if (iter == m_mapTexture.end())
	{
		CTexture* pTexture = nullptr;
		if (0 == wstrStateKey.length())
			pTexture = new CSingleTexture();
		else
			pTexture = new CMultiTexture;

		HRESULT hr = pTexture->LoadTexture(rFilePath, wstrStateKey, iCount);
		FAILED_CHECK_RETURN(hr, )
		m_mapTexture.emplace(rImageKey, pTexture);
	}
	else
	{
		if (0 == wstrStateKey.length())
			ERR_MSG(L"이미 그림이 있습니다.")
		else
		{
			HRESULT hr = iter->second->LoadTexture(rFilePath, wstrStateKey, iCount);
			FAILED_CHECK_RETURN(hr, )
		}
	}
}

void CTextureMgr::Release()
{
	for (auto& pPair : m_mapTexture)
	{
		if (pPair.second)
		{
			delete pPair.second;
			pPair.second = nullptr;
		}
	}
	m_mapTexture.clear();
}
