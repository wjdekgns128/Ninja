#include "cGuide.h"
#include "cEnum.h"
#include "cGame.h"

cGuide::cGuide(KGAnimate* animate, KGSprite* sprite)
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

	m_dartAmount			= 5;
	m_ppDart				= (cDart**)malloc(sizeof(cDart*) * m_dartAmount);
	for(int i = 0; i < m_dartAmount; i++)
		m_ppDart[i]			= new cDart();
}


cGuide::~cGuide()
{
	
}


void cGuide::Init(int kind)
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	m_position				= D3DXVECTOR3(550.0, 100.0 + (kind*150), 0.0);
	if(kind == 0) {
		m_displacement		= pGame->m_pHero->m_displacement;
		m_position			= D3DXVECTOR3(550, 100,0);
		m_movePoint			= D3DXVECTOR3(2000,100,0);
		SetMoveData(m_movePoint);
	}
	else if(kind == 1) {
		m_position			= D3DXVECTOR3(550, 225,0);
		m_throwDelay		= 0.0;
		m_attPoint			= D3DXVECTOR3(2000,225,0);
		m_saveDelay			= pGame->m_pHero->m_saveDelay;
		Attack(m_attPoint);
	}
	for(int i = 0; i < S_AMOUNT; i++) {
		m_pSingle[i]->SetMove(m_position);
		m_pSingle[i]->SetAngle(D3DXToRadian(m_rotation));
	}
	for(int i = 0; i < m_dartAmount; i++)
		m_ppDart[i]->m_state = S_WAIT;
	m_kind					= 0;
}


void cGuide::Update(float fElapsedTime)
{
	cNinja::Update(fElapsedTime);

	switch(m_state)
	{
	case S_WAIT:
		if(m_throwDelay == 0.0)
			Attack(m_attPoint);
		break;
	case S_MOVE:
		if(m_position.x > 1024.0)
			m_position.x	= 550;
		m_pSingle[S_SUFFER]->SetMove(m_position);
		Move();
		break;
	case S_ATTACK:
		if(m_throwDelay == 0.0)
			Attack(m_attPoint);
		if(m_timer > THROW_TIME) {
			m_timer			= 0.0;
			m_state			= S_WAIT;
		}
		break;
	case S_SUFFER:
		if(m_timer > SUFFER_TIME) {
			m_state			= S_DIE;
			m_timer			= 0.0;
		}
		break;
	case S_DIE:
		if(m_timer > 0.5) {
			m_position.x	= 550;
			m_state			= S_MOVE;
		}
		break;
	}
	for(int i = 0; i < m_dartAmount; i++) {
		if(m_ppDart[i]->m_state == S_MOVE) {
			if(m_ppDart[i]->m_position.x < 515.0 || m_ppDart[i]->m_position.x > 975 || m_ppDart[i]->m_position.y < 45.0 || m_ppDart[i]->m_position.y > 265.0)
				m_ppDart[i]->m_state = S_WAIT;
		}
	}

	m_pSingle[m_state]->SetMove(m_position);
	m_pSingle[m_state]->SetAngle(D3DXToRadian(m_rotation));
}