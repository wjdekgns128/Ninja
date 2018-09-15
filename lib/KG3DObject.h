#ifndef	_KG_3D_OBJECT_H
#define	_KG_3D_OBJECT_H

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
#endif


#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_MAPPER_H
	#include "KGMapper.h"
#endif
#ifndef	_KG_3D_X_FILE_H
	#include "KG3DXFile.h"
#endif


namespace KG
{
	namespace _3D
	{


class _DECLSPEC KG3DObject
{
private:
	CRITICAL_SECTION		m_csLock;


protected:
	IDirect3DDevice9*		m_pd3dDevice;

	KGMapper				m_Table;


public:
	KG3DObject(IDirect3DDevice9* pd3dDevice);
	virtual ~KG3DObject();


public:
	void					Entry(const WCHAR* wsName, const WCHAR* wsFileName);

	KG3DObjectChunk*		Trans(const WCHAR* wsName);

	IMPLEMENT_PSET_PGET(IDirect3DDevice9*, d3dDevice);
};


	}
}


#endif

