#include "cParticle.h"
#include "cLink.h"

cParticle::cParticle()
{
	m_die					= false;
	m_single				= false;
	m_pSingle				= NULL;
	m_alpha					= 1.0;
	m_timer					= 0.0;
	m_radius				= 0.0;

	m_position				= D3DXVECTOR3(0,0,0);
	m_vector				= D3DXVECTOR3(0,0,0);

	memset(m_imgName, 0, sizeof(m_imgName));
}


cParticle::~cParticle()
{
	SAFE_DELETE(m_pSingle);
}


void cParticle::Update(float fElapsedTime)
{
	m_timer					+= fElapsedTime;
}


void cParticle::Render(KGSprite* sprite)
{
	if(m_die)
		return;

	sprite->Render(m_imgName, KGRect(m_position.x-m_radius,m_position.y-m_radius,m_position.x+m_radius,m_position.y+m_radius), D3DXCOLOR(1,1,1,m_alpha));
}


void cParticle::Register()
{
	cLink* pLink = cLink::GetInstance();
	pLink->m_List.push_back(this);
}


bool cParticle::Collision(D3DXVECTOR3 point, int radius)
{
	return (pow(m_position.x - point.x, 2) + pow(m_position.y - point.y, 2) < pow((float)m_radius + (float)radius, 2));
}