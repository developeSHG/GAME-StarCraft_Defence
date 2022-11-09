#include "stdafx.h"
#include "MyButton.h"

#include "SceneMgr.h"

CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{

}

void CMyButton::Initialize()
{
	// CObj 상속변수 (초기화 변경 필요시 코딩)

	// CMyButton 고유변수 (초기화 변경 필요시 코딩)
}

int CMyButton::Update()
{
	if (true == m_bIsDead)
		return OBJ_DEAD;

	return OBJ_LIVE;
}

void CMyButton::LateUpdate()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tInfo.rcRect, pt))
	{
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			if (L"Button_Single" == m_wsImageKey)
			{
				CSoundMgr::GetInstance()->MyPlaySound(L"MouseDown.wav", CSoundMgr::UI);
				CSceneMgr::GetInstance()->SceneChange(CSceneMgr::SCENE_STAGE);
				return;
			}
			else if (L"Button_Exit" == m_wsImageKey)
			{
				CSoundMgr::GetInstance()->MyPlaySound(L"MouseDown.wav", CSoundMgr::UI);
				DestroyWindow(g_hWnd);
			}
		}
		m_tFrame.iFrameStart = 1;
	}
	else
		m_tFrame.iFrameStart = 0;

	CObj::UpdateRect();				// 충돌Rect 초기화
}

void CMyButton::Render()
{
	// 충돌Rect 보기 (시작)
	if (GetAsyncKeyState('Q') & 0x8000)
		CObj::ViewRect();
	else
		m_bViewRect = false;
	// 충돌Rect 보기 (끝)

	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, L"Normal", m_tFrame.iFrameStart);

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, L"Normal", m_tFrame.iFrameStart)->pTexture,
		nullptr,																						/* Rect의 포인터, 그릴 영역 */
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),	/* 출력 중심점 */
		nullptr,																						/* 출력 위치 */
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CMyButton::Release()
{
}
