#ifndef	_KG_ANIMATE_CHUNK_H
#define	_KG_ANIMATE_CHUNK_H

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
#ifndef	_KG_TYPE_H
	#include "KGType.h"
#endif
#ifndef	_KG_VECTOR_H
	#include "KGVector.h"
#endif
#ifndef	_KG_SPRITE_H
	#include "KGSprite.h"
#endif


namespace KG
{


class KGAnimateChunk
{
private:
	KGSprite*				m_pSprite;


public:
	D3DXVECTOR3				vAbsolute;
	D3DXVECTOR3				vRelative;

	KGString				wsName;

	D3DXCOLOR				fColor;
	
	KGRect					rcRect;

	float					fTime;


public:
	KGAnimateChunk(KGSprite* pSprite);
	~KGAnimateChunk();


public:
	void					Render(D3DXVECTOR3& vPos, float fScale, float fAngle);
};


class _DECLSPEC KGAnimateScene
{
private:
	KGSprite*				m_pSprite;


public:
	KGVector				Table;
	KGVector*				pTable;

#pragma warning(disable : 4251)
	D3DXVECTOR3				vPos;
	D3DXVECTOR3				vPos0;
	D3DXVECTOR3				vSavePos;
	D3DXVECTOR3				vTranslate;
#pragma warning(default : 4251)

	float					fTime;
	float					fScale;
	float					fAngle;

	bool					bPlay;
	bool					bShow;

	int						nFrame;
	int						nLoop;


public:
	KGAnimateScene(KGSprite* pSprite, const D3DXVECTOR3& _vPos);
	~KGAnimateScene();

	KGAnimateScene& operator = (const KGAnimateScene& _scene);


public:
	int						OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
};


}


#endif