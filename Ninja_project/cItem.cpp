#include "cItem.h"
#define JUMP_SPEED 10 - (20 * m_timer)

cItem::cItem(D3DXVECTOR3 point)
{
	m_kind					= 1+ rand()%3;
	m_position				= point;
	m_radius				= 30;
	m_direction				= false;
	int x					= 50;
	int y					= 50;
	m_endPoint				= D3DXVECTOR3(m_position.x + (rand()%x - (x/2)), m_position.y + (rand()%y - (y/4)), 0);
	m_xspeed				= (m_endPoint.x - m_position.x)*0.5;
	
	if(m_kind == 1)
		memcpy(m_imgName, L"h", sizeof(m_imgName));
	else if(m_kind == 2)
		memcpy(m_imgName, L"t", sizeof(m_imgName));
	else if(m_kind == 3)
		memcpy(m_imgName, L"c", sizeof(m_imgName));

	cParticle::Register();
}


cItem::~cItem()
{
	
}


void cItem::Update(float fElapsedTime)
{
	if(m_die)
		return;

	cParticle::Update(fElapsedTime);
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	if(pGame->m_pHero->Collision(m_position, m_radius/2)) {
		Eaten();
		m_die				= true;
	}
	if(m_timer > 6.0f) {
		m_alpha -= 0.01;
		if(m_alpha == 0.0)
			m_die			= true;
	}
	if(JUMP_SPEED > 0 || m_position.y > m_endPoint.y)
		Jump();
	if(m_position.x < 0.0 || m_position.x > 1024.0)
		Bounce(false);
	if(m_position.y < 80.0 || m_position.y > 768.0)
		Bounce(true);
}


void cItem::Jump()
{
	m_position.x			+= m_xspeed;
	(m_direction == false) ? m_position.y -= JUMP_SPEED : m_position.y += JUMP_SPEED;
}


void cItem::Eaten()
{
	cGame* pGame		= (cGame*)cMain()->GetCurrent();
	pGame->m_pHero->Eat(m_kind);
}


void cItem::Bounce(bool wh)
{
	m_timer					= 0.0;
	if(wh == true)
		m_direction				= !m_direction;
	else
		m_xspeed				= - m_xspeed;
}