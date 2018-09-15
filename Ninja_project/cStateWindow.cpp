#include "cStateWindow.h"
#include "cGame.h"

cStateWindow::cStateWindow(KGAnimate* animate, KGDialog* dialog, KGFont* font, KGSprite* sprite)
{
	m_pDialog				= dialog;
	m_pFont					= font;
	for(int i = 0; i < 2; i++) {
		m_pGuide[i]			= new cGuide(animate, sprite);
		m_pGuide[i]->Init(i);
	}

	memset(&m_eventPlus, 0, sizeof(m_eventPlus));
	m_eventKill				= 0;
	m_skillPoint			= 0;
	m_lifeMax				= 0;
	m_dartbuy				= false;
	m_pSprite				= sprite;
}


cStateWindow::~cStateWindow()
{
	for(int i = 0; i < 2; i++)
		delete [] m_pGuide[i];
}


void cStateWindow::Reset(bool end)
{
	for(int i = 0; i < 2; i++)
		m_pGuide[i]->Init(i);
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	if(pGame->m_pHero->m_kind == 0) {
		int level = pGame->m_level;
		if(level >= 3)
			m_pDialog->GetButton(B_DART1)->SetDisable(false);
		if(level >= 5)
			m_pDialog->GetButton(B_DART2)->SetDisable(false);
		if(level >= 7)
			m_pDialog->GetButton(B_DART3)->SetDisable(false);
		if(level >= 9)
			m_pDialog->GetButton(B_DART4)->SetDisable(false);
	}
	if(end == true) {
		memset(&m_eventPlus, 0, sizeof(m_eventPlus));
		m_eventKill				= 0;
		m_skillPoint			= 0;
		m_dartbuy				= false;
		m_lifeMax				= 0;
		m_pDialog->GetButton(B_SKILL1)->SetDisable(false);
	}
	m_guideTouch				= false;
}


void cStateWindow::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	SAFE_ONFRAMEMOVE(m_pDialog);
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	for(int i = 0; i < 2; i++) 
		m_pGuide[i]->Update(fElapsedTime);

	for(int i = 0; i < m_pGuide[1]->m_dartAmount; i++) {
		if(m_pGuide[1]->m_ppDart[i]->m_state == S_MOVE) {
			if(m_pGuide[0]->m_state == S_MOVE) {
				if(m_pGuide[0]->Collision(m_pGuide[1]->m_ppDart[i]->m_position, m_pGuide[1]->m_ppDart[i]->m_radius)) {
					m_pGuide[0]->m_state = S_SUFFER;
					m_pGuide[1]->m_ppDart[i]->m_state = S_WAIT;
					pGame->m_pSound->Play(L"star_crash");
					m_eventKill++;
					if(m_eventKill >= 5) {
						pGame->ScoreAccumulate(1);
						m_eventKill = 0;
						m_eventPlus.score = 1;
						m_eventPlus.alpha = 1.0;
						m_eventPlus.show = true;
						m_eventPlus.timer = 0.0;
						if(pGame->m_pHero->m_kind == 0) {
							int level = pGame->m_level;
							if(level >= 3)
								m_pDialog->GetButton(B_DART1)->SetDisable(false);
							if(level >= 5)
								m_pDialog->GetButton(B_DART2)->SetDisable(false);
							if(level >= 7)
								m_pDialog->GetButton(B_DART3)->SetDisable(false);
							if(level >= 9)
								m_pDialog->GetButton(B_DART4)->SetDisable(false);
						}
					}
				}
			}
		}
	}
	if(m_eventPlus.show == true) {
		m_eventPlus.timer += fElapsedTime;
		if(m_eventPlus.timer > SCORETIMER) {
			m_eventPlus.alpha -= 0.05;
			if(m_eventPlus.alpha < 0.0)
				memset(&m_eventPlus, 0, sizeof(m_eventPlus));
		}
	}
}


void cStateWindow::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	m_pSprite->Render(L"shop",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
	TextDraw();
	SAFE_ONFRAMERENDER(m_pDialog);

	for(int i=B_DART1; i<=B_DART4;i++) {
		if(m_pDialog->GetButton(i)->GetDisable() == false)
		{
			if(m_pDialog->GetButton(B_DART1)->GetOvered())
			{
				m_pSprite->Render(L"tt1",D3DXVECTOR3(m_mouse.x-70,m_mouse.y-200,0),D3DXCOLOR(1,1,1,1));
			}
			else if(m_pDialog->GetButton(B_DART2)->GetOvered())
			{
				m_pSprite->Render(L"tt2",D3DXVECTOR3(m_mouse.x-70,m_mouse.y-200,0),D3DXCOLOR(1,1,1,1));
			}
			else if(m_pDialog->GetButton(B_DART3)->GetOvered())
			{
				m_pSprite->Render(L"tt3",D3DXVECTOR3(m_mouse.x-70,m_mouse.y-200,0),D3DXCOLOR(1,1,1,1));
			}
			else if(m_pDialog->GetButton(B_DART4)->GetOvered())
			{
				m_pSprite->Render(L"tt4",D3DXVECTOR3(m_mouse.x-70,m_mouse.y-200,0),D3DXCOLOR(1,1,1,1));
			}
		}
	}
	for(int i = 0; i < 2; i++)
		SAFE_ONFRAMERENDER(m_pGuide[i]);
}


void cStateWindow::Mouse(bool LButton, D3DXVECTOR3 point)
{
	if(LButton == true) {
		if(m_pGuide[1]->Collision(point, 0))
			m_guideTouch = true;
		else
			m_guideTouch = false;
	}
	if(m_guideTouch == true) {
		if(!m_pGuide[1]->Collision(point, 0)) {
			m_pGuide[1]->m_rotation = m_pGuide[1]->CalcAngle(point);
			m_pGuide[1]->m_attPoint = point;
		}
	}
}


void cStateWindow::TextDraw()
{
	cGame* pGame		= (cGame*)cMain()->GetCurrent();
	WCHAR wstr[20];
	if(m_eventPlus.show == true) {
		swprintf(wstr, L"+%d", m_eventPlus.score);
		m_pFont->DrawTextW(0, NULL, wstr, -1, KGRect(600, 240, 1024, 768), DT_NOCLIP, D3DXCOLOR(1, 1, 1, m_eventPlus.alpha));
	}
	memset(wstr,0,sizeof(wstr));
	swprintf(wstr,L"%s",pGame->m_name);
	m_pFont->DrawTextW(0,NULL,wstr,-1,KGRect(80,25,1024,768),DT_NOCLIP,D3DXCOLOR(1,1,1,1));
	memset(wstr, 0, sizeof(wstr));
	swprintf(wstr, L"%d", m_skillPoint);
	m_pFont->DrawTextW(0, NULL, wstr, -1, KGRect(400, 25, 1024, 768), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	memset(wstr,0,sizeof(wstr));
	swprintf(wstr,L"%d",pGame->m_level);
	m_pFont->DrawTextW(0, NULL , wstr, -1 , KGRect(290,25,1024,768),DT_NOCLIP,D3DXCOLOR(1,1,1,1));
	memset(wstr,0,sizeof(wstr));
	swprintf(wstr,L"%d",pGame->m_score);
	m_pFont->DrawTextW(0, NULL,wstr,-1 , KGRect(880,415,1024,768),DT_NOCLIP,D3DXCOLOR(1,1,1,1));
	memset(wstr, 0, sizeof(wstr));
	swprintf(wstr, L"%.2f", pGame->m_pHero->m_displacement);
	m_pFont->DrawTextW(0, NULL, wstr, -1, KGRect(185, 166, 300, 150), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	memset(wstr, 0, sizeof(wstr));
	swprintf(wstr, L"%.2f", pGame->m_pHero->m_saveDelay);
	m_pFont->DrawTextW(0, NULL, wstr, -1, KGRect(185, 237, 300, 200), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	memset(wstr, 0, sizeof(wstr));
	swprintf(wstr, L"%d", pGame->m_pHero->m_life);
	m_pFont->DrawTextW(0, NULL, wstr, -1, KGRect(202, 100, 300, 200), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
}


void cStateWindow::OnEvent(UINT id, int xPos, int yPos)
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	switch(id)
	{
	case B_SKILL2:
		if(m_skillPoint > 0) {
			pGame->m_pHero->m_displacement += 0.15;
			m_pGuide[0]->m_displacement = pGame->m_pHero->m_displacement;
			m_pGuide[0]->SetMoveData(m_pGuide[0]->m_movePoint);
			m_skillPoint--;
		}
		break;
	case B_SKILL3:
		if(m_skillPoint > 0) {
			if(pGame->m_pHero->m_saveDelay > 0.0) {
				pGame->m_pHero->m_saveDelay -= 0.05;
				m_pGuide[1]->m_saveDelay = pGame->m_pHero->m_saveDelay;
				m_skillPoint--;
			}
		}
		break;
	case B_SKILL1:
		if(m_skillPoint > 0) {
			pGame->m_pHero->m_life +=1;
			m_lifeMax++;
			if(m_lifeMax == 2)
				m_pDialog->GetButton(B_SKILL1)->SetDisable(true);
			m_skillPoint--;
		}
		break;
	case B_DART1: //3 包烹
		pGame->m_pHero->SetDartKind(D_PENETRATE);
		m_pDialog->GetButton(B_DART1)->SetSprite(L"t1-2",L"t1-2",L"t1-2",L"t1-2");

		for(int i=B_DART1;i<=B_DART4;i++)
			m_pDialog->GetButton(i)->SetDisable(true);
		m_pDialog->GetButton(B_DART1)->SetDisable(false);
		Reset(false);
		break;
	case B_DART2: //4 屁辫
		pGame->m_pHero->SetDartKind(D_BOUNCE);
		m_pDialog->GetButton(B_DART2)->SetSprite(L"t2-2",L"t2-2",L"t2-2",L"t2-2");

		for(int i=B_DART1;i<=B_DART4;i++)
			m_pDialog->GetButton(i)->SetDisable(true);
		m_pDialog->GetButton(B_DART2)->SetDisable(false);
		Reset(false);
		break;
	case B_DART3: //5 气藕
		pGame->m_pHero->SetDartKind(D_BOOM);
		m_pDialog->GetButton(B_DART3)->SetSprite(L"t3-2",L"t3-2",L"t3-2",L"t3-2");

		for(int i=B_DART1;i<=B_DART4;i++)
			m_pDialog->GetButton(i)->SetDisable(true);
		m_pDialog->GetButton(B_DART3)->SetDisable(false);
		Reset(false);
		break;
	case B_DART4: //6
		pGame->m_pHero->SetDartKind(D_HALF);
		m_pDialog->GetButton(B_DART4)->SetSprite(L"蔫加2",L"t蔫加2",L"蔫加2",L"蔫加2");

		for(int i=B_DART1;i<=B_DART4;i++)
			m_pDialog->GetButton(i)->SetDisable(true);
		m_pDialog->GetButton(B_DART4)->SetDisable(false);
		Reset(false);
		break;
	}
}


void cStateWindow::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	SAFE_ONMOUSE(m_pDialog);
	m_mouse.x = xPos;
	m_mouse.y = yPos;
}