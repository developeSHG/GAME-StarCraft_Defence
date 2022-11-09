#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;

	RECT rcRect;

	D3DXMATRIX matScale;
	D3DXMATRIX matRotate;
	D3DXMATRIX matTrans;
	D3DXMATRIX matWorld;		
}INFO;

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9	pTexture;
	D3DXIMAGE_INFO		tImgInfo;
}TEX_INFO;

typedef struct tagFrame
{
	int iFrameStart;
	int iFrameEnd;
	int iFrameScene;
	DWORD dwFrameSpeed;
	DWORD dwFrameTime;
}FRAME;

