#ifndef	_KG_TE_FILE_H
#define	_KG_TE_FILE_H

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


namespace KG
{


class _DECLSPEC KGTeFile
{
private:
	IDirect3DDevice9*		m_pd3dDevice;

	KGMapper*				m_pMapper;

	CRITICAL_SECTION		m_csLock;


public:
	KGTeFile(IDirect3DDevice9* pd3dDevice, KGMapper* pMapper);
	virtual ~KGTeFile();


public:
	void					Entry(const WCHAR* wsFileName);
	void					Entry(const WCHAR* wsFileName, bool bTexture);

	IMPLEMENT_PGET(IDirect3DDevice9*, d3dDevice);


protected:
	DWORD					log2(DWORD input);
};


}


#endif