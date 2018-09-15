#include "cEnemy.h"
#include "cBloodstain.h"
#include "cBloodGush.h"
#include "cItem.h"

cEnemy::cEnemy(KGAnimate* animate, KGSprite* sprite)
{
	for(int i = 0; i < S_AMOUNT; i++)
		m_pSingle[i]		= new KGRenderSingle(animate);
	m_pSprite				= sprite;
	m_pSingle[S_WAIT]->Entry(L"j_stop", m_position, true, -1);
	m_pSingle[S_MOVE]->Entry(L"j_move", m_position, true, -1);
	m_pSingle[S_ATTACK]->Entry(L"j_throwing", m_position, true, -1);
	m_pSingle[S_CUT]->Entry(L"j_sword", m_position, true, -1);
	m_pSingle[S_SUFFER]->Entry(L"j_deth", m_position, true, -1);
	m_pSingle[S_STOP]->Entry(L"j_stop", m_position, true, -1);
	m_pSingle[S_DEFENCE]->Entry(L"j_defence", m_position, true, -1);
	m_pSingle[S_DIE]->Entry(L"", m_position, true, -1);
	m_pSingle[S_PUNG]->Entry(L"pung", m_position, true, -1);

	m_dartAmount			= 1;
	m_ppDart				= (cDart**)malloc(sizeof(cDart*) * m_dartAmount);
	for(int i = 0; i < m_dartAmount; i++)
		m_ppDart[i]			= new cDart();

	m_state					= S_DIE;
	m_kind					= D_ENOMAL;
	m_dieTimer				= 0.0;
}


cEnemy::~cEnemy()
{

}


void cEnemy::Update(float fElapsedTime)
{
	cNinja::Update(fElapsedTime);

	switch(m_state) {
		case S_WAIT:
			if(m_timer > 0.5) {
				m_reachPoint.x		= rand()%1024, 
					m_reachPoint.y		= 80.0 + rand()%688;
				SetMoveData(m_reachPoint);
				m_state				= S_MOVE;
				m_timer				= 0.0;
			}			
			break;
		case S_MOVE:
			{
				m_enemyPoint		= Sensing();

				if(m_enemyPoint.x != -1) {
					if(m_throwDelay == 0.0)
						DartNinjaAI(m_enemyPoint);
					else
						SetMoveData(m_enemyPoint);
				}
				Move();
			}
			break;

		case S_ATTACK:
			if(m_timer > THROW_TIME) {
				m_state				= S_MOVE;
				m_timer				= 0.0;
			}
			break;
		case S_DEFENCE:
			if(m_timer > 0.5) {
				m_state				= S_WAIT;
				m_timer				= 0.0;
			}
			break;
		case S_SUFFER:
			if(m_timer > SUFFER_TIME) {
				m_state				= S_DIE;
				m_timer				= 0.0;
			}
			break;
		case S_PUNG:
			if(m_timer > 0.5) {
				m_state				= S_WAIT;
				m_timer				= 0.0;
			}
			break;
	}
	if(m_dieTimer != 0.0) {
		m_dieTimer					-= fElapsedTime;
		if(m_dieTimer <= 0.0) {
			Die();
			m_dieTimer				= 0.0;
		}
	}
	m_pSingle[m_state]->SetMove(m_position);
	m_pSingle[m_state]->SetAngle(D3DXToRadian(m_rotation));
}


bool cEnemy::Create()
{
	m_displacement			= ENEMY_DISPLACEMENT;
	m_saveDelay				= ENEMY_DELAY;
	m_position				= D3DXVECTOR3(rand()%1024, 80.0 + rand()%688, 0);
	m_die					= true;
	m_state					= S_PUNG;

	m_pSingle[m_state]->SetMove(m_position);
	for(int i = 0; i < S_AMOUNT; i++) {
		m_pSingle[i]->SetMove(m_position);
		m_pSingle[i]->SetAngle(0.0);
	}
	m_speed					= 0.0;
	m_timer					= 0.0;
	m_dieTimer				= 0.0;
	m_rotation				= 0.0;
	m_pSingle[S_PUNG]->Entry(L"pung", m_position, true, -1);
	cGame* pGame		= (cGame*)cMain()->GetCurrent();
	pGame->m_pSound->Play(L"pung");
	return true;
}


void cEnemy::Reset()
{
	m_state					= S_DIE;
	m_speed					= 0.0;
	m_timer					= 0.0;
	m_throwDelay			= 0.0;
	m_dieTimer				= 0.0;

	for(int i = 0; i < m_dartAmount; i++)
		m_ppDart[i]->m_state= S_WAIT;

}


bool cEnemy::Suffer()
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	bool check				= false;
	m_timer					= 0.0;
	if(rand()%10 < 7) {
		Die();
		check				= true;
	}
	else {
		m_state					= S_DEFENCE;
		pGame->m_pSound->Play(L"defense");
	}

	m_pSingle[m_state]->SetAngle(D3DXToRadian(m_rotation));
	m_pSingle[m_state]->SetMove(m_position);
	return check;
}


void cEnemy::Die()
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();

	m_state					= S_SUFFER;
	m_timer					= 0.0;
	cBloodstain* k			= new cBloodstain(m_position);
	for(int i = 0; i < 10; i++)
		cBloodGush* z		= new cBloodGush(m_position, m_rotation);
	if(rand()%11000/1000.0 < 1)
		cItem*	o			= new cItem(m_position);
	pGame->m_pSound->Play(L"star_crash");

	m_pSingle[m_state]->SetAngle(D3DXToRadian(m_rotation));
	m_pSingle[m_state]->SetMove(m_position);
}


void cEnemy::DartNinjaAI(D3DXVECTOR3 point)
{
	if(point.x == -1)
		return;

	float dis = sqrt(pow(point.x - m_position.x, 2) + pow(point.y - m_position.y, 2));

	if(dis < 280.0) {
		if(m_position.x > point.x)
			m_reachPoint.x = m_position.x + rand()%50 + 20;
		else
			m_reachPoint.x = m_position.x - rand()%50 - 20;
		if(m_position.y > point.y)
			m_reachPoint.y = m_position.y + rand()%50 + 20;
		else
			m_reachPoint.y = m_position.y - rand()%50 - 20;
		SetMoveData(m_reachPoint);
	}
	if(dis < 300.0) {
		Attack(point);
	}
	else if(dis < 350.0) {
		m_reachPoint.x = point.x + (float)(rand()%50 - 25);
		m_reachPoint.y = point.y + (float)(rand()%50 - 25);
		SetMoveData(m_reachPoint);
	}
	else {
		SetMoveData(point);
	}
}


void cEnemy::SwordEnemyAI(D3DXVECTOR3 point)
{
	
}


D3DXVECTOR3 cEnemy::Sensing()
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	if(pGame->m_pHero->m_hide == true)
		return D3DXVECTOR3(-1, -1, 0);
	D3DXVECTOR3 tpoint		= pGame->m_pHero->m_position;
	if(m_position.x - SENSING_RANGE < tpoint.x && m_position.x + SENSING_RANGE > tpoint.x)
		if(m_position.y - SENSING_RANGE < tpoint.y && m_position.y + SENSING_RANGE > tpoint.y)
			return tpoint;
	return D3DXVECTOR3(-1, -1, 0);
}