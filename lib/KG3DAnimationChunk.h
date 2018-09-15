#ifndef	_KG_3D_ANIMATION_CHUNK_H
#define	_KG_3D_ANIMATION_CHUNK_H

#ifndef UNICODE
	#error "KG-Emotion requires a Unicode build. See the nearby comments for details"
#endif

#if defined(KG_DLL_EXPORTS)
	#define	_DECLSPEC		__declspec(dllexport)
#else
	#define	_DECLSPEC
#endif

#ifdef WIN32
	#ifndef WINVER
		#define WINVER			0x0410
	#endif
	#ifndef _WIN32_WINDOWS
		#define _WIN32_WINDOWS	0x0410 
	#endif
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT	0x0500 
	#endif
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
#endif


#ifndef	_KG_3D_CAMERA_H
	#include "KG3DCamera.h"
#endif
#ifndef	_KG_3D_OBJECT_CHUNK_H
	#include "KG3DObjectChunk.h"
#endif
#ifndef	_KG_TYPE_H
	#include "KGType.h"
#endif
#ifndef	_KG_VIEWPORT_H
	#include "KGViewport.h"
#endif


namespace KG
{
	namespace _3D
	{


class _DECLSPEC KG3DAnimationChunk
{
private:
	IDirect3DDevice9*		m_pd3dDevice;


public:
	KG3DCamera*				m_pCamera;
	KG3DObjectChunk*		m_pObject;
	KGViewport*				m_pViewport;
	KGResponseObject*		m_pResponse;

	bool					m_Play;
	bool					m_Show;

	int						m_Loop;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_Position;
#pragma warning(default : 4251)


public:
	KG3DAnimationChunk(IDirect3DDevice9* pd3dDevice);
	KG3DAnimationChunk(const KG3DAnimationChunk& _scene);
	~KG3DAnimationChunk();


public:
	KG3DAnimationChunk& operator = (const KG3DAnimationChunk& _scene);
	KG3DAnimationChunk& operator = (const KG3DObjectChunk& _object);


public:
	int						OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);


public:
	IMPLEMENT_SET_GET_NOLOCK(D3DXVECTOR3, Position);
	IMPLEMENT_SET_GET_NOLOCK(bool, Play);
	IMPLEMENT_SET_GET_NOLOCK(bool, Show);
};


	}
}


#endif

