#ifndef	_KG_3D_TYPE_H
#define	_KG_3D_TYPE_H

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


namespace KG
{
	namespace _3D
	{


typedef struct _KG3DMESHCONTAINER_tag : public D3DXMESHCONTAINER
{
    IDirect3DTexture9**		ppTextures;
	D3DMATERIAL9*			pMaterials;

	ID3DXMesh*				pSkinMesh;
	D3DXMATRIXA16*			pBoneOffsets;
	D3DXMATRIXA16**			ppFrameCombinedMatrixPointer;
} KG3DMESHCONTAINER;


typedef struct _KG3DFRAME_tag : public D3DXFRAME
{
    D3DXMATRIXA16			CombinedTransformationMatrix;
} KG3DFRAME;


	}
}



#endif