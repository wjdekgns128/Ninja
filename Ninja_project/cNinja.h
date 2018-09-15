#ifndef _CNINJA_H
#define _CNINJA_H

#include <KGEmotion.h>
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif

using namespace KG;

#include "cObject.h"
#include "cDart.h"
#include "cEnum.h"

class cNinja : public cObject
{
public:
	KGRenderSingle*			m_pSingle[S_AMOUNT];
	cDart**					m_ppDart;

	int						m_dartAmount;
	int						m_kind;
	
	float					m_throwDelay;
	float					m_saveDelay;

public:
	cNinja();
	~cNinja();

	void Update(float fElapsedTime);
	void Attack(D3DXVECTOR3 point);
	void Move();
	void SetDartKind(int kind);
	void SetMoveData(D3DXVECTOR3 point);

	virtual void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
};

#endif