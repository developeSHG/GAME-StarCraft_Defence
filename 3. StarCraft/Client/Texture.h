#pragma once
class CTexture
{
public:
	explicit CTexture();

public:
	virtual ~CTexture();

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"",
		const int& iIndex = 0) PURE;

public:
	virtual HRESULT LoadTexture(
		const wstring& wstrFilePath,			/* �ؽ�ó ��� */
		const wstring& wstrStateKey = L"",		/* ���� Ű�� ��Ƽ �ؽ�ó�� ���� ��� */
		const int& iCount = 0) PURE;			/* �ҷ��� �̹��� ����. �ؽ�ó�� ���� ��� */
	virtual void Release() PURE;
};

