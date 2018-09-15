#ifndef _CHELP_H
#define _CHELP_H

#include "cGuide.h"
class cGuide;

using namespace KG;

class cHelp
{
public:
	KGSprite*				m_pSprite;
	KGRenderSingle*			m_pSingle[4];

	bool					m_curPage;

	float					m_timer;

	int						m_click[3];

public:
	cHelp(KGAnimate* animate, KGSprite* sprite);
	~cHelp();

	void Reset();
	void OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	bool CALLBACK	OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
};

#endif