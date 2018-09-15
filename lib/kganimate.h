#ifndef	_KG_ANIMATE_H
#define	_KG_ANIMATE_H

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
#ifndef	_KG_TYPE_H
	#include "KGType.h"
#endif
#ifndef	_KG_VECTOR_H
	#include "KGVector.h"
#endif
#ifndef	_KG_SPRITE_H
	#include "KGSprite.h"
#endif
#ifndef _KG_ANIMATE_CHUNK_H
	#include "KGAnimateChunk.h"
#endif
#ifndef	_KG_AM_FILE_H
	#include "KGAmFile.h"
#endif
#ifndef	_KG_TA_FILE_H
	#include "KGTaFile.h"
#endif


namespace KG
{


class _DECLSPEC KGAnimate : public KGAmFile, public KGTaFile
{
private:
	KGSprite*				m_pSprite;

	CRITICAL_SECTION		m_csLock;


protected:
	KGMapper				m_Table;


public:
	KGAnimate(KGSprite* pSprite);
	~KGAnimate();


public:
	void					Entry(const WCHAR* wsFileName);

	KGAnimateScene*			Trans(const WCHAR* wsName);
	
	IMPLEMENT_PGET(KGSprite*, Sprite);
};


class _DECLSPEC KGRenderMulti
{
private:
	KGAnimate*				m_pAnimate;

	KGVector				m_Table;

	CRITICAL_SECTION		m_csLock;


public:
	KGRenderMulti(KGAnimate* pAnimate);
	~KGRenderMulti();


public:
	void					clear();
	void					OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);

	bool					Entry(const WCHAR* wsName, const D3DXVECTOR3& vPos, bool bPlay = true, int iLoop = -1);
	bool					empty();
};


class _DECLSPEC KGRenderSingle
{
private:
	KGAnimate*				m_pAnimate;

	KGAnimateScene*			m_pAmScene;

	KGString				m_wsName;

	CRITICAL_SECTION		m_csLock;


public:
	KGRenderSingle(KGAnimate* pAnimate);
	~KGRenderSingle();


public:
	void					clear();
	void					SetMove(D3DXVECTOR3& vPos);
	void					SetScale(float fScale);
	void					SetAngle(float fAngel);
	void					OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);

	bool					Entry(const WCHAR* wsName, const D3DXVECTOR3& vPos, bool bPlay = true, int iLoop = -1, bool bReset = true);
	bool					empty();
};


}


#endif

