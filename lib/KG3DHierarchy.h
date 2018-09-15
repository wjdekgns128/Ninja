#ifndef	_KG_3D_HIERARCHY_H
#define	_KG_3D_HIERARCHY_H

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

#ifndef	_KG_STRING_H
	#include "KGString.h"
#endif
#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_3D_TYPE_H
	#include "KG3DType.h"
#endif


namespace KG
{
	namespace _3D
	{


class _DECLSPEC KG3DHierarchy : public ID3DXAllocateHierarchy
{
private:
	KGString				m_PathName;


public:
    // callback to create a D3DXFRAME extended object and initialize it
    STDMETHOD(CreateFrame)(LPCSTR Name, LPD3DXFRAME* ppFrame);

    // callback to create a D3DXMESHCONTAINER extended object and initialize it
    STDMETHOD(CreateMeshContainer)(LPCSTR Name, CONST D3DXMESHDATA* meshData, 
                            CONST D3DXMATERIAL* materials, CONST D3DXEFFECTINSTANCE* effectInstances,
                            DWORD numMaterials, CONST DWORD* adjacency, LPD3DXSKININFO pSkinInfo, 
                            LPD3DXMESHCONTAINER* ppMeshContainer);

    // callback to release a D3DXFRAME extended object
    STDMETHOD(DestroyFrame)(LPD3DXFRAME frameToFree);

    // callback to release a D3DXMESHCONTAINER extended object
    STDMETHOD(DestroyMeshContainer)(LPD3DXMESHCONTAINER meshContainerToFree);


public:
	void					SetPathName(const WCHAR* pPathName);
};


	}
}


#endif

