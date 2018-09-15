#ifndef	_KG_TEXTURE_H
#define	_KG_TEXTIRE_H

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
#ifndef	_KG_TEXTURE_CHUNK_H
	#include "KGTextureChunk.h"
#endif
#ifndef	_KG_OM_FILE_H
	#include "KGOmFile.h"
#endif
#ifndef	_KG_TE_FILE_H
	#include "KGTeFile.h"
#endif


namespace KG
{


class _DECLSPEC KGTexture : public KGOmFile, public KGTeFile
{
private:
	CRITICAL_SECTION		m_csLock;


protected:
	IDirect3DDevice9*		m_pd3dDevice;

	KGMapper				m_Table;


public:
	KGTexture(IDirect3DDevice9* pd3dDevice);
	virtual ~KGTexture();


public:
	void					Entry(const WCHAR* wsFileName);
	void					Entry(const WCHAR* wsFileName, bool bTexture);
	void					Entry(const WCHAR* wsName, const WCHAR* wsFileName, bool bCenter = false);

	KGTextureChunk*			Trans(const WCHAR* wsName);

	IMPLEMENT_PSET_PGET(IDirect3DDevice9*, d3dDevice);
};


}


#endif
