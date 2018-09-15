#ifndef	_KG_3D_ANIMATION_H
#define	_KG_3D_ANIMATION_H

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


#ifndef	_KG_3D_ANIMATION_CHUNK_H
	#include "KG3DAnimationChunk.h"
#endif
#ifndef	_KG_3D_OBJECT_H
	#include "KG3DObject.h"
#endif
#ifndef	_KG_VECTOR_H
	#include "KGVector.h"
#endif
#ifndef	_KG_VIEWPORT_H
	#include "KGViewport.h"
#endif


namespace KG
{
	namespace _3D
	{


class _DECLSPEC KG3DRenderMulti
{
private:
	IDirect3DDevice9*		m_pd3dDevice;

	KG3DObject*				m_pObject;

	KGMapper				m_Table;

	CRITICAL_SECTION		m_csLock;


public:
	KG3DRenderMulti(KG3DObject* pObject);
	~KG3DRenderMulti();


public:
	IMPLEMENT_PGET(IDirect3DDevice9*, d3dDevice);

	KG3DObjectChunk*		GetObject(const WCHAR* wsName);
	KG3DCamera*				GetCamera(const WCHAR* wsName);


public:
	void					SetViewport(const WCHAR* wsName, const KGRect& _rect);
	void					clear();
	void					erase(const WCHAR* wsName);
	void					OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);

	bool					Entry(const WCHAR* wsName, const WCHAR* wsNameObject, const D3DXVECTOR3& vPos,
								  const KGRect& _rect = KGRect(0, 0, 0, 0), UINT Index = 0, bool bReset = true, bool bPlay = true, int Loop = -1);
	bool					empty();
};


class _DECLSPEC KG3DRenderSingle
{
private:
	IDirect3DDevice9*		m_pd3dDevice;

	KG3DObject*				m_pObject;
	KGResponseObject*		m_pResponse;

	KG3DAnimationChunk*		m_pAnimationChunk;

	float					m_ActionTime;

	CRITICAL_SECTION		m_csLock;


public:
	KG3DRenderSingle(KG3DObject* pObject, KGResponseObject* pResponse = NULL);
	~KG3DRenderSingle();


public:
	IMPLEMENT_PGET(IDirect3DDevice9*, d3dDevice);

	KG3DObjectChunk*		GetObject();
	KG3DCamera*				GetCamera();


private:
	D3DXVECTOR3				Convert2dTo3d_NoLock(D3DXVECTOR3 vPos);


public:
	void					clear();
	void					OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);

	bool					Entry(const WCHAR* wsName, const D3DXVECTOR3& vPos, const KGRect& _rect = KGRect(0, 0, 0, 0), UINT Index = 0, bool bReset = true, bool bPlay = true, int Loop = -1);
	bool					empty();

	D3DXVECTOR3				GetPosition();

	void					SetPosition(D3DXVECTOR3 vPos);
	void					SetViewport(const KGRect& _rect);
	void					SetResponse(KGResponseObject* pResponse);
	void					SetActionTime(float fTime);
	void					SetPlay(bool bPlay);
};


	}
}


#endif

