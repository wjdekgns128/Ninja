#include "cObject.h"


cObject::cObject()
{
	m_state					= S_WAIT;
	m_inclination			= 0.0;
	m_sections				= 0.0;
	m_rotation				= 0.0;
	m_speed					= 0.0;
	m_timer					= 0.0;
	
	m_position				= D3DXVECTOR3(0,0,0);
	m_reachPoint			= D3DXVECTOR3(0,0,0);
}


cObject::~cObject()
{
	
}


float cObject::CalcAngle(D3DXVECTOR3 point)
{
	float x = point.x - m_position.x + 0.001;
	float y = point.y - m_position.y + 0.001;
	float nTan = x/y;
	float ang = D3DXToDegree( atan(nTan) );

	if( x>0 && y>0 )
	{
		return ang + 180;
	}
	else if( x<0 && y>0 )
	{
		return ang + 180;
	}
	else if( x<0 && y<0 )
	{
		return ang;
	}
	else if( x>0 && y<0 )
	{
		return ang + 360;
	}
}


bool cObject::Collision(D3DXVECTOR3 point, int radius)
{
	return (pow(m_position.x - point.x, 2) + pow(m_position.y - point.y, 2) < pow((float)m_radius + (float)radius, 2));
}


void cObject::SetMoveData(D3DXVECTOR3 point)
{
	if((point.y - m_position.y) == 0.0) {
		m_position.y		+= 0.1;
		point.y				+= 0.01;
	}
	if((point.x - m_position.x) == 0.0) {
		m_position.x		+= 0.01;
		point.x				+= 0.1;
	}

	m_inclination			= (point.y - m_position.y)/(point.x - m_position.x);
	m_sections				= m_position.y - (m_position.x * m_inclination);
	m_speed					= m_displacement*(point.x - m_position.x)/(sqrt(pow((point.x - m_position.x),2) + pow((point.y - m_position.y),2)));
	m_rotation				= CalcAngle(point);
	
	if(m_speed == 0.0)
		int a = 0;
	m_reachPoint			= point;
	if(m_state != S_CUT && m_state != S_ATTACK)
		m_state					= S_MOVE;
}


void cObject::Move()
{
	m_position.x			+= m_speed;
	m_position.y			= (m_inclination * m_position.x) + m_sections;
}