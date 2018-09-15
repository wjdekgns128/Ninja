#ifndef	_KG_VIEWPORT_H
#define	_KG_VIEWPORT_H

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
#ifndef	_KG_RECT_H
	#include "KGRect.h"
#endif


namespace KG
{


class _DECLSPEC KGViewport
{
private:
	IDirect3DDevice9*		m_pd3dDevice;

	D3DVIEWPORT9			m_Viewport;
	D3DVIEWPORT9			m_ViewportOld;

	bool					m_isEmpty;


public:
	KGViewport(IDirect3DDevice9* pd3dDevice);
	virtual ~KGViewport();


public:
	HRESULT					BeginScene(KGRect& _rect);
	HRESULT					BeginScene(const D3DVIEWPORT9* pViewport);
	HRESULT					EndScene();

	void					SetViewport(KGRect& _rect);
	void					SetViewport(const D3DVIEWPORT9* pViewport);

	bool					empty();
};


}


#endif
