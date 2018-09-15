#ifndef	_KG_SPRITE_H
#define	_KG_SPRITE_H

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
	#ifndef _DXERR9_H_
		#include <dxerr9.h>
		#pragma comment(lib, "dxerr9.lib")
	#endif
#else
#endif

#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_MAPPER_H
	#include "KGMapper.h"
#endif
#ifndef	_KG_RECT_H
	#include "KGRect.h"
#endif
#ifndef	_KG_STRING_H
	#include "KGString.h"
#endif
#ifndef	_KG_TEXTURE_H
	#include "KGTexture.h"
#endif
#ifndef	_KG_KALMAN_H
	#include "KGKalman.h"
#endif
#ifndef	_KG_TYPE_H
	#include "KGType.h"
#endif
#ifndef	_KG_SPRITE_RENDER_H
	#include "KGSpriteRender.h"
#endif


namespace KG
{


class _DECLSPEC KGSprite : public KGTexture, public KGSpriteRender
{
private:
	KGKalman				m_KmLeft;
	KGKalman				m_KmRight;
	KGKalman				m_KmTop;
	KGKalman				m_KmBottom;

	CRITICAL_SECTION		m_csLock;


public:
	KGSprite(IDirect3DDevice9* pd3dDevice);
	virtual ~KGSprite();


public:
	void					Render(IDirect3DTexture9* pTexture, D3DXVECTOR3& vPos, D3DXCOLOR& Color);


public:
	KGTextureChunk*			Render(const WCHAR* wsName, D3DXVECTOR3& vPos, D3DXCOLOR& Color, DWORD MirrorType = KG_MIRROR_NONE);
	KGTextureChunk*			Render(const WCHAR* wsName, D3DXVECTOR3& vPos, float fAngle, D3DXCOLOR& Color, DWORD MirrorType = KG_MIRROR_NONE);
	KGTextureChunk*			Render(const WCHAR* wsName, KGRect& d3dRect, D3DXCOLOR& Color, DWORD MirrorType = KG_MIRROR_NONE);
	KGTextureChunk*			Render(const WCHAR* wsName, KGRect& d3dRect, float fAngle, D3DXCOLOR& Color, DWORD MirrorType = KG_MIRROR_NONE);
	KGTextureChunk*			Render(const WCHAR* wsName, D3DXVECTOR3& vPos, D3DXVECTOR3& vAxis, float fAngle, D3DXCOLOR& Color, DWORD MirrorType = KG_MIRROR_NONE);
	KGTextureChunk*			Render(const WCHAR* wsName, KGRect& d3dRect, D3DXVECTOR3& vAxis, float fAngle, D3DXCOLOR& Color, DWORD MirrorType = KG_MIRROR_NONE);

	KGTextureChunk*			RenderLerp(const WCHAR* wsName, D3DXVECTOR3& vPos, D3DXCOLOR& Color, float fTime, DWORD LerpType = KG_LERP_RIGHT);
};


}


#endif
