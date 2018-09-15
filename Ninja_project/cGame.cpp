#include "cGame.h"
#include "cLink.h"
#include "time.h"
#include <locale.h>					//wprintf 쓸때 호출해줘야 함.
// 맨 위에 그림 , 스테이지 넘어가거나 리셋 될떄 그림 안사라짐;
cGame::cGame()
{
	SRANDOM;

	setlocale(LC_ALL, "korean");	//wprintf 쓸때 호출해줘야 함.
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
	m_pSingle				= NULL;
	m_pFont					= NULL;
	m_pDialog				= NULL;
	m_pDialog2				= NULL;
	m_pName					= NULL;
	m_pCursor				= NULL;
	m_pSound				= NULL;
	m_pStopmenu				= NULL;
	m_pHelp					= NULL;

	m_pHero					= NULL;
	for(int i = 0; i < ENEMY_AMOUNT; i++)
		m_pEnemy[i]			= NULL;
	m_pStateWindow			= NULL;

	m_stop					= true;
	m_nameWrite				= true;

	m_timer					= 0.0;
	m_max					= 0.5;
	m_accelerate			= 0.0;
	m_accelTimer			= 0.0;
	m_etime					= 0.0;
	m_UITimer				= 0.1;
	m_UIAlpha[0] = m_UIAlpha[1] = 1.0;
	m_maxEnemy				= 15;
	m_score					= 0;
	m_bestScore				= 0;
	m_bestLevel				= 0;
	memset(m_name, 0, sizeof(m_name));
	memset(m_bestName, 0, sizeof(m_bestName));
	m_curExp				= 0;
	m_expMax				= 7;

	m_showLvUp				= false;
	m_showHelp				= false;
	m_showStateWindow		= false;
	m_level					= 1;
	m_guideTouch			= false;
	m_gamestop				= false;

	m_enterTimer			= 0.0;
	m_enterAlpha			= 0.0;
	m_enterCheck			= true;

	m_hexp					= 0;
	m_fapl					= 0.0;
	m_gameapl				= 1.0;
	m_gamecheck				= 0;

	memset(m_scorePlus, 0, sizeof(m_scorePlus));

	if(m_pDialog) {
		for(int i=B_RETUNR; i<= B_MENU;i++)
			m_pStopmenu->GetButton(i)->SetDisable(!m_gamestop);
	}
	if(m_pSound) {
		m_pSound->Play(L"bgm", true, 0, DSBPLAY_LOOPING);
	}

	FILE* pfile = _wfopen(L"score.ssk", L"rt");
	if(pfile) {
		fwscanf(pfile, L"%d %d %s", &m_bestScore, &m_bestLevel, m_bestName);
		fclose(pfile);
	}
	else {
		FILE* cfile = _wfopen(L"score.ssk", L"wt");
		fwprintf(cfile, L"0");
		fclose(cfile);
	}
}


cGame::~cGame()
{
	SAFE_DELETE(m_pSprite);	//!< 동적 할당한 변수를 delete시켜주는 메크로
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pName);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pSound);
	SAFE_DELETE(m_pHelp);

	SAFE_DELETE(m_pHero);
	for(int i = 0; i < ENEMY_AMOUNT; i++)
		SAFE_DELETE(m_pEnemy[i]);
	SAFE_DELETE(m_pStateWindow);
	cLink* pLink = cLink::GetInstance();
	delete pLink;
}


HRESULT cGame::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"../res/te/dart.Te");
		m_pSprite->Entry(L"../res/te/map.Te");
		m_pSprite->Entry(L"../res/te/gameover.te");
		m_pSprite->Entry(L"../res/te/BT.te");
		m_pSprite->Entry(L"../res/te/h.te");
		m_pSprite->Entry(L"../res/te/j.te");
		m_pSprite->Entry(L"../res/te/bg.te");
		m_pSprite->Entry(L"../res/te/cursor.te");
		m_pSprite->Entry(L"../res/te/enter.te");
		m_pSprite->Entry(L"../res/te/object.te");
		m_pSprite->Entry(L"../res/te/point1.te");
		m_pSprite->Entry(L"../res/te/RankInterface.Te");
		m_pSprite->Entry(L"../res/te/Dialog_number.Te");
		m_pSprite->Entry(L"../res/te/number.Te");
		m_pSprite->Entry(L"../res/te/best.Te");
		m_pSprite->Entry(L"../res/te/gameUI.Te");
		m_pSprite->Entry(L"../res/te/boom.Te");
		m_pSprite->Entry(L"../res/te/shop.Te");
		m_pSprite->Entry(L"../res/te/shop_m.Te");
		m_pSprite->Entry(L"../res/te/shop_m2.Te");
		m_pSprite->Entry(L"../res/te/pung.Te");
		m_pSprite->Entry(L"../res/te/stop.Te");
	}

	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"../res/ta/h.Ta");
		m_pAnimate->Entry(L"../res/ta/j.Ta");
		m_pAnimate->Entry(L"../res/ta/point1.ta");
		m_pAnimate->Entry(L"../res/ta/boom.ta");
		m_pAnimate->Entry(L"../res/ta/pung.ta");
	}

	if(m_pSingle == NULL)
	{
		m_pSingle			= new KGRenderSingle(m_pAnimate);
	}

	if (m_pCursor == NULL)
	{
		m_pCursor = new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768), L"cur", L"cur");
	}

	if(m_pFont == NULL)
	{
		m_pFont				= new KGFont(pd3dDevice);
		m_pFont->Entry(0, L"궁서", 30, 10);
		m_pFont->Entry(1, L"궁서", 25, 10);
		m_pFont->Entry(2, L"궁서", 40, 15);
	}
	if(m_pDialog == NULL)
	{
		m_pDialog = new KGDialog(m_pSprite);
		m_pDialog->AddNumber(0, L"num_", D3DXVECTOR3(200, 10, 0), -8 );
		m_pDialog->GetNumber(0)->SetNumber(m_score);
		m_pDialog->AddNumber(1, L"num_", D3DXVECTOR3(780, 10, 0), -8 );
		m_pDialog->GetNumber(1)->SetNumber(m_bestScore);
		m_pDialog->AddButton(99,L"빛빛",L"빛빛",L"빛빛",L"빛빛",D3DXVECTOR3(5,12,0),true);
		m_pDialog->GetButton(99)->SetShow(false);
		m_pDialog->AddNumber(101,L"Dnum_",D3DXVECTOR3(470,10,0),-25); // 걍 숫자는 num
	}

	if(m_pDialog2 == NULL)
	{
		m_pDialog2 = new KGDialog(m_pSprite, NULL, this);
		m_pDialog2->AddButton(B_SKILL1, L"up1", L"up3", L"up2", L"up2", D3DXVECTOR3(280,81,0), true);
		m_pDialog2->AddButton(B_SKILL2, L"up1", L"up3", L"up2", L"up2", D3DXVECTOR3(280,153,0), true);
		m_pDialog2->AddButton(B_SKILL3, L"up1", L"up3", L"up2", L"up2", D3DXVECTOR3(280,224,0), true);

		m_pDialog2->AddButton(B_DART1, L"t1", L"t1-2" ,L"t1-2", L"t1", D3DXVECTOR3(25,470,0), true);
		m_pDialog2->AddButton(B_DART2, L"t2", L"t2-2", L"t2-2", L"t2", D3DXVECTOR3(275,470,0), true);
		m_pDialog2->AddButton(B_DART3, L"t3", L"t3-2", L"t3-2", L"t3", D3DXVECTOR3(525,470,0), true);
		m_pDialog2->AddButton(B_DART4, L"쾌속1", L"쾌속2", L"쾌속2", L"쾌속1", D3DXVECTOR3(777,470,0), true);

		m_pDialog2->GetButton(B_DART1)->SetDisable(true);
		m_pDialog2->GetButton(B_DART2)->SetDisable(true);
		m_pDialog2->GetButton(B_DART3)->SetDisable(true);
		m_pDialog2->GetButton(B_DART4)->SetDisable(true);
	}

	if(m_pStopmenu == NULL)
	{
		m_pStopmenu = new KGDialog(m_pSprite ,NULL, this);
		m_pStopmenu->AddButton(B_RETUNR,L"계속1",L"계속2",L"계속2",L"계속2",D3DXVECTOR3(516,333,0),true);
		m_pStopmenu->AddButton(B_HELP,L"도움1",L"도움2",L"도움2",L"도움2",D3DXVECTOR3(516,414,0),true);
		m_pStopmenu->AddButton(B_MENU,L"메인1",L"메인2",L"메인2",L"메인2",D3DXVECTOR3(516,498,0),true);
		for(int i=B_RETUNR; i<= B_MENU;i++)
			m_pStopmenu->GetButton(i)->SetDisable(true);
	}

	if(m_pName	== NULL)
	{
		m_pName			= new KGDialog(m_pSprite);
		m_pName->AddEditBox(100, m_pFont->Get(2), KGRect(520, 365, 702, 702), D3DXCOLOR(1, 1, 1, 1), DT_NOCLIP);
		m_pName->AddListBox(101,m_pFont->Get(2), KGRect(350, 0, 1024, 768));
		m_pName->GetEditBox(100)->SetDisable(true);
		m_pName->GetListBox(101)->SetDisable(true);
	}

	if(m_pSound == NULL) {
		m_pSound = new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"defense", L"../res/sound/effect/defense.wav");
		m_pSound->Entry(L"sword_attack", L"../res/sound/effect/sword_attack.wav");
		m_pSound->Entry(L"star_crash", L"../res/sound/effect/star_crash.wav");
		m_pSound->Entry(L"star_attack", L"../res/sound/effect/star_attack.wav");
		m_pSound->Entry(L"pung", L"../res/sound/effect/pung.wav");
		m_pSound->Entry(L"bgm", L"../res/sound/bgm/battle.wav");
		m_pSound->Play(L"bgm", true, 0, DSBPLAY_LOOPING);
	}

	if(m_pHero == NULL) {
		m_pHero				= new cHero(m_pAnimate, m_pSprite);
	}

	for(int i = 0; i < ENEMY_AMOUNT; i++) {
		if(m_pEnemy[i] == NULL) {
			m_pEnemy[i]		= new cEnemy(m_pAnimate, m_pSprite);
		}
	}

	if(m_pStateWindow == NULL) {
		m_pStateWindow		= new cStateWindow(m_pAnimate, m_pDialog2, m_pFont, m_pSprite);
	}

	if(m_pHelp == NULL)
	{
		m_pHelp			= new cHelp(m_pAnimate, m_pSprite);
	}
	
	return S_OK;
}


HRESULT cGame::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pFont);
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pDialog2);
	SAFE_ONRESETDEVICE(m_pName);
	SAFE_ONRESETDEVICE(m_pStopmenu);
	return S_OK;
}


void cGame::OnLostDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pName);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pSound);
	SAFE_DELETE(m_pStopmenu);
	SAFE_DELETE(m_pHelp);
	SAFE_DELETE(m_pHero);
	for(int i = 0; i < ENEMY_AMOUNT; i++)
		SAFE_DELETE(m_pEnemy[i]);
	SAFE_DELETE(m_pStateWindow);
}


void cGame::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pName);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pSound);
	SAFE_DELETE(m_pStopmenu);
	SAFE_DELETE(m_pHelp);
	SAFE_DELETE(m_pHero);
	for(int i = 0; i < ENEMY_AMOUNT; i++)
		SAFE_DELETE(m_pEnemy[i]);
	SAFE_DELETE(m_pStateWindow);
}


void cGame::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	if(m_stop) {
		if(m_showStateWindow) {
			SAFE_ONFRAMEMOVE(m_pStateWindow);
		}
		else if(m_nameWrite) {
			SAFE_ONFRAMEMOVE(m_pName);
		}
		else if(m_showHelp) {
			SAFE_ONFRAMEMOVE(m_pHelp);
		}
		return;
	}

	SAFE_ONFRAMEMOVE(m_pDialog);

	if(m_pHero->m_state == S_DIE) {
		ShowEnter(fElapsedTime);
		return;
	}

	if(m_hexp == 0)
	{
		if(m_fapl	<  (m_curExp / (float)m_expMax))
			m_fapl  += 0.03;
	}
	if(m_hexp == 1)
	{
		m_fapl -= 0.04;
		if(m_fapl <= 0)
		{
			m_hexp = 0;
			m_fapl	= 0;
		}
	}

	m_timer += fElapsedTime;
	m_etime += fElapsedTime;
	GameNM(m_etime);
	m_pDialog->GetNumber(101)->SetNumber(m_etime);
	m_pHero->Update(fElapsedTime);
	EnemyUpdate(fElapsedTime);
	Collsion();

	cLink* pLink = cLink::GetInstance();
	pLink->Update(fElapsedTime);

	if(m_accelTimer > 0.0) {
		m_accelTimer -= fElapsedTime;
		if(m_accelTimer < 0.0)
			m_accelTimer = 0.0;
	}

	for(int i = 0; i < 8; i++) {
		if(m_scorePlus[i].show == true) {
			m_scorePlus[i].timer += fElapsedTime;
			if(m_scorePlus[i].timer > SCORETIMER) {
				m_scorePlus[i].alpha -= 0.05;
				if(m_scorePlus[i].alpha < 0.0)
					memset(m_scorePlus, 0, sizeof(m_scorePlus));
			}
		}
	}

	if(m_UITimer != 0.0) {
		if(m_UITimer > 2.0f) {
			for(int i = 0; i < 2; i++)
				m_UIAlpha[i] -= 0.01;
			if(m_UIAlpha[0] < 0.6)
				m_UIAlpha[0] = 0.6;
			if(m_UIAlpha[1] < 0.0) {
				m_UIAlpha[1] = 0.0;
				m_UITimer	= 0.0;
			}
		}
		else
			m_UITimer += fElapsedTime;
	}
}


void cGame::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		if(m_stop) {
			if(m_showStateWindow) {
				SAFE_ONFRAMERENDER(m_pStateWindow);
			}
			else if(m_showHelp)
			{
				SAFE_ONFRAMERENDER(m_pHelp);
			}
			else if(m_gamestop)
			{
				m_pSprite->Render(L"맵 1", KGRect(0,0,1024,768), D3DXCOLOR(m_gameapl,m_gameapl,m_gameapl,m_gameapl));
				cLink* pLink = cLink::GetInstance();
				SAFE_ONFRAMERENDER(pLink);
				for(int i = 0; i < m_maxEnemy; i++)
					SAFE_ONFRAMERENDER(m_pEnemy[i]);
				SAFE_ONFRAMERENDER(m_pHero);
				UIDraw();
				SAFE_ONFRAMERENDER(m_pSingle);
				TextDraw();
				m_pSprite->Render(L"일시정지",D3DXVECTOR3(512,384,0),D3DXCOLOR(1,1,1,1));
				SAFE_ONFRAMERENDER(m_pStopmenu);
			}
			else if(m_nameWrite)
			{
				m_pSprite->Render(L"맵 1", KGRect(0,0,1024,768), D3DXCOLOR(m_gameapl,m_gameapl,m_gameapl,m_gameapl));
				m_pSprite->Render(L"이름", D3DXVECTOR3(340,300,0),D3DXCOLOR(1,1,1,1));
				m_pName->GetEditBox(100)->SetDisable(false);
				m_pName->GetListBox(101)->SetDisable(false);

				SAFE_ONFRAMERENDER(m_pName);
				m_string = m_pName->GetEditBox(100)->GetText();
			}
		}
		else {
			m_pSprite->Render(L"맵 1", KGRect(0,0,1024,768), D3DXCOLOR(m_gameapl,m_gameapl,m_gameapl,m_gameapl));

			cLink* pLink = cLink::GetInstance();
			SAFE_ONFRAMERENDER(pLink);
			for(int i = 0; i < m_maxEnemy; i++)
				SAFE_ONFRAMERENDER(m_pEnemy[i]);
			SAFE_ONFRAMERENDER(m_pHero);



			UIDraw();

			SAFE_ONFRAMERENDER(m_pSingle);

			TextDraw();

			SAFE_ONFRAMERENDER(m_pDialog);
			if(m_pHero->m_state == S_DIE)
				m_pSprite->Render(L"푸쉬", KGRect(0, 50, 80, 90), D3DXCOLOR(1,1,1,1));
		}
		m_pSprite->Render(L"black", D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,m_stateAlpha));
		SAFE_ONFRAMERENDER(m_pCursor);
		V(pd3dDevice->EndScene());
	}
}


void cGame::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	SAFE_ONKEYBOARD(m_pName);

	if(bKeyDown) {
		m_pHero->Key(nChar);

		switch(nChar) {
			case VK_Q:
				ExpManage(1000);
				break;
			case 188:
				if(m_accelerate > -3.0)
					m_accelerate -= 0.2;
				m_accelTimer = 1.0;
				break;
			case 190:
				if(m_accelerate < -0.2)
					m_accelerate += 0.2;
				m_accelTimer = 1.0;
				break;
			case VK_F1:
				if(m_showHelp == false)
					if(m_showStateWindow == true || m_gamestop == true)
						break;
				
				m_pHelp->Reset();
				m_showHelp = !m_showHelp;
				if(m_gamestop == false)
					m_stop = m_showHelp;
				else {
					for(int i=B_RETUNR; i<= B_MENU;i++)
						m_pStopmenu->GetButton(i)->SetDisable(!m_gamestop);
				}
				break;
			case VK_F2:
				if(m_showStateWindow == false)
					if(m_showHelp == true || m_gamestop == true)
						break;

				if(m_pHero->m_life <= 0)
					break;
				if(m_showStateWindow == false) {
					if(m_nameWrite)
						break;
					m_showStateWindow = true;
					m_pStateWindow->Reset(false);
					m_stop = true;
				}
				else {
					m_showHelp = false;
					m_showStateWindow = false;
					m_stop = false;
				}
				break;
			case VK_ESCAPE:
				if(m_nameWrite == false && m_showHelp == false && m_showStateWindow == false)
				{
					m_gamestop = !m_gamestop;
					m_stop	   = m_gamestop;
					for(int i=B_RETUNR; i<= B_MENU;i++)
						m_pStopmenu->GetButton(i)->SetDisable(!m_gamestop);
				}
				else if(m_gamestop == true && m_stop == true) {
					m_showHelp = false;
					m_showStateWindow = false;
					for(int i=B_RETUNR; i<= B_MENU;i++)
						m_pStopmenu->GetButton(i)->SetDisable(!m_gamestop);
				}
				else if(m_stop == true) {
					m_showHelp = false;
					m_showStateWindow = false;
					m_gamestop = false;
					m_stop = false;
					
				}
				break;
			case VK_RETURN:
				if(m_nameWrite == true)
				{
					m_nameWrite = false;
					m_stop		= false;
					m_pName->GetEditBox(100)->SetDisable(true);
					m_pName->GetListBox(101)->SetDisable(true);
					if(m_pName->GetEditBox(100)->empty() != true)
					{
						if(m_string.size() > 3)
							m_string[3] = L'\0';
					memcpy(m_name, m_string.c_str(), sizeof(m_name));
					}
					else if(m_pName->GetEditBox(100)->empty() == true)
						memcpy(m_name, L"임시명", sizeof(L"임시명"));
				}
				else {
					if(m_pHero->m_state != S_DIE)
						break;
					m_pHero->ReSet();
					for(int i = 0; i < ENEMY_AMOUNT; i++)
						m_pEnemy[i]->Reset();

					m_enterTimer			= 0.0;
					m_enterAlpha			= 0.0;
					m_enterCheck			= true;
					m_timer					= 0.0;
					m_max					= 0.5;
					m_score					= 0;
					m_level					= 1;
					m_showLvUp				= false;
					m_curExp				= 0;
					m_expMax				= 7;
					m_fapl					= 0.0;
					m_etime					= 0;
					m_gameapl				= 1.0;
					m_gamecheck				= 0;

					memset(m_scorePlus, 0, sizeof(m_scorePlus));
					m_pDialog->GetNumber(0)->SetNumber(m_score);
					m_pDialog->GetNumber(1)->SetNumber(m_bestScore);
					m_pStateWindow->Reset(true);
					m_pDialog->GetButton(99)->SetShow(false);
					m_pDialog2->GetButton(B_DART1)->SetSprite(L"t1",L"t1-2",L"t1-2",L"t1");
					m_pDialog2->GetButton(B_DART2)->SetSprite(L"t2",L"t2-2",L"t2-2",L"t2");
					m_pDialog2->GetButton(B_DART3)->SetSprite(L"t3",L"t3-2",L"t3-2",L"t3");
					m_pDialog2->GetButton(B_DART4)->SetSprite(L"쾌속1",L"쾌속2",L"쾌속2",L"쾌속1");
					for(int i=B_DART1;i<=B_DART4;i++)
					{
						m_pDialog2->GetButton(i)->SetDisable(true);
					}
					cLink* pLink = cLink::GetInstance();
					pLink->end();
				}
				break;
		}
	}
}


void cGame::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	SAFE_ONMOUSE(m_pCursor);
	SAFE_ONMOUSE(m_pDialog);
	SAFE_ONMOUSE(m_pStopmenu);

	if(m_stop) {
		if(m_showStateWindow == true) {
			SAFE_ONMOUSE(m_pStateWindow);
			m_pStateWindow->Mouse(bLeftButtonDown, D3DXVECTOR3(xPos, yPos, 0));
		}
		else if(m_showHelp == true) {
			if(m_pHelp->OnMouse(bButtonDown, bLeftButtonDown, bRightButtonDown, bMiddleButtonDown, bSideButton1Down, bSideButton2Down, nMouseWheelDelta, xPos, yPos,pUserContext)) {
				m_showHelp = false;
				if(m_gamestop == false)
					m_stop = false;
				else {
					for(int i=B_RETUNR; i<= B_MENU;i++)
						m_pStopmenu->GetButton(i)->SetDisable(!m_gamestop);
				}
			}
		}
		return;
	}

	if(bButtonDown)
	{
		if(m_pHero->m_state == S_DIE) {
			if(m_pDialog->GetButton(99)->GetOvered() == true) {
				m_nameWrite	= !m_nameWrite;
				m_stop		= m_nameWrite;
			}
		}
		m_pHero->Mouse(bRightButtonDown, D3DXVECTOR3(xPos, yPos, 0));
		if(!bLeftButtonDown)
			if(bRightButtonDown)
				m_pSingle->Entry(L"point", D3DXVECTOR3(xPos, yPos, 0), true, 1);
	}
}


LRESULT cGame::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	SAFE_ONMSGPROC(m_pDialog);
	SAFE_ONMSGPROC(m_pStopmenu);
	if(m_stop) {
		if(m_showStateWindow)
			SAFE_ONMSGPROC(m_pDialog2);
		if(m_nameWrite)
			SAFE_ONMSGPROC(m_pName);
	}
	return uMsg;
}

void cGame::EnemyUpdate(float fElapsedTime)
{
	
	int count = 0;
	if(m_timer > 5.0 + m_max/5 + m_accelerate) {
		for(int i = 0; i < m_maxEnemy; i++) {
			if(count > m_max)
				break;
			if(m_pEnemy[i]->m_state == S_DIE) {
				if(m_pEnemy[i]->Create())
					count++;
			}
		}
		m_timer = 0.0;
		m_max += 0.3;
		m_maxEnemy += 0.1;
	}

	int temp = 0;
	for(int i = 0; i < m_maxEnemy; i++) {
		m_pEnemy[i]->Update(fElapsedTime);
		if(m_pEnemy[i]->m_state == S_SUFFER && m_pEnemy[i]->m_die == true) {
			temp++;
			m_pEnemy[i]->m_die = false;
		}
	}
	ScoreAccumulate(temp);
	m_pDialog->GetNumber(0)->SetNumber(m_score);
}

void cGame::Collsion()
{
	for(int k = 0; k < m_maxEnemy; k++) {
		for(int j = 0; j < m_pEnemy[k]->m_dartAmount; j++) {
			if(m_pEnemy[k]->m_ppDart[j]->m_state == S_MOVE) {
				if(m_pHero->m_state == S_SUFFER || m_pHero->m_state == S_DIE || m_pEnemy[k]->m_ppDart[j]->m_saveObject == m_pHero || m_pHero->m_hide == true)
					continue;
				if(m_pHero->Collision(m_pEnemy[k]->m_ppDart[j]->m_position, m_pEnemy[k]->m_ppDart[j]->m_radius)) {
					m_pHero->Suffer();
					m_pEnemy[k]->m_ppDart[j]->m_saveObject = m_pHero;
				}
			}
		}
		if(m_pEnemy[k]->m_state == S_DIE || m_pEnemy[k]->m_state == S_SUFFER)
			continue;
		for(int j = 0; j < m_pHero->m_dartAmount; j++) {
			if(m_pHero->m_ppDart[j]->m_state == S_MOVE && m_pHero->m_ppDart[j]->m_saveObject != m_pEnemy[k]) {
				if(m_pEnemy[k]->Collision(m_pHero->m_ppDart[j]->m_position, m_pHero->m_ppDart[j]->m_radius)) {
					m_pEnemy[k]->Suffer();
					m_pHero->m_ppDart[j]->Bounce(k);
					m_pHero->m_ppDart[j]->m_saveObject = m_pEnemy[k];
					break;
				}
			}
		}
	}
}

void cGame::ExpManage(int exp)
{
	m_curExp				+= exp;
	if(m_curExp >= m_expMax) {
		m_level++;
		m_pStateWindow->m_skillPoint++;
		m_curExp			= m_curExp % m_expMax;
		m_expMax			= m_expMax + m_expMax * 0.2;
		m_hexp				= 1;

		m_pHero->LevelUp();
	}
}

void cGame::SaveScore(int score)
{
	if(score > m_bestScore) {
		m_bestScore	= score;
		m_bestLevel = m_level;
		memcpy(m_bestName, m_name, sizeof(m_name));
	}
	WCHAR saveName[5][10] = {0,};
	int saveScore[5] = {0,};
	int saveLevel[5] = {0,};
	int count = 0;

	FILE* pfile = _wfopen(L"score.ssk", L"rt");
	for(int i = 0; i < 5; i++)
		fwscanf(pfile, L"%d %d %s", &saveScore[i], &saveLevel[i], saveName[i]);
	fclose(pfile);

	FILE* wfile		= _wfopen(L"score.ssk", L"wt");
	for(int i = 0; i < 5; i++) {
		if(score > saveScore[i]) {
			fwprintf(wfile, L"%d %d %s", score, m_level, m_name);
			fwprintf(wfile, L"\n");
			break;
		}
		else {
			fwprintf(wfile, L"%d %d %s", saveScore[i], saveLevel[i], saveName[i]);
			fwprintf(wfile, L"\n");
			count++;
		}
	}
	for(int i = count; i < 4; i++) {
		fwprintf(wfile, L"%d %d %s", saveScore[i], saveLevel[i], saveName[i]);
		fwprintf(wfile, L"\n");
	}
	fclose(wfile);
	m_pDialog->GetNumber(1)->SetNumber(m_bestScore);
}


void cGame::ScoreAccumulate(int score)
{
	if(score == 0)
		return;

	for(int i = 0; i < 8; i++) {
		if(m_scorePlus[i].show == false) {
			m_scorePlus[i].timer = 0.0;
			m_scorePlus[i].alpha = 1.0;
			m_scorePlus[i].score = score;
			m_scorePlus[i].show = true;
			m_score += score;
			ExpManage(score);
			if(i == 2 || i == 6) {
				int temp = 0;
				for(int l = 0; l < i+1; l++) {
					temp += m_scorePlus[l].score;
					m_scorePlus[l].alpha = 1.0;
					m_scorePlus[l].timer = 0.0;
				}
				m_scorePlus[i+1].score = temp / 3;
				m_score += m_scorePlus[i+1].score;
				ExpManage(m_scorePlus[i+1].score);
				m_scorePlus[i+1].timer = 0.0;
				m_scorePlus[i+1].alpha = 1.0;
				m_scorePlus[i+1].show = true;
				if(i == 6)
					m_scorePlus[i+1].timer = 1.5;
			}
			return;
		}
	}
	memset(m_scorePlus, 0, sizeof(m_scorePlus));
	ScoreAccumulate(score);
}


void cGame::ShowEnter(float fElapsedTime)
{
	if(m_enterTimer == 0.0) {
		if(m_enterCheck == true) {
			if(m_enterAlpha < 1.0)
				m_enterAlpha += 0.01;
			else {
				m_enterTimer = 1.5;
				m_enterCheck = !m_enterCheck;
			}
		}
		else {
			if(m_enterAlpha > 0.0)
				m_enterAlpha -= 0.025;
			else {
				m_enterTimer = 0.6;
				m_enterCheck = !m_enterCheck;
			}
		}
	}
	else {
		m_enterTimer -= fElapsedTime;
		if(m_enterTimer < 0.0)
			m_enterTimer = 0.0;
	}
}


void cGame::UIDraw()
{
	if(m_pHero->m_state == S_DIE) {
		m_pSprite->Render(L"게임오버", KGRect(280, 200, 780, 300), D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"enter", KGRect(280, 400, 780, 500), D3DXCOLOR(1,1,1,m_enterAlpha));
	}

	if(m_pHero->m_keyState == false) {
		m_pSprite->Render(L"단도아이콘2", KGRect(0,650,130,780), D3DXCOLOR(1,1,1,m_UIAlpha[1]));
		m_pSprite->Render(L"검아이콘1", KGRect(30,610,160,740), D3DXCOLOR(1,1,1,m_UIAlpha[0]));
	}
	else {
		m_pSprite->Render(L"검아이콘2", KGRect(0,650,130,780), D3DXCOLOR(1,1,1,m_UIAlpha[1]));
		m_pSprite->Render(L"단도아이콘1", KGRect(30,610,160,740), D3DXCOLOR(1,1,1,m_UIAlpha[0]));
	}
	switch(m_pHero->m_inven[1]) {
		case I_NOITEM:
			m_pSprite->Render(L"비었다2", KGRect(115,650,245,780), D3DXCOLOR(1,1,1,m_UIAlpha[1]));
			break;
		case I_HIDE:
			m_pSprite->Render(L"은신2", KGRect(115,650,245,780), D3DXCOLOR(1,1,1,m_UIAlpha[1]));
			break;
		case I_THREEDART:
			m_pSprite->Render(L"three2", KGRect(115,650,245,780), D3DXCOLOR(1,1,1,m_UIAlpha[1]));
			break;
		case I_SUM:
			m_pSprite->Render(L"섬2", KGRect(115,650,245,780), D3DXCOLOR(1,1,1,m_UIAlpha[1]));
			break;
	}
	switch(m_pHero->m_inven[0]) {
		case I_NOITEM:
			m_pSprite->Render(L"비었다", KGRect(145,610,275,740), D3DXCOLOR(1,1,1,m_UIAlpha[0]));
			break;
		case I_HIDE:
			m_pSprite->Render(L"은신1", KGRect(145,610,275,740), D3DXCOLOR(1,1,1,m_UIAlpha[0]));
			break;
		case I_THREEDART:
			m_pSprite->Render(L"three1", KGRect(145,610,275,740), D3DXCOLOR(1,1,1,m_UIAlpha[0]));
			break;
		case I_SUM:
			m_pSprite->Render(L"섬1", KGRect(145,610,275,740), D3DXCOLOR(1,1,1,m_UIAlpha[0]));
			break;
	}

	m_pSprite->Render(L"판때기", KGRect(0,0,1024,80), D3DXCOLOR(1,1,1,1));
	m_pSprite->Render(L"칼1", KGRect(0,-10,400,100), D3DXCOLOR(1,1,1,1));
	m_pSprite->Render(L"칼2", KGRect(620,-10,1024,100), D3DXCOLOR(1,1,1,1));
	m_pSprite->Render(L"칼s2",KGRect(70,-10,405,85),D3DXCOLOR(1,1,1,m_fapl));
}


void cGame::TextDraw()
{
	WCHAR wstr[20];
	for(int i = 0; i < 8; i++) {
		if(m_scorePlus[i].show == true) {
			swprintf(wstr, L"+%d", m_scorePlus[i].score);
			if(i == 3 || i == 7)
				m_pFont->DrawTextW(1, NULL, wstr, -1, KGRect(95+i*30, 45, 1024, 768), DT_NOCLIP, D3DXCOLOR(0, 1, 0, m_scorePlus[i].alpha));
			else
				m_pFont->DrawTextW(1, NULL, wstr, -1, KGRect(95+i*30, 45, 1024, 768), DT_NOCLIP, D3DXCOLOR(1, 1, 1, m_scorePlus[i].alpha));
		}
	}

	m_pFont->DrawTextW(0, NULL, L"도움말 F1", -1, KGRect(900, 730, 1024, 768), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	WCHAR str[15];
	m_pFont->DrawTextW(1, NULL, m_name, -1, KGRect(13, 25, 100, 40), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	m_pFont->DrawTextW(1, NULL, m_bestName, -1, KGRect(940, 27, 1024, 40), DT_NOCLIP, D3DXCOLOR(1, 0.2f, 0, 1));
	memset(wstr, 0, sizeof(wstr));
	swprintf(str, L"Lv %d", m_bestLevel);
	m_pFont->DrawTextW(1, NULL, str, -1, KGRect(700, 30, 900, 100), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));

	memset(wstr, 0, sizeof(wstr));
	if(m_accelTimer > 0.0) {
		swprintf(wstr, L"생성 속도 감소 %.1f", m_accelerate);
		m_pFont->DrawTextW(1, NULL, wstr, -1, KGRect(10, 85, 1024, 768), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	}
}


void cGame::OnEvent(UINT id, int xPos, int yPos)
{
	m_pStateWindow->OnEvent(id, xPos, yPos);
	switch(id)
	{
	case B_RETUNR:
		m_gamestop = !m_gamestop;
		m_stop	   = m_gamestop;
		for(int i=B_RETUNR; i<= B_MENU;i++)
			m_pStopmenu->GetButton(i)->SetDisable(true);
		break;
	case B_HELP:
		m_pHelp->Reset();
		m_showHelp = true;
		m_stop = true;
		for(int i=B_RETUNR; i<= B_MENU;i++)
			m_pStopmenu->GetButton(i)->SetDisable(true);
		break;
	case B_MENU:
		cMain()->Trans(L"menu");
		break;
	}
}


void cGame::UIVisible()
{
	m_UIAlpha[0] = m_UIAlpha[1] = 1.0;
	m_UITimer = 0.00001;
}


void cGame::GameNM(float time)
{
	int m;

	m = (int)time % 10;
	if(m_gameapl >= 1)
	{
		m_gamecheck = 1;
	}
	else if(m_gameapl < 0.4)
	{
		m_gamecheck = 0;
	}
	if(m_gamecheck == 1)
		m_gameapl = m_gameapl - (m *  0.00003);
	else if(m_gamecheck == 0)
		m_gameapl = m_gameapl + (m * 0.00003);


}