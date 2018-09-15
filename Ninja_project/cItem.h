#ifndef _CITEM_H
#define _CITEM_H

#include "cParticle.h"

class cItem :public cParticle
{
public:
	int						m_kind;
	float					m_xspeed;
	D3DXVECTOR3				m_endPoint;
	bool					m_direction;
public:
	cItem(D3DXVECTOR3 point);
	~cItem();

	void Update(float fElapsedTime);
	void Jump();
	void Eaten();
	void Bounce(bool wh);
};

#endif