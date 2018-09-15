#ifndef	_KG_TEXTURE_CHUNK_H
#define	_KG_TEXTURE_CHUNK_H

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
#else
#endif

#ifndef	_KG_RECT_H
	#include "KGRect.h"
#endif


namespace KG
{


typedef struct _KGTextureChunk_tag
{
	KGRect					rcImage;
	KGRect					rcMap;
	KGRect					rcCollision;

#pragma warning(disable : 4251)
	D3DXVECTOR2				vCenter;
#pragma warning(default : 4251)

	IDirect3DTexture9*		pTexture;
	IDirect3DTexture9*		pRoot;

	_KGTextureChunk_tag()
	{
		rcImage				= KGRect(0, 0, 0, 0);
		rcMap				= KGRect(0, 0, 0, 0);
		rcCollision			= KGRect(0, 0, 0, 0);

		vCenter				= D3DXVECTOR2(0, 0);

		pTexture			= NULL;
		pRoot				= NULL;
	}

	~_KGTextureChunk_tag()
	{
		rcImage				= KGRect(0, 0, 0, 0);
		rcMap				= KGRect(0, 0, 0, 0);
		rcCollision			= KGRect(0, 0, 0, 0);

		vCenter				= D3DXVECTOR2(0, 0);

		SAFE_RELEASE(pTexture);

		pRoot				= NULL;
	}
} KGTextureChunk;


}


#endif