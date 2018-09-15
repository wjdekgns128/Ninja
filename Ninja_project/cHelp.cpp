#include "cHelp.h"

cHelp::cHelp(KGAnimate* animate, KGSprite* sprite)
{
	m_pSprite				= sprite;
	sprite->Entry(L"../res/te/h.te");
	sprite->Entry(L"../res/te/help1.te");
	sprite->Entry(L"../res/te/help2.te");
	sprite->Entry(L"../res/te/help3.te");
	animate->Entry(L"../res/ta/h.Ta");
	for(int i = 0; i < 4; i++)
		m_pSingle[i]		= new KGRenderSingle(animate);
	m_pSingle[0]->Entry(L"h_move", D3DXVECTOR3(240,450,0));
	m_pSingle[1]->Entry(L"h_sword", D3DXVECTOR3(560,470,0));
	m_pSingle[2]->Entry(L"h_throwing", D3DXVECTOR3(890,470,0));
	m_pSingle[3]->Entry(L"h_defence", D3DXVECTOR3(245,450,0));

	m_curPage			= false;
	m_timer				= 0.0;
}


cHelp::~cHelp()
{
	for(int i = 0; i < 4; i++)
		delete m_pSingle[i];
}


void cHelp::Reset()
{
	m_curPage			= false;
	m_timer				= 0.0;
	m_click[0] = m_click[1] = m_click[2] = 0;
}


void cHelp::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	static float angle	= 0;
	m_timer				+= fElapsedTime;
	if(m_timer > 1.0) {
		angle			= ((int)angle+30) % 360;
		for(int i = 0; i < 4; i++) {
			m_pSingle[i]->SetAngle(D3DXToRadian(angle));
		}
		m_timer			= 0.0;
	}
}


void cHelp::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(m_curPage == false)
		m_pSprite->Render(L"도움말11",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
	else
		m_pSprite->Render(L"도움말22",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));

	if(m_click[0] == 0)
		m_pSprite->Render(L"이전1",KGRect(624, 668, 824, 768),D3DXCOLOR(1,1,1,1));
	else
		m_pSprite->Render(L"이전2",KGRect(624, 668, 824, 768),D3DXCOLOR(1,1,1,1));
	if(m_click[1] == 0)
		m_pSprite->Render(L"다음1",KGRect(824, 668, 1024, 768),D3DXCOLOR(1,1,1,1));
	else
		m_pSprite->Render(L"다음2",KGRect(824, 668, 1024, 768),D3DXCOLOR(1,1,1,1));
	if(m_click[2] == 0)
		m_pSprite->Render(L"메인1",KGRect(0, 668, 200, 768),D3DXCOLOR(1,1,1,1));
	else
		m_pSprite->Render(L"메인2",KGRect(0, 668, 200, 768),D3DXCOLOR(1,1,1,1));

	if(m_curPage == false) {
		for(int i = 0; i < 3; i++)
			SAFE_ONFRAMERENDER(m_pSingle[i]);
	}
	else
		SAFE_ONFRAMERENDER(m_pSingle[3]);
}


bool cHelp::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	if(bButtonDown) {
		if(bLeftButtonDown) {
			if(xPos > 624 && xPos < 824 && yPos > 668 && yPos < 768)
				m_click[0] = 1;
			else if(xPos > 824 && xPos < 1024 && yPos > 668 && yPos < 768)
				m_click[1] = 1;
			else if(xPos > 0 && xPos < 200 && yPos > 668 && yPos < 768)
				m_click[2] = 1;
		}
	}
	else {
		if(m_click[0] == 1) {
			if(xPos > 624 && xPos < 824 && yPos > 668 && yPos < 768)
				if(m_curPage == true)
					m_curPage = false;
		}
		else if(m_click[1] == 1) {
			if(xPos > 824 && xPos < 1024 && yPos > 668 && yPos < 768)
				if(m_curPage == false)
					m_curPage = true;
		}
		else if(m_click[2] == 1) {
			if(xPos > 0 && xPos < 200 && yPos > 668 && yPos < 768)
				return true;
		}
		m_click[0] = m_click[1] = m_click[2] = 0;
	}
	return false;
}