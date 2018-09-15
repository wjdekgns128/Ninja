#ifndef _CMENU_H
#define _CMENU_H

#include "CMAIN.h"
#include "cHelp.h"
class cHelp;


using namespace KG;

class cMenu : public KGScene, public KGResponseDialog
{
public:
	KGSprite*				m_pSprite;
	KGDialog*				m_pDialog;
	KGCursor*				m_pCursor;
	KGSound*				m_pSound;
	KGAnimate*				m_pAnimate;
	cHelp*					m_pHelp;

	bool					m_showHelp;

	D3DXVECTOR3				m_verMove;
	int						m_start[3];
	int						m_help;
	float					m_MoveTime;
	float					m_fmoveapl;
public:
	cMenu();
	~cMenu();

	void Next(int z);
public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
	void CALLBACK			OnEvent(UINT id, int xPos, int yPos);
	
	LRESULT CALLBACK		OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);

};

#endif