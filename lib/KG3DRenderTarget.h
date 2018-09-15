#ifndef	_KG_3D_RENDER_TARGET_H
#define	_KG_3D_RENDER_TARGET_H

#ifndef UNICODE
	#error "KG-Emotion requires a Unicode build. See the nearby comments for details"
#endif

#if defined(KG_DLL_EXPORTS)
	#define	_DECLSPEC		__declspec(dllexport)
#else
	#define	_DECLSPEC
#endif

#ifdef WIN32
	#ifndef	_INC_WINDOWS
		#include <windows.h>
	#endif
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
#ifndef	_KG_3D_OBJECT_H
	#include "KG3DObject.h"
#endif
#ifndef	_KG_3D_OBJECT_CHUNK_H
	#include "KG3DObjectChunk.h"
#endif


namespace KG
{
	namespace _3D
	{


class _DECLSPEC KG3DRenderTarget
{
private:
	IDirect3DDevice9*		m_pd3dDevice;
	IDirect3DTexture9*		m_pTexture;
	IDirect3DSurface9*		m_pSurface;
	ID3DXRenderToSurface*	m_pRenderToSurface;

	KG3DObject*				m_pObject;

	CRITICAL_SECTION		m_csLock;


public:
	KG3DRenderTarget(KG3DObject* pObject);
	virtual ~KG3DRenderTarget();


public:
	IMPLEMENT_PGET(IDirect3DDevice9*, d3dDevice);


public:
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
};


	}
}


#endif
