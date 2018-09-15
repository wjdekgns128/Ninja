#include "cBloodstain.h"

cBloodstain::cBloodstain(D3DXVECTOR3 point)
{
	m_position				= point;
	m_radius				= 20;

	memcpy(m_imgName, L"bloodstain", sizeof(m_imgName));

	cParticle::Register();
}


cBloodstain::~cBloodstain()
{
	
}


void cBloodstain::Update(float fElapsedTime)
{
	if(m_die)
		return;

	cParticle::Update(fElapsedTime);

	if(m_timer >= 6.0f) {
		m_alpha				-= 0.01;
		if(m_alpha == 0.0)
			m_die				= true;
	}
}