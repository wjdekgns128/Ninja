#ifndef _CDART_H
#define _CDART_H

#include <KGEmotion.h>
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif

using namespace KG;

#include "cObject.h"

class cDart : public cObject
{
public:
	KGRenderSingle*			m_pSingle;

	int						m_kind;
	int 					m_bounce;
	int						m_frame;
	
	void*					m_saveObject;
	
	float					m_alpha;

	bool					m_reach;
	
	WCHAR					m_imgName[20];

	D3DXVECTOR3				m_startPoint;

public:
	cDart();
	~cDart();

	void Update(float time);
	void Render(KGSprite* sprite);
	void Create(D3DXVECTOR3 position, D3DXVECTOR3 point, int kind);
	void Bounce(int num);
	D3DXVECTOR3 Sensing(int _num);
};

#endif