#ifndef	_KG_CURSOR_H
#define	_KG_CURSOR_H

#ifndef UNICODE
	#error "KG-Emotion requires a Unicode build. See the nearby comments for details"
#endif

#if defined(KG_DLL_EXPORTS)
	#define	_DECLSPEC		__declspec(dllexport)
#else
	#define	_DECLSPEC
#endif

#ifndef	_KG_SPRITE_H
	#include "KGSprite.h"
#endif
#ifndef	_KG_ANIMATE_H
	#include "KGAnimate.h"
#endif
#ifndef _KG_STRING_H
	#include "KGString.h"
#endif
#ifndef	_KG_RECT_H
	#include "KGRect.h"
#endif


namespace KG
{

#ifndef SAFE_ONFRAMEMOVE
	#define SAFE_ONFRAMEMOVE(p)		{if(p) {p->OnFrameMove(pd3dDevice, fTime, fElapsedTime, pUserContext);}}
#endif
#ifndef SAFE_ONFRAMERENDER
	#define SAFE_ONFRAMERENDER(p)	{if(p) {p->OnFrameRender(pd3dDevice, fTime, fElapsedTime, pUserContext);}}
#endif
#ifndef SAFE_ONKEYBOARD
	#define SAFE_ONKEYBOARD(p)		{if(p) {p->OnKeyboard(nChar, bKeyDown, bAltDown, pUserContext);}}
#endif
#ifndef SAFE_ONMOUSE
	#define SAFE_ONMOUSE(p)			{if(p) {p->OnMouse(bButtonDown, bLeftButtonDown, bRightButtonDown, bMiddleButtonDown, bSideButton1Down, bSideButton2Down, nMouseWheelDelta, xPos, yPos, pUserContext);}}
#endif
#ifndef	SAFE_ONRESETDEVICE
	#define	SAFE_ONRESETDEVICE(p)	{if(p) {p->OnResetDevice(pd3dDevice, pBackBufferSurfaceDesc, pUserContext);}}
#endif
#ifndef	SAFE_ONLOSTDEVICE
	#define	SAFE_ONLOSTDEVICE(p)	{if(p) {p->OnLostDevice(pUserContext);}}
#endif
#ifndef	SAFE_ONRESETDEVICE_0
#define	SAFE_ONRESETDEVICE_0(p)		{if(p) {p->OnResetDevice();}}
#endif
#ifndef	SAFE_ONLOSTDEVICE_0
	#define	SAFE_ONLOSTDEVICE_0(p)	{if(p) {p->OnLostDevice();}}
#endif


class _DECLSPEC KGCursor
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGRenderSingle*			m_pRender;

	KGString				m_wsRender;
	KGString				m_wsDefault;
	KGString				m_wsLeftButtonDown;
	KGString				m_wsRightButtonDown;
	KGString				m_wsMiddleButtonDown;
	KGString				m_wsSideButton1Down;
	KGString				m_wsSideButton2Down;
	KGString				m_wsName;

	KGRect					m_rcRect;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_vPos;
	D3DXCOLOR				m_Color;
#pragma warning(default : 4251)

	bool					m_Visible;
	bool					m_Disable;

	CRITICAL_SECTION		m_csLock;


public:
	KGCursor(KGSprite* pSprite);
	KGCursor(KGAnimate* pAnimate);
	virtual ~KGCursor();


public:
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);


public:
	void					Entry(KGRect& rcRect, const WCHAR* wsDefault, const WCHAR* wsLeftButtonDown = NULL, const WCHAR* wsRightButtonDown = NULL,
								  const WCHAR* wsMiddleButtonDown = NULL, const WCHAR* wsSideButton1Down = NULL, const WCHAR* wsSideButton2Down = NULL);

	IMPLEMENT_SET_GET(bool, Visible);
	IMPLEMENT_SET_GET(bool, Disable);

	void					SetSprite(const WCHAR* wsName, D3DXCOLOR& Color);
};


}


#endif
