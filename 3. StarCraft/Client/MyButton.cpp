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
	// CObj ��Ӻ��� (�ʱ�ȭ ���� �ʿ�� �ڵ�)

	// CMyButton �������� (�ʱ�ȭ ���� �ʿ�� �ڵ�)
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

	CObj::UpdateRect();				// �浹Rect �ʱ�ȭ
}

void CMyButton::Render()
{
	// �浹Rect ���� (����)
	if (GetAsyncKeyState('Q') & 0x8000)
		CObj::ViewRect();
	else
		m_bViewRect = false;
	// �浹Rect ���� (��)

	const TEX_INFO* TextureInfo = CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, L"Normal", m_tFrame.iFrameStart);

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans;
	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDeviceMgr::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->FindTexture(m_wsImageKey, L"Normal", m_tFrame.iFrameStart)->pTexture,
		nullptr,																						/* Rect�� ������, �׸� ���� */
		&D3DXVECTOR3(TextureInfo->tImgInfo.Width * 0.5f, TextureInfo->tImgInfo.Height * 0.5f, 0.0f),	/* ��� �߽��� */
		nullptr,																						/* ��� ��ġ */
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CMyButton::Release()
{
}
