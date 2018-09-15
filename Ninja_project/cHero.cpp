#include "cHero.h"
#include "cEnemy.h"
#include "cBloodGush.h"

cHero::cHero(KGAnimate* animate, KGSprite* sprite)
{
	for(int i = 0; i < S_AMOUNT; i++)
		m_pSingle[i]		= new KGRenderSingle(animate);
	m_pSprite				= sprite;
	m_pSingle[S_WAIT]->Entry(L"h_stop", m_position, true, -1);
	m_pSingle[S_MOVE]->Entry(L"h_move", m_position, true, -1);
	m_pSingle[S_ATTACK]->Entry(L"h_throwing", m_position, true, -1);
	m_pSingle[S_CUT]->Entry(L"h_sword", m_position, true, -1);
	m_pSingle[S_SUFFER]->Entry(L"h_deth", m_position, true, -1);
	m_pSingle[S_STOP]->Entry(L"h_stop", m_position, true, -1);
	m_pSingle[S_DEFENCE]->Entry(L"h_defence", m_position, true, -1);
	m_pSingle[S_DIE]->Entry(L"h_die", m_position, true, -1);
	

	m_dartAmount			= 7;
	m_ppDart				= (cDart**)malloc(sizeof(cDart*) * m_dartAmount);
	for(int i = 0; i < m_dartAmount; i++)
		m_ppDart[i]			= new cDart();

	ReSet();
}


cHero::~cHero()
{
	
}


void cHero::Update(float fElapsedTime)
{
	cGame* pGame		= (cGame*)cMain()->GetCurrent();
	cNinja::Update(fElapsedTime);

	switch(m_state) {
		case S_WAIT:	
			break;
		case S_MOVE:
			Move();
			break;
		case S_ATTACK:
			Move();
			if(m_timer > THROW_TIME) {
				m_state				= S_MOVE;
				m_timer				= 0.0;
			}
			break;
		case S_CUT:
			Move();
			
			if(m_timer > CUT_DELAY) {
				m_state				= S_MOVE;
				m_timer				= 0.0;
			}
			break;
		case S_SUFFER:
			if(m_timer > SUFFER_TIME) {
				m_state				= S_DIE;
				m_timer				= 0.0;
				cGame* pGame		= (cGame*)cMain()->GetCurrent();
				pGame->SaveScore(pGame->m_score);
				pGame->m_pDialog->GetButton(99)->SetShow(true);
			}
			break;
		case S_DEFENCE:
			Move();
			Defence();
			if(m_timer > 0.5) {
				(Collision(m_reachPoint, 0) == true) ? m_state = S_WAIT : m_state = S_MOVE;
				m_timer				= 0.0;
			}
			break;
	}
	if(m_sum == true)
		Sum(fElapsedTime);
	if(m_hide == true) {
		m_hideTimer					+= fElapsedTime;
		HideBlink(fElapsedTime);
		if(m_hideTimer > 5.0f)
			EndHide();
	}
	if(m_levelUpTimer != 0.0) {
		m_levelUpTimer				-= fElapsedTime;
		m_levelUpValue				+= 0.5;
		if(m_levelUpTimer < 0.0)
			m_levelUpTimer			= 0.0;
	}

	m_pSingle[m_state]->SetMove(m_position);
	m_pSingle[m_state]->SetAngle(D3DXToRadian(m_rotation));
}


void cHero::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cNinja::OnFrameRender(pd3dDevice, fTime, fElapsedTime, pUserContext);
	
	if(m_levelUpTimer != 0.0)
		m_pSprite->Render(L"레벨업", D3DXVECTOR3(m_position.x-45, m_position.y-50-m_levelUpValue,0), D3DXCOLOR(1,1,1,1));

	if(m_sum == true) {
		ID3DXLine* line;
		D3DXCreateLine(pd3dDevice, &line);
		line->SetWidth(2.5);
		
		line->Draw(m_linePoint,2,D3DXCOLOR(1,1,1,1));
		line->End();
		line->Release();
	}
}


void cHero::Key(char key)
{
	if(m_state == S_DIE || m_state == S_SUFFER)
		return;
	cGame* pGame		= (cGame*)cMain()->GetCurrent();
	switch(key) {
		case VK_D:
			m_state					= S_DEFENCE;
			m_timer					= 0.0;
			if(m_hide == true)
				EndHide();
			break;
		case VK_A:
			m_keyState				= !m_keyState;
			pGame->UIVisible();
			break;
		case VK_S:
			if(m_inven[0] != I_NOITEM) {
				if(Skill(m_inven[0])) {
					if(m_inven[1] != I_NOITEM) {
						m_inven[0]	= m_inven[1];
						m_inven[1]	= I_NOITEM;
					}
					else
						m_inven[0]	= I_NOITEM;
				}
			}
			pGame->UIVisible();
			break;
	}
}


void cHero::Mouse(bool direction, D3DXVECTOR3 point)		//flase : 왼쪽 true : 오른쪽
{
	if(m_state == S_SUFFER || m_state == S_DIE)
		return;
	if(point.y < 80.0)
		return;

	if(direction == false) {
		if(m_hide == true)
			EndHide();
		if(m_sumTouch == true) {
			SetSum(point);
			m_sumTouch		= false;
			return;
		}
		if(m_keyState == true)
			Attack(point);
		else {
			cGame* pGame	= (cGame*)cMain()->GetCurrent();
			if(pGame->m_scorePlus[4].show == true) {
				int a		= rand()%10;
				if(a < 3)
					Wield(point);
				else
					Cut(point);
			}
			else
				Cut(point);
		}
	}
	else {
		m_reachPoint = point;
		SetMoveData(m_reachPoint);
		if(m_state != S_CUT)
			m_timer			= 0.0;
	}
}


void cHero::ReSet()
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();

	for(int i = 0; i < m_dartAmount; i++)
		m_ppDart[i]->m_state = S_WAIT;
	m_state					= S_WAIT;

	m_hideTimer				= 0.0;
	m_sum					= false;
	m_sumTouch				= false;
	m_hide					= false;
	m_keyState				= false;
	m_speed					= 0.0;
	m_levelUpTimer			= 0.0;
	m_blinkTimer			= 0.0;

	if(m_life <= 0) {
		m_life					= 1;
		m_skillInven			= 0;
		m_displacement			= HERO_DISPLACEMENT;
		m_saveDelay				= 1.0;
		m_kind					= 0;
	}
	
	m_inven[0] = m_inven[1] = I_NOITEM;
	m_position				= D3DXVECTOR3(512.0, 384.0, 0);
	m_reachPoint			= D3DXVECTOR3(512.0, 384.0, 0);
	for(int i = 0; i < S_AMOUNT; i++)
		m_pSingle[i]->SetMove(m_position);
}


void cHero::Defence()
{
	cGame* pGame		= (cGame*)cMain()->GetCurrent();
	
	for(int i = 0; i < ENEMY_AMOUNT; i++) {
		for(int j = 0; j < 1; j++) {
			if(pGame->m_pEnemy[i]->m_ppDart[j]->m_state != S_MOVE)
				continue;
			if(Collision(pGame->m_pEnemy[i]->m_ppDart[j]->m_position, pGame->m_pEnemy[i]->m_ppDart[j]->m_radius+5)) {
				pGame->m_pEnemy[i]->m_ppDart[j]->m_state = S_WAIT;
				pGame->m_pSound->Play(L"defense");
			}
		}
	}
}


void cHero::Cut(D3DXVECTOR3 point)
{
	if(m_state == S_CUT)
		return;

	float inclination		= (point.y - m_position.y)/(point.x - m_position.x);
	float sections			= m_position.y - (m_position.x * inclination);
	float x					= m_position.x + 30*(point.x - m_position.x)/(sqrt(pow((point.x - m_position.x),2) + pow((point.y - m_position.y),2)));
	float y					= (inclination * x) + sections;

	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	for(int i = 0; i < ENEMY_AMOUNT; i++) {
		for(int j = 0; j < pGame->m_pEnemy[i]->m_dartAmount; j++)
			if(pGame->m_pEnemy[i]->m_ppDart[j]->m_state == S_MOVE)
				if(pGame->m_pEnemy[i]->m_ppDart[j]->Collision(D3DXVECTOR3(x,y,0), 30))
					pGame->m_pEnemy[i]->m_ppDart[j]->m_state = S_WAIT;
		if(pGame->m_pEnemy[i]->m_state == S_DIE || pGame->m_pEnemy[i]->m_state == S_SUFFER)
			continue;
		if(pGame->m_pEnemy[i]->Collision(D3DXVECTOR3(x, y, 0), 30)) {
			pGame->m_pEnemy[i]->Suffer();
		}
	}

	m_timer			= 0.0;
	m_state			= S_CUT;
	m_rotation		= CalcAngle(point);
	m_pSingle[m_state]->SetAngle(D3DXToRadian(m_rotation));

	if(rand()%10 < 7) {
		m_pSingle[m_state]->Entry(L"h_sword", m_position, true, -1);
	}
	else {
		m_pSingle[m_state]->Entry(L"h_sword1", m_position, true, -1);
	}
	pGame->m_pSound->Play(L"sword_attack");
}


void cHero::Wield(D3DXVECTOR3 point)
{
	if(m_state == S_CUT)
		return;

	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	for(int i = 0; i < ENEMY_AMOUNT; i++) {
		for(int j = 0; j < pGame->m_pEnemy[i]->m_dartAmount; j++)
			if(pGame->m_pEnemy[i]->m_ppDart[j]->m_state == S_MOVE)
				if(pGame->m_pEnemy[i]->m_ppDart[j]->Collision(m_position, 40))
					pGame->m_pEnemy[i]->m_ppDart[j]->m_state = S_WAIT;
		if(pGame->m_pEnemy[i]->m_state == S_DIE || pGame->m_pEnemy[i]->m_state == S_SUFFER)
			continue;
		if(pGame->m_pEnemy[i]->Collision(m_position, 40)) {
			pGame->m_pEnemy[i]->Suffer();
		}
	}

	m_timer			= 0.0;
	m_state			= S_CUT;
	m_rotation		= CalcAngle(point);
	m_pSingle[m_state]->SetAngle(D3DXToRadian(m_rotation));
	m_pSingle[m_state]->Entry(L"h_sword", m_position, true, -1);
	pGame->m_pSound->Play(L"sword_attack");
}


void cHero::Suffer()
{
	m_life--;
	if(m_life <= 0) {
		m_state				= S_SUFFER;
		m_pSingle[m_state]->SetMove(m_position);
	}
	m_timer					= 0.0;

	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	for(int i = 0; i < 10; i++)
		cBloodGush* z		= new cBloodGush(m_position, m_rotation);
}


void cHero::Hide()
{
	m_blink					= false;
	if(m_hide == false) {
		m_hide					= true;
		m_displacement			-= 1.5;
	}
	m_hideTimer				= 0.0;
	m_blinkTimer			= 0.0;
	m_maxBlinkTimer			= 0.2;
	SetMoveData(m_reachPoint);

	m_pSingle[S_WAIT]->Entry(L"h_hidestop", m_position, true, -1);
	m_pSingle[S_MOVE]->Entry(L"h_hide", m_position, true, -1);
}


void cHero::EndHide()
{
	m_displacement			+= 1.5;
	m_hide					= false;
	SetMoveData(m_reachPoint);
	m_pSingle[S_WAIT]->Entry(L"h_stop", m_position, true, -1);
	m_pSingle[S_MOVE]->Entry(L"h_move", m_position, true, -1);
}


void cHero::Eat(int item)
{
	for(int i = 0; i < 2; i++)
		if(m_inven[i] == I_NOITEM) {
			cGame* pGame			= (cGame*)cMain()->GetCurrent();
			m_inven[i] = item;
			pGame->UIVisible();
			break;
		}
}


void cHero::LevelUp()
{
	m_levelUpTimer			= 1.5;
	m_levelUpValue			= 0.0;
}


bool cHero::Skill(int item)
{
	switch(item) {
		case I_HIDE:
			Hide();
			break;
		case I_THREEDART:
			SThreeDart();
			if(m_hide == true)
				EndHide();
			return true;
			break;
		case I_SUM:
			m_sumTouch		= true;
			return true;
			break;
	}
}


void cHero::SThreeDart()
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();

	int count = 0;
	void* save[3] = {0,};
	bool check = false;
	for(int i = 0; i < ENEMY_AMOUNT; i++) {
		if(pGame->m_pEnemy[i]->m_state == S_DIE || pGame->m_pEnemy[i]->m_state == S_SUFFER)
			continue;
		for(int k = 0; k < 2; k++) {
			if(pGame->m_pEnemy[i] == save[k]) {
				check = true;
				break;
			}
		}
		if(check == true) {
			check = false;
			continue;
		}
		for(int j = 0; j < m_dartAmount; j++) {
			if(m_ppDart[j]->m_state == S_WAIT) {
				m_ppDart[j]->Create(m_position, pGame->m_pEnemy[i]->m_position, m_kind);
				save[count] = &pGame->m_pEnemy[i];
				count++;
				break;
			}
		}
		if(count == 3)
			return;
	}
	for(int i = count; i < 3; i++) {
		for(int j = 0; j < m_dartAmount; j++) {
			if(m_ppDart[j]->m_state == S_WAIT) {
				m_ppDart[j]->Create(m_position, D3DXVECTOR3(rand()%1024, rand()%768, 0), m_kind);
				break;
			}
		}
	}
}


void cHero::SetSum(D3DXVECTOR3 point)
{
	memset(m_linePoint, 0, sizeof(m_linePoint));
	
	m_sumInclination		= (point.y - m_position.y)/(point.x - m_position.x);
	m_sumSections			= m_position.y - (m_position.x * m_sumInclination);
	m_sumSpeed				= 40.0*(point.x - m_position.x)/(sqrt(pow((point.x - m_position.x),2) + pow((point.y - m_position.y),2)));

	m_reachPoint			= point;
	m_rotation				= cObject::CalcAngle(point);
	m_sumDirection			= (point.x > m_position.x);

	if(m_sumDirection == true) {
		if(m_position.x + m_sumSpeed*3 > point.x) {
			m_position		= point;
			return;
		}
	}
	else {
		if(m_position.x + m_sumSpeed*3 < point.x) {
			m_position		= point;
			return;
		}
	}

	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	cEnemy* enemy = NULL;
	bool yDirection			= (m_position.y < point.y);
	float a;
	float b = pow(m_sumInclination, 2) + 1.0;
	for(int i = 0; i < ENEMY_AMOUNT; i++) {
		if(pGame->m_pEnemy[i]->m_state == S_DIE || pGame->m_pEnemy[i]->m_state == S_SUFFER)
			continue;
		enemy = pGame->m_pEnemy[i];
		if(m_sumDirection == true) {
			if(enemy->m_position.x + m_radius < m_position.x ||
				enemy->m_position.x - m_radius > point.x)
				continue;
		}
		else {
			if(enemy->m_position.x - m_radius > m_position.x ||
				enemy->m_position.x + m_radius < point.x)
				continue;
		}
		if(yDirection == true) {
			if(enemy->m_position.y + m_radius < m_position.y ||
				enemy->m_position.y - m_radius > point.y)
				continue;
		}
		else {
			if(enemy->m_position.y - m_radius > m_position.y ||
				enemy->m_position.y + m_radius < point.y)
				continue;
		}

		a = abs(m_sumInclination*enemy->m_position.x - enemy->m_position.y + m_sumSections);
		if(a / b <= 35) {
			enemy->m_dieTimer = (rand()%50000 / 10000.0)*0.1;
			enemy->m_state = S_WAIT;
			enemy->m_timer	= 0.0;
		}
	}

	m_linePoint[0].x		+= m_position.x + 1*m_sumSpeed;
	m_linePoint[0].y		= m_sumInclination * m_linePoint[0].x + m_sumSections;

	m_linePoint[1].x		+= m_linePoint[0].x + 2*m_sumSpeed;
	m_linePoint[1].y		= m_sumInclination * m_linePoint[1].x + m_sumSections;

	
	
	m_sumSavePoint			= point;
	m_sumSavePoint.x		-= m_sumSpeed;
	m_position				= point;
	m_state					= S_WAIT;
	m_speed					= 0.0;
	m_timer					= 0.0;

	m_sumTimer				= 0.0;
	m_sum					= true;
}


void cHero::Sum(float time)
{
	m_sumTimer				+= time;

	if(m_sumDirection == true) {
		if(m_linePoint[1].x < m_sumSavePoint.x) {
			m_linePoint[1].x	+= m_sumSpeed;
			m_linePoint[1].y	= m_sumInclination * m_linePoint[1].x + m_sumSections;
		}
	}
	else {
		if(m_linePoint[1].x > m_sumSavePoint.x) {
			m_linePoint[1].x	+= m_sumSpeed;
			m_linePoint[1].y	= m_sumInclination * m_linePoint[1].x + m_sumSections;
		}
	}

	if(m_sumTimer > 0.2) {
		if(m_sumDirection == true) {
			if(m_linePoint[0].x > m_sumSavePoint.x)
				m_sum			= false;
			m_linePoint[0].x	+= m_sumSpeed;
			m_linePoint[0].y	= m_sumInclination * m_linePoint[0].x + m_sumSections;
		}
		else {
			if(m_linePoint[0].x < m_sumSavePoint.x)
				m_sum			= false;
			m_linePoint[0].x	+= m_sumSpeed;
			m_linePoint[0].y	= m_sumInclination * m_linePoint[0].x + m_sumSections;
		}
	}
}


void cHero::HideBlink(float fElapsedTime)
{
	if(m_hideTimer > 3.2) {
		m_blinkTimer += fElapsedTime;
		if(m_blinkTimer >= m_maxBlinkTimer) {
			if(m_blink == false) {
				m_pSingle[S_WAIT]->Entry(L"h_stop", m_position, true, -1);
				m_pSingle[S_MOVE]->Entry(L"h_move", m_position, true, -1);
			}
			else {
				m_pSingle[S_WAIT]->Entry(L"h_hidestop", m_position, true, -1);
				m_pSingle[S_MOVE]->Entry(L"h_hide", m_position, true, -1);
				m_maxBlinkTimer -= 0.04;
			}
			m_blink = !m_blink;
			m_blinkTimer = 0.0;
		}
	}
}