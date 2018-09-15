#ifndef _CBLOODSTAIN_H
#define _CBLOODSTAIN_H

#include "cParticle.h"

class cBloodstain :public cParticle
{
public:

public:
	cBloodstain(D3DXVECTOR3 point);
	~cBloodstain();

	void Update(float fElapsedTime);
};

#endif