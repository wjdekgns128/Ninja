#include "cLogo.h"

cLogo::cLogo()
{
	m_pSprite = NULL;
	m_pAnimate = NULL;
	m_pCursor = NULL;

	m_alpa = 0.0;
}


cLogo::~cLogo()
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pCursor);
}


HRESULT cLogo::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSprite == NULL)
	{
		m_pSprite = new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"../res/te/logo.te");
	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate = new KGAnimate(m_pSprite);
	}
	if(m_pCursor == NULL)
	{
		m_pCursor = new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768), L"cur", L"cur");
	}
	return S_OK;
}


HRESULT cLogo::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	return S_OK;
}


void cLogo::OnLostDevice(void* pUserContext)
{
}


void cLogo::OnDestroyDevice(void* pUserContext)
{
}


void cLogo::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(m_alpa < 1.0)
		m_alpa += 0.01;
	if(fTime > 3.5)
		cMain()->Trans(L"menu");
}


void cLogo::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		m_pSprite->Render( L"logo", D3DXVECTOR3(512, 384, 0), D3DXCOLOR(1, 1, 1, m_alpa) );
		SAFE_ONFRAMERENDER(m_pCursor);
		V(pd3dDevice->EndScene());
	}
}


void cLogo::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
}


void cLogo::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	
	SAFE_ONMOUSE(m_pCursor);
}


LRESULT cLogo::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return uMsg;
}
