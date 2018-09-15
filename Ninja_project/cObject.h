#ifndef _COBJECT_H
#define _COBJECT_H

#include <KGEmotion.h>
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif

using namespace KG;

#include "cEnum.h"
#include "cDefine.h"

class cObject
{
public:
	KGSprite*				m_pSprite;
	int						m_state;
	
	int						m_radius;
	
	float					m_inclination; //기울기
	float					m_sections; //절편
	float					m_rotation;
	float					m_speed;
	float					m_displacement;

	float					m_timer;
	
	D3DXVECTOR3				m_position;
	D3DXVECTOR3				m_reachPoint;

public:
	cObject();
	virtual ~cObject();

	void SetMoveData(D3DXVECTOR3 point);
	void Move();
	float CalcAngle(D3DXVECTOR3 point);
	bool Collision(D3DXVECTOR3 point, int radius);	
};

#endif