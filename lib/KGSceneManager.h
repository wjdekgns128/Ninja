#ifndef	_KG_SCENE_MANAGER_H
#define	_KG_SCENE_MANAGER_H

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
#endif

#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_MAPPER_H
	#include "KGMapper.h"
#endif
#ifndef	_KG_SCENE_H
	#include "KGScene.h"
#endif
#ifndef	_KG_STRING_H
	#include "KGString.h"
#endif


namespace KG
{


class _DECLSPEC KGSceneManager
{
private:
	KGMapper				m_Table;

	KGScene*				m_pCurrent;
	KGScene*				m_pCur;

	KGString				m_szName;

	CRITICAL_SECTION		m_csLock;


public:
	KGSceneManager();
	~KGSceneManager();


public:
	void					Entry(const WCHAR* szName, KGScene* pScene);
	void					Dispatcher(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void					Trans(const WCHAR* szName);

	IMPLEMENT_PGET(KGScene*, Current);
};


}


#endif