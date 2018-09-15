#ifndef	_KG_3D_X_FILE_H
#define	_KG_3D_X_FILE_H

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



#ifndef	_KG_3D_TYPE_H
	#include "KG3DType.h"
#endif
#ifndef	_KG_3D_OBJECT_CHUNK_H
	#include "KG3DObjectChunk.h"
#endif
#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_STRING_H
	#include "KGString.h"
#endif


namespace KG
{
	namespace _3D
	{


class _DECLSPEC KG3DXFile : public KG3DObjectChunk
{
private:
	LPDIRECT3DDEVICE9		m_pd3dDevice;

	LPD3DXFRAME				m_pd3dFrame;
	LPD3DXANIMATIONCONTROLLER	m_pd3dAnimationController;

	KG3DMESHCONTAINER*		m_pMeshContainer;

	D3DXMATRIXA16*			m_pBoneMatrices;

	int						m_MaxBones;

	UINT					m_CurrentAnimationSet;
	UINT					m_NumAnimationSets;
	UINT					m_CurrentTrack;

	float					m_CurrentTime;
	float					m_SpeedAdjust;
	float					m_SphereRadius;
	float					m_ElapsedTime;

	double					m_Period;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_SphereCenter;
#pragma warning(default : 4251)


public:
	KG3DXFile(LPDIRECT3DDEVICE9 pd3dDevice);
	virtual ~KG3DXFile();


private:
	void					SetupCallbackKeyFrames();
	void					UpdateFrameMatrices(const D3DXFRAME* pd3dFrame, const D3DXMATRIXA16* pMatrix);
	void					DrawFrame(LPD3DXFRAME pd3dFrame) const;
	void					DrawMeshContainer(LPD3DXMESHCONTAINER pd3dMeshContainer, LPD3DXFRAME pd3dFrame) const;
	void					SetupBoneMatrices(KG3DFRAME* pFrame, LPD3DXMATRIX pMatrix);
	void					CloneFrameHierarchy(LPD3DXFRAME pFrameSrc, LPD3DXFRAME* ppFrameDest) const;
	void					CloneMeshContainer(LPD3DXMESHCONTAINER pMeshContainerSrc, LPD3DXMESHCONTAINER* ppMeshContainerDest) const;

HRESULT AddCallbackKeysAndCompress( LPD3DXANIMATIONCONTROLLER pAC,
                                           LPD3DXKEYFRAMEDANIMATIONSET pAS,
                                           DWORD dwNumCallbackKeys,
                                           D3DXKEY_CALLBACK aKeys[],
                                           DWORD dwCompressionFlags,
                                           FLOAT fCompression );


public:
	bool					Entry(const WCHAR* wsFileName);

	void					SetAnimationSet(UINT index);
	void					SetAnimationSet(UINT index, bool bReset);
	void					NextAnimation();

	D3DXVECTOR3				GetInitialCameraPosition();

	KGString				GetAnimationSetName(UINT index);

	ID3DXAnimationController*	GetAnimationController()	{return m_pd3dAnimationController;};

	IMPLEMENT_GET_SET_NOLOCK(UINT, CurrentAnimationSet);
	IMPLEMENT_GET_SET_NOLOCK(float, SpeedAdjust);
	IMPLEMENT_GET_NOLOCK(double, Period);
	IMPLEMENT_GET_SET_NOLOCK(float, ElapsedTime);
	IMPLEMENT_GET_NOLOCK(D3DXVECTOR3, SphereCenter);


public:
	KG3DObjectChunk*		Clone();

	KG3DXFile&				operator = (const KG3DXFile& _xFile);

	void					Clone(KG3DObjectChunk** ppObjectChunk);


public:
	void					OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void 					OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
};


	}
}


#endif