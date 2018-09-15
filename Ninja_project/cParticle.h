#ifndef _CPARTICLE_H
#define _CPARTICLE_H

#include "cInclude.h"

using namespace KG;

class cParticle
{
public:
	KGRenderSingle*			m_pSingle;

	bool					m_die;
	bool					m_single;
	D3DXVECTOR3				m_position;
	D3DXVECTOR3				m_vector;
	
	float					m_timer;
	float					m_alpha;
	float					m_radius;

	WCHAR					m_imgName[20];

public:
	cParticle();
	virtual ~cParticle();

	virtual void Update(float fElapsedTime);
	void Render(KGSprite* sprite);
	void Register();
	bool Collision(D3DXVECTOR3 point, int radius);
};

#endif