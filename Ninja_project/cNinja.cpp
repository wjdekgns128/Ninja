#include "cNinja.h"
#include "cTutorial.h"


cNinja::cNinja()
{
	m_saveDelay				= 0.0;
	m_radius				= 20;
	
	m_throwDelay			= 0.0;
	m_saveDelay				= 0.0;
	m_dartAmount			= 0;
}


cNinja::~cNinja()
{
	for(int i = 0; i < S_AMOUNT; i++)
		SAFE_DELETE(m_pSingle[i]);
	for(int i = 0; i < m_dartAmount; i++)
		delete [] m_ppDart[i];
	free(m_ppDart);
}


void cNinja::Update(float fElapsedTime)
{
	m_timer					+= fElapsedTime;
	for(int i = 0; i < m_dartAmount; i++)
		m_ppDart[i]->Update(fElapsedTime);
	
	if(m_throwDelay > 0.0)
		m_throwDelay		-= fElapsedTime;
	else
		m_throwDelay		= 0.0;

	if(m_state == S_MOVE) {
		if(Collision(m_reachPoint, 0)) {
			m_state				= S_WAIT;
			m_speed				= 0.0;
			m_timer				= 0.0;
		}
	}
}


void cNinja::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	SAFE_ONFRAMERENDER(m_pSingle[m_state]);

	for(int i = 0; i < m_dartAmount; i++) {
		m_ppDart[i]->Render(m_pSprite);
		if(m_ppDart[i]->m_state == S_PUNG)
			SAFE_ONFRAMERENDER(m_ppDart[i]->m_pSingle);
	}
}


void cNinja::Move()
{
	if(m_speed == 0.0)
		return;

	cObject::Move();
	if(m_position.y < 80.0) {
		m_state				= S_WAIT;
		m_timer				= 0.0;
		m_speed				= 0.0;
	}
	if(Collision(m_reachPoint, 0)) {
		m_state				= S_WAIT;
		m_speed				= 0.0;
	}
}


void cNinja::Attack(D3DXVECTOR3 point)
{
	if(m_throwDelay != 0.0)
		return;

	cTutorial* pGame		= (cTutorial*)cMain()->GetCurrent();
	for(int i = 0; i < m_dartAmount; i++) {
		if(m_ppDart[i]->m_state == S_WAIT) {
			m_ppDart[i]->Create(m_position, point, m_kind);
			m_timer			= 0.0;
			m_throwDelay	= m_saveDelay;
			m_state			= S_ATTACK;
			m_rotation		= CalcAngle(point);
			m_pSingle[m_state]->SetMove(m_position);
			m_pSingle[m_state]->SetAngle(D3DXToRadian(m_rotation));
			pGame->m_pSound->Play(L"star_attack");
			return;
		}
	}
}


void cNinja::SetDartKind(int kind)
{
	m_kind					= kind;
	switch(kind) {
		case D_PENETRATE:
			break;
		case D_BOUNCE:
			break;
		case D_BOOM:
			break;
		case D_HALF:
			m_saveDelay		-= 0.5;
			if(m_saveDelay < 0)
				m_saveDelay = 0;
			break;
	}
}


void cNinja::SetMoveData(D3DXVECTOR3 point)
{
	cObject::SetMoveData(point);
	m_pSingle[S_MOVE]->SetAngle(D3DXToRadian(m_rotation));
}