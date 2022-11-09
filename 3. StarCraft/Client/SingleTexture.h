#pragma once
#include "Texture.h"
class CSingleTexture :
	public CTexture
{
public:
	explicit CSingleTexture();

public:
	virtual ~CSingleTexture();

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"",
		const int& iIndex = 0) override;

public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT LoadTexture(
		const wstring & wstrFilePath,
		const wstring & wstrStateKey = L"",
		const int & iCount = 0) override;
	virtual void Release() override;

private:
	TEX_INFO*	m_pTexInfo;
};

