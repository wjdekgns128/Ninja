#ifndef _CGUIDE_H
#define _CGUIDE_H

#include "cNinja.h"
using namespace KG;

class cGuide : public cNinja
{
public:
	D3DXVECTOR3				m_attPoint;
	D3DXVECTOR3				m_movePoint;

public:
	cGuide(KGAnimate* animate, KGSprite* sprite);
	~cGuide();

	void Init(int kind);
	void Update(float fElapsedTime);
};

#endif