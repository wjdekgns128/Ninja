#ifndef	_KG_RENDER_TARGET_H
#define	_KG_RENDER_TARGET_H

#ifndef UNICODE
	#error "KG-Emotion requires a Unicode build. See the nearby comments for details"
#endif

#if defined(KG_DLL_EXPORTS)
	#define	_DECLSPEC		__declspec(dllexport)
#else
	#define	_DECLSPEC
#endif

#ifdef WIN32
	#define _WINSOCKAPI_
	#ifndef	_INC_WINDOWS
		#include <windows.h>
	#endif
	#undef _WINSOCKAPI_
	#ifndef _D3D9_H_
		#include <d3d9.h>
		#pragma comment(lib, "d3d9.lib")
	#endif
	#ifndef __D3DX9_H__
		#include <d3dx9.h>
		#if defined(DEBUG) || defined(_DEBUG)
			#pragma comment(lib, "d3dx9d.lib")
		#else
			#pragma comment(lib, "d3dx9.lib")
		#endif
	#endif
#else
#endif


#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_SPRITE_RENDER_H
	#include "KGSpriteRender.h"
#endif


namespace KG
{


class _DECLSPEC KGRenderTarget : protected KGSpriteRender
{
private:
	IDirect3DDevice9*		m_pd3dDevice;
	IDirect3DTexture9*		m_pTexture;
	IDirect3DSurface9*		m_pSurface;
	ID3DXRenderToSurface*	m_pRenderToSurface;

#pragma warning(disable : 4251)
	D3DXCOLOR				m_Color;
	D3DVIEWPORT9			m_Viewport;
#pragma warning(default : 4251)

	bool					m_Visible;

	CRITICAL_SECTION		m_csLock;

	KGRect					m_Canvas;
	KGRect					m_Screen;


public:
	KGRenderTarget(IDirect3DDevice9* pd3dDevice, D3DVIEWPORT9* pViewport = NULL);
	virtual ~KGRenderTarget();


public:
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);


public:
	HRESULT					BeginScene();
	HRESULT					EndScene();

	IMPLEMENT_GET_SET(D3DXCOLOR, Color);
	IMPLEMENT_GET_SET(bool, Visible);

	void					SetCanvas(const KGRect& rcCanvas);
	void					SetScreen(const KGRect& rcScreen);

	void					Entry(const KGRect& rcCanvas, const KGRect& rcScreen, D3DXCOLOR Color = D3DXCOLOR(1, 1, 1, 1), bool bVisible = true);
};


}


#endif
