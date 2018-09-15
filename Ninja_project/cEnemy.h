#ifndef _cEnemy_H
#define _cEnemy_H

#include "cNinja.h"
#include "cInclude.h"

using namespace KG;

class cEnemy : public cNinja
{
public:
	bool					m_die;
	
	float					m_dieTimer;
	D3DXVECTOR3				m_enemyPoint;

public:
	cEnemy(KGAnimate* animate, KGSprite* sprite);
	~cEnemy();

	void Update(float fElapsedTime);
	bool Create();
	void Reset();
	bool Suffer();
	void Die();
	void DartNinjaAI(D3DXVECTOR3 point);
	void SwordEnemyAI(D3DXVECTOR3 point);
	D3DXVECTOR3 cEnemy::Sensing();
};

#endif