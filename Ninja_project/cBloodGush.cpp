#include "cBloodGush.h"
#include <math.h>

cBloodGush::cBloodGush(D3DXVECTOR3 point, float angle)
{
	m_position				= point;
	m_radius				= 5 + rand()%30000 / 10000.1;

	float speedx			= rand()%50000 / 10000.1;
	float speedy			= rand()%50000 / 10000.1;
	float ang				= angle + rand()%80 + 50;
	m_vector.x				= speedx*cos(ang*DegToRad);
	m_vector.y				= speedy*cos(ang*DegToRad);

	memcpy(m_imgName, L"bloodgush", sizeof(m_imgName));

	cParticle::Register();
}


cBloodGush::~cBloodGush()
{
	
}


void cBloodGush::Update(float fElapsedTime)
{
	if(m_die)
		return;

	cParticle::Update(fElapsedTime);

	m_radius					-= 0.2;
	m_position.x				+= m_vector.x;
	m_position.y				+= m_vector.y;
	if(m_radius <= 0.0)
		m_die					= true;
}