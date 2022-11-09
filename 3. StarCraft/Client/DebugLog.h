#pragma once
class CDebugLog
{
public:
	CDebugLog();
	~CDebugLog();
public:
	void DebugLog(HDC hDC, float fData, int x, int y)
	{
		memset(szDebug, 0, lstrlen(szDebug));
		swprintf_s(szDebug, L"%5.2lf", fData);
		TextOut(hDC, x, y, szDebug, lstrlen(szDebug));
	}
	void DebugLog(HDC hDC, LPCWSTR szData, int x, int y)
	{
		memset(szDebug, '\0', lstrlen(szDebug));
		swprintf_s(szDebug, L"%s", szData);
		wsprintf(szDebug, szData);
		TextOut(hDC, x, y, szDebug, lstrlen(szDebug));
	}
	//void DebugLog(HDC hDC, LPCWSTR szData, int x, int y)
	//{
	//	if (FAILED(hr))						
	//	{									
	//		ERR_MSG(msg);					
	//		return;							
	//	}
	//}
private:
	TCHAR szDebug[32];
};
extern CDebugLog huibeom;


