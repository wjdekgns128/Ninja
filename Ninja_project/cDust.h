#ifndef _CDUST_H
#define _CDUST_H

#include "cParticle.h"

class cDust :public cParticle
{
public:

public:
	cDust();
	~cDust();

	void Update(float fElapsedTime);
};

#endif