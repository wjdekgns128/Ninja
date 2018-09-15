#ifndef _CBLOODGUSH_H
#define _CBLOODGUSH_H

#include "cParticle.h"


class cBloodGush :public cParticle
{
public:
	

public:
	cBloodGush(D3DXVECTOR3 point, float angle);
	~cBloodGush();

	void Update(float fElapsedTime);
};

#endif