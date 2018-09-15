#include "cMenu.h"

cMenu::cMenu()
{
	m_pSprite = NULL;
	m_pDialog = NULL;
	m_verMove = D3DXVECTOR3(0,0,0);
	m_pCursor	= NULL;
	m_pSound  = NULL;
	m_pAnimate = NULL;
	m_pHelp		= NULL;
	m_showHelp = false;

	for(int i=0;i<3;i++)
		m_start[i]  =  0;
	m_MoveTime = 0.0;
	m_help	= 0;
	m_fmoveapl = 1;

	if(m_pSound) {
		m_pSound->Play(L"bgm", true, 0, DSBPLAY_LOOPING);
	}
}


cMenu::~cMenu()
{
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pSound);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pHelp);
}
void cMenu::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pSound);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pHelp);
	
}

HRESULT cMenu::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"../res/te/menu.Te");
		m_pSprite->Entry(L"../res/te/menu_b.Te");
		m_pSprite->Entry(L"../res/te/RankInterface.Te");
		m_pSprite->Entry(L"../res/te/cursor.te");
		m_pSprite->Entry(L"../res/te/help1.te");
		m_pSprite->Entry(L"../res/te/help2.te");
		m_pSprite->Entry(L"../res/te/help3.te");
	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
	}
	if(m_pDialog == NULL)
	{
		m_pDialog = new KGDialog(m_pSprite,NULL,this);
		m_pDialog->AddButton(GAME_START,L"게임시작1",L"게임시작2",L"게임시작2",L"게임시작2",D3DXVECTOR3(160,300,0),true);
		m_pDialog->AddButton(GAME_HELP,L"도움말1",L"도움말2",L"도움말2",L"도움말2",D3DXVECTOR3(160,450,0),true);
		m_pDialog->AddButton(EXIT,L"나가기1",L"나가기2",L"나가기2",L"나가기2",D3DXVECTOR3(160,600,0),true);
	}
	if (m_pCursor == NULL)
	{
		m_pCursor = new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768), L"cur", L"cur");
	}
	if( m_pSound == NULL)
	{
		m_pSound = new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"sword_attack", L"../res/sound/effect/sword_attack.wav");
		m_pSound->Entry(L"main", L"../res/sound/bgm/main.wav");
		m_pSound->Play(L"main", true, 0, DSBPLAY_LOOPING);
	}
	if(m_pHelp == NULL)
	{
		m_pHelp = new cHelp(m_pAnimate, m_pSprite);
	}
	return S_OK;
}


HRESULT cMenu::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	return S_OK;
}


void cMenu::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	
}

void cMenu::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(m_showHelp == true) {
		SAFE_ONFRAMEMOVE(m_pHelp);
	}
	else {
		for(int i=0;i<3;i++)
			if(m_start[i] == 1)
			{
				m_MoveTime += fElapsedTime;
				m_verMove.x += 20;
				m_fmoveapl  -= 0.02;
				if(m_MoveTime > 0.45)
				{
					Next(i);
					m_MoveTime = 0;
				}
			}
	}
}


void cMenu::Next(int z)
{
	if( z == 0)
	{
		cMain()->Trans(L"game");
		m_pSound->Stop();
	}
	else if(z == 1)
		m_showHelp = true;
	else if (z == 2)
		cMain()->CloseWindow();

	for(int i=0;i<3;i++)
		m_start[i] = 0;
}


void cMenu::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{

		if(m_showHelp == true) {
			SAFE_ONFRAMERENDER(m_pHelp);
		}
		else {
			m_pSprite->Render(L"어쌔신훈의역습",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
			SAFE_ONFRAMERENDER(m_pDialog);
			for(int i=0;i<3;i++)
				if(m_start[i] == 1)
					m_pSprite->Render(L"표창",m_verMove,D3DXCOLOR(1,1,1,m_fmoveapl));
		}
		SAFE_ONFRAMERENDER(m_pCursor);
		V(pd3dDevice->EndScene());
	}
}


void cMenu::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

}


void cMenu::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	SAFE_ONMOUSE(m_pCursor);
	
	SAFE_ONMOUSE(m_pDialog);
	if(m_showHelp == true) {
		if(m_pHelp->OnMouse(bButtonDown, bLeftButtonDown, bRightButtonDown, bMiddleButtonDown, bSideButton1Down, bSideButton2Down, nMouseWheelDelta, xPos, yPos,pUserContext)) {
			m_showHelp = false;
		}
	}
}


LRESULT cMenu::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	SAFE_ONMSGPROC(m_pDialog);
	return uMsg;
}


void cMenu::OnEvent(UINT id, int xPos, int yPos)
{
	for(int i=0;i<3;i++)
		if(m_start[i] == 1)
			return;
	switch(id)
	{
	case GAME_START:
		m_verMove = D3DXVECTOR3(-10,310,0);
		m_pSound->Play(L"sword_attack");

		m_pDialog->GetButton(GAME_START)->SetSprite(L"게임시작2",L"게임시작2",L"게임시작2",L"게임시작2");
		m_start[0] = 1;
		m_fmoveapl = 1;
		break;
	case GAME_HELP:
		m_verMove = D3DXVECTOR3(-10,460,0);
		m_pSound->Play(L"sword_attack");

		//m_pDialog->GetButton(GAME_HELP)->SetSprite(L"도움말2",L"도움말2",L"도움말2",L"도움말2");

		m_start[1] = 1;
		m_fmoveapl = 1;
		break;
	case EXIT:
		m_verMove = D3DXVECTOR3(-10,610,0);
		m_pSound->Play(L"sword_attack");

		m_pDialog->GetButton(EXIT)->SetSprite(L"나가기2",L"나가기2",L"나가기2",L"나가기2");
		
		m_start[2] = 1;
		m_fmoveapl = 1;
		break;
	}
}
