#include "cTutorial.h"
#include "cLink.h"


cTutorial::cTutorial()
{
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
	m_pSingle				= NULL;
	m_pFont					= NULL;
	m_pDialog				= NULL;
	m_pDialog2				= NULL;
	m_pName					= NULL;
	m_pCursor				= NULL;
	m_pSound				= NULL;

	m_pHero					= NULL;
	for(int i = 0; i < ENEMY_AMOUNT; i++)
		m_pEnemy[i]			= NULL;
	
	m_stop					= true;
	m_nameWrite				= true;

	m_timer					= 0.0;
	m_max					= 0.5;
	m_accelerate			= 0.0;
	m_accelTimer			= 0.0;
	m_maxEnemy				= 15;
	m_score					= 0;
	m_bestScore				= 0;
	memset(m_name, 0, sizeof(m_name));
	memset(m_bestName, 0, sizeof(m_bestName));
	m_curExp				= 0;
	m_expMax				= 7;

	m_showLvUp				= false;
	m_showHelp				= false;
	m_showStateWindow		= false;
	m_level					= 1;
	m_guideTouch			= false;

	m_enterTimer			= 0.0;
	m_enterAlpha			= 0.0;
	m_enterCheck			= true;

	memset(m_scorePlus, 0, sizeof(m_scorePlus));
}


cTutorial::~cTutorial()
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

	SAFE_DELETE(m_pHero);
	for(int i = 0; i < ENEMY_AMOUNT; i++)
		SAFE_DELETE(m_pEnemy[i]);
	cLink* pLink = cLink::GetInstance();
	delete pLink;
}


HRESULT cTutorial::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"../res/te/dart.Te");
		m_pSprite->Entry(L"../res/te/map.Te");
		m_pSprite->Entry(L"../res/te/example.te");
		m_pSprite->Entry(L"../res/te/gameover.te");
		m_pSprite->Entry(L"../res/te/BT.te");
		m_pSprite->Entry(L"../res/te/char.te");
		m_pSprite->Entry(L"../res/te/h.te");
		m_pSprite->Entry(L"../res/te/bg.te");
		m_pSprite->Entry(L"../res/te/cursor.te");
		m_pSprite->Entry(L"../res/te/enter.te");
		m_pSprite->Entry(L"../res/te/blood.te");
		m_pSprite->Entry(L"../res/te/point1.te");
		m_pSprite->Entry(L"../res/te/box.te");
		m_pSprite->Entry(L"../res/te/help1.te");
		m_pSprite->Entry(L"../res/te/help2.te");
		m_pSprite->Entry(L"../res/te/RankInterface.Te");
	}

	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"../res/ta/dart.Ta");
		m_pAnimate->Entry(L"../res/ta/char.Ta");
		m_pAnimate->Entry(L"../res/ta/h.Ta");
		m_pAnimate->Entry(L"../res/ta/point1.ta");
		m_pAnimate->Entry(L"../res/ta/help.ta");
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
		m_pDialog->AddNumber(0, L"num_", D3DXVECTOR3(620, 10, 0), 5 );
		m_pDialog->GetNumber(0)->SetNumber(m_score);
		m_pDialog->AddNumber(1, L"num_", D3DXVECTOR3(880, 10, 0), 5 );
		m_pDialog->GetNumber(1)->SetNumber(m_bestScore);
		m_pDialog->AddButton(99,L"Box1",L"Box1",L"Box1",L"Box1",D3DXVECTOR3(0,-20,0),true);
		m_pDialog->GetButton(99)->SetShow(false);
	}

	if(m_pDialog2 == NULL)
	{
		m_pDialog2 = new KGDialog(m_pSprite, NULL, this);
		m_pDialog2->AddButton(B_SKILL1, L"bt_return_default", L"bt_return_click", L"bt_return_over", L"bt_return_disable", D3DXVECTOR3(300,100,0), true);
		m_pDialog2->AddButton(B_SKILL2, L"bt_return_default", L"bt_return_click", L"bt_return_over", L"bt_return_disable", D3DXVECTOR3(300,150,0), true);
		m_pDialog2->AddButton(B_DART1, L"bt_return_default", L"bt_return_click", L"bt_return_over", L"bt_return_disable", D3DXVECTOR3(200,500,0), true);
		m_pDialog2->AddButton(B_DART2, L"bt_return_default", L"bt_return_click", L"bt_return_over", L"bt_return_disable", D3DXVECTOR3(400,500,0), true);
		m_pDialog2->GetButton(B_DART1)->SetDisable(true);
		m_pDialog2->GetButton(B_DART2)->SetDisable(true);
	}

	if(m_pName	== NULL)
	{
		m_pName			= new KGDialog(m_pSprite);
		m_pName->AddEditBox(100, m_pFont->Get(2), KGRect(520, 402, 1024, 768), D3DXCOLOR(1, 1, 1, 1), DT_NOCLIP);
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
		m_pSound->Entry(L"bgm", L"../res/sound/bgm/0036.wav");
		m_pSound->Play(L"bgm", true, 0, DSBPLAY_LOOPING);
	}

	if(m_pHero == NULL) {
		m_pHero				= new cHero(m_pAnimate, m_pSprite);
	}

	for(int i = 0; i < ENEMY_AMOUNT; i++)
		if(m_pEnemy[i] == NULL) {
			m_pEnemy[i]		= new cEnemy(m_pAnimate, m_pSprite);
		}


	return S_OK;
}


HRESULT cTutorial::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pFont);
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pDialog2);
	SAFE_ONRESETDEVICE(m_pName);
	return S_OK;
}


void cTutorial::OnLostDevice(void* pUserContext)
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

	SAFE_DELETE(m_pHero);
	for(int i = 0; i < ENEMY_AMOUNT; i++)
		SAFE_DELETE(m_pEnemy[i]);
}


void cTutorial::OnDestroyDevice(void* pUserContext)
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

	SAFE_DELETE(m_pHero);
	for(int i = 0; i < ENEMY_AMOUNT; i++)
		SAFE_DELETE(m_pEnemy[i]);
}


void cTutorial::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(m_stop) {
		if(m_nameWrite) {
			SAFE_ONFRAMEMOVE(m_pName);
		}
		return;
	}

	SAFE_ONFRAMEMOVE(m_pDialog);

	if(m_pHero->m_state == S_DIE) {
		ShowEnter(fElapsedTime);
		return;
	}

	m_timer += fElapsedTime;
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

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 4; j++) {
			if(m_scorePlus[i][j].show == true) {
				m_scorePlus[i][j].timer += fElapsedTime;
				if(m_scorePlus[i][j].timer > SCORETIMER) {
					m_scorePlus[i][j].alpha -= 0.05;
					if(m_scorePlus[i][j].alpha < 0.0)
						memset(m_scorePlus, 0, sizeof(m_scorePlus));
				}
			}
		}
	}
}


void cTutorial::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		if(m_stop) {
			if(m_nameWrite)
			{
				m_pSprite->Render(L"맵 1", KGRect(0,0,1024,768), D3DXCOLOR(1,1,1,1));
				m_pSprite->Render(L"이름기입란", D3DXVECTOR3(340,300,0),D3DXCOLOR(1,1,1,1));
				m_pName->GetEditBox(100)->SetDisable(false);
				m_pName->GetListBox(101)->SetDisable(false);

				SAFE_ONFRAMERENDER(m_pName);
			}
		}
		else {
			m_pSprite->Render(L"맵 1", KGRect(0,0,1024,768), D3DXCOLOR(1,1,1,1));

			cLink* pLink = cLink::GetInstance();
			pLink->Render(m_pSprite);
			for(int i = 0; i < m_maxEnemy; i++)
				SAFE_ONFRAMERENDER(m_pEnemy[i]);
			SAFE_ONFRAMERENDER(m_pHero);
			SAFE_ONFRAMERENDER(m_pDialog);

			UIDraw();

			SAFE_ONFRAMERENDER(m_pSingle);

			TextDraw();
		}
		SAFE_ONFRAMERENDER(m_pCursor);
		V(pd3dDevice->EndScene());
	}
}


void cTutorial::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	SAFE_ONKEYBOARD(m_pName);
	
	if(bKeyDown) {
		m_pHero->Key(nChar);

		switch(nChar) {
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
				/////////////////////////////////////////
				/////////////////////////////////////////
			case VK_F1:
				m_showHelp = true;
				m_stop = true;
				break;
			case VK_ESCAPE:
				m_showHelp = false;
				m_stop = false;
				break;
			case VK_RETURN:
				if(m_nameWrite == true)
				{
					m_nameWrite = false;
					m_stop		= false;
					m_pName->GetEditBox(100)->SetDisable(true);
					m_pName->GetListBox(101)->SetDisable(true);
					memcpy(m_name, m_pName->GetEditBox(100)->GetText(), sizeof(m_name));
					if(m_pName->GetEditBox(100)->empty() == true)
						memcpy(m_name, L"임시명", sizeof(L"임시명"));
				}
				else {
					if(m_pHero->m_state != S_DIE)
						break;
					m_pHero->ReSet();
					for(int i = 0; i < ENEMY_AMOUNT; i++) {
						m_pEnemy[i]->Reset();
					}
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
					memset(m_scorePlus, 0, sizeof(m_scorePlus));
					m_pDialog->GetNumber(0)->SetNumber(m_score);
					m_pDialog->GetNumber(1)->SetNumber(m_bestScore);
					m_pStateWindow->Reset(true);
					m_pDialog->GetButton(99)->SetShow(false);
					cLink* pLink = cLink::GetInstance();
					pLink->end();
				}
				break;
		}
	}
}


void cTutorial::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	SAFE_ONMOUSE(m_pCursor);
	SAFE_ONMOUSE(m_pDialog);

	if(m_stop) {
		SAFE_ONMOUSE(m_pDialog2);
		if(m_showStateWindow == true)
			m_pStateWindow->Mouse(bLeftButtonDown, D3DXVECTOR3(xPos, yPos, 0));
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


LRESULT cTutorial::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	SAFE_ONMSGPROC(m_pDialog);
	if(m_stop) {
		if(m_nameWrite)
			SAFE_ONMSGPROC(m_pName);
	}
	return uMsg;
}


void cTutorial::EnemyUpdate(float fElapsedTime)
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


void cTutorial::Collsion()
{
	for(int k = 0; k < m_maxEnemy; k++) {
		for(int j = 0; j < m_pEnemy[k]->m_dartAmount; j++) {
			if(m_pEnemy[k]->m_ppDart[j]->m_state == S_MOVE) {
				if(m_pHero->m_state == S_SUFFER || m_pHero->m_state == S_DIE || m_pEnemy[k]->m_ppDart[j]->m_saveObject == m_pHero)
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
					m_pHero->m_ppDart[j]->Bounce(k);
					m_pHero->m_ppDart[j]->m_saveObject = m_pEnemy[k];
					m_pEnemy[k]->Suffer();
					break;
				}
			}
		}
	}
}


void cTutorial::ExpManage(int exp)
{
	m_curExp				+= exp;
	if(m_curExp >= m_expMax) {
		m_level++;
		m_pStateWindow->m_skillPoint++;
		m_curExp			= m_curExp % m_expMax;
		m_expMax			= m_expMax + m_expMax * 0.2;
	}
}


void cTutorial::ScoreAccumulate(int score)
{
	if(score == 0)
		return;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(m_scorePlus[i][j].show == false) {
				m_scorePlus[i][j].timer = 0.0;
				m_scorePlus[i][j].alpha = 1.0;
				m_scorePlus[i][j].score = score;
				m_scorePlus[i][j].show = true;
				m_score += score;
				ExpManage(score);

				if(j == 2) {
					if(m_scorePlus[i][3].show == false) {
						int temp = 0;
						for(int l = 0; l < i+1; l++)
							for(int k = 0; k < 4; k++) {
								temp += m_scorePlus[l][k].score;
								m_scorePlus[l][k].alpha = 1.0;
								m_scorePlus[l][k].timer = 0.0;
							}
							m_scorePlus[i][3].score = temp / 3;
							m_score += m_scorePlus[i][3].score;
							ExpManage(m_scorePlus[i][3].score);
							m_scorePlus[i][3].timer = 0.0;
							m_scorePlus[i][3].alpha = 1.0;
							m_scorePlus[i][3].show = true;
							if(i == 2)
								m_scorePlus[i][3].timer = 1.5;
					}
				}
				return;
			}
		}
	}
}


void cTutorial::TextDraw()
{
	WCHAR wstr[20];
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 4; j++) {
			if(m_scorePlus[i][j].show == true) {
				swprintf(wstr, L"+%d", m_scorePlus[i][j].score);
				if(j != 3)
					m_pFont->DrawTextW(0, NULL, wstr, -1, KGRect(600+j*30, 40+i*30, 1024, 768), DT_NOCLIP, D3DXCOLOR(1, 1, 1, m_scorePlus[i][j].alpha));
				else
					m_pFont->DrawTextW(0, NULL, wstr, -1, KGRect(610+j*30, 40+i*30, 1024, 768), DT_NOCLIP, D3DXCOLOR(0, 1, 0, m_scorePlus[i][j].alpha));
			}
		}
	}

	m_pFont->DrawTextW(0, NULL, L"도움말 F1", -1, KGRect(900, 730, 1024, 768), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	m_pFont->DrawTextW(1, NULL, L"현재 점수", -1, KGRect(500, 10, 940, 30), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	WCHAR str[15];
	m_pFont->DrawTextW(1, NULL, m_name, -1, KGRect(10, 10, 100, 40), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	memset(wstr, 0, sizeof(wstr));
	swprintf(str, L"%d / %d  Lv%d", m_curExp, m_expMax, m_level);
	m_pFont->DrawTextW(1, NULL, str, -1, KGRect(10, 50, 100, 100), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));

	memset(wstr, 0, sizeof(wstr));
	if(m_accelTimer > 0.0) {
		swprintf(wstr, L"감속 %.1f", m_accelerate);
		m_pFont->DrawTextW(1, NULL, wstr, -1, KGRect(350, 10, 1024, 768), DT_NOCLIP, D3DXCOLOR(1, 1, 1, 1));
	}
}