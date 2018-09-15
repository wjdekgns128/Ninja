#ifndef _CSTATEWINDOW_H
#define _CSTATEWINDOW_H

#include "cGuide.h"
#include "cGame.h"
class cGuide;

using namespace KG;

class cStateWindow
{
public:
	KGDialog*				m_pDialog;
	KGFont*					m_pFont;
	cGuide*					m_pGuide[2];
	KGSprite*				m_pSprite;

	_ScorePlus				m_eventPlus;
	int						m_eventKill;
	int						m_skillPoint;
	int						m_lifeMax;

	bool					m_dartbuy;
	bool					m_guideTouch;
	D3DXVECTOR3				m_mouse;

public:
	cStateWindow(KGAnimate* animate, KGDialog* dialog, KGFont* font, KGSprite* sprite);
	~cStateWindow();

	void Reset(bool end);
	void OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void Mouse(bool LButton, D3DXVECTOR3 point);
	void TextDraw();
	void OnEvent(UINT id, int xPos, int yPos);
	void CALLBACK	OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
};

#endif