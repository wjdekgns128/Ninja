#ifndef	_KG_3D_OBJECT_CHUNK_H
#define	_KG_3D_OBJECT_CHUNK_H

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



#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_STRING_H
	#include "KGString.h"
#endif
#ifndef	_KG_RESPONSE_H
	#include "KGResponse.h"
#endif


namespace KG
{
	namespace _3D
	{


typedef struct _CALLBACK_DATA_tag
{
	int						index;
} _CALLBACK_DATA;


class _DECLSPEC KG3DObjectChunk : public ID3DXAnimationCallbackHandler
{
protected:
	UINT					m_Type;

	float					m_ActionTime;

	bool					m_AnimationFinsh;
	bool					m_Action;

	KGResponseObject*		m_pResponse;


public:
	_CALLBACK_DATA*			m_pCallbackData;


public:
	KG3DObjectChunk()		{m_ActionTime = 0.f; m_Type = 0; m_pResponse = NULL; m_Action = false; m_AnimationFinsh = false; m_pCallbackData = NULL;}
	virtual ~KG3DObjectChunk()	{SAFE_DELETE_ARRAY(m_pCallbackData);}


public:
	bool					GetAnimationFinsh()					{return m_AnimationFinsh;}
	void					SetAnimationFinsh(bool bAnimationFinsh)	{m_AnimationFinsh = bAnimationFinsh;}
	void					SetResponse(KGResponseObject* pResponse) {m_pResponse = pResponse;}
	
	IMPLEMENT_GET_SET_NOLOCK(float, ActionTime);


public:
	virtual bool			Entry(const WCHAR* wsFileName)		{return true;}

	virtual void			SetAnimationSet(UINT index)			{}
	virtual void			SetAnimationSet(UINT index, bool bReset)	{}
	virtual void			NextAnimation()						{}

	virtual D3DXVECTOR3		GetInitialCameraPosition() 			{return D3DXVECTOR3(0, 0, 0);}

	virtual KGString		GetAnimationSetName(UINT index)		{return KGString(L"Error: virtual function");}

	IMPLEMENT_VSET_VGET(UINT, CurrentAnimationSet);
	IMPLEMENT_VSET_VGET(float, SpeedAdjust);
	IMPLEMENT_VSET_VGET(float, ElapsedTime);
	IMPLEMENT_VGET(double, Period);
	IMPLEMENT_VGET(ID3DXAnimationController*, AnimationController);

	virtual D3DXVECTOR3		GetSphereCenter()					{return D3DXVECTOR3(0, 0, 0);}


public:
	virtual KG3DObjectChunk*	Clone()								= 0;
	virtual void			Clone(KG3DObjectChunk** ppObjectChunk)	= 0;


public:
	virtual void			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)		{}
	virtual void 			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)	{}


public:
	UINT					GetType()	{return m_Type;}

	HRESULT CALLBACK HandleCallback(UINT Track, LPVOID pCallbackData)
	{
		_CALLBACK_DATA*		pData	= (_CALLBACK_DATA*)pCallbackData;

		if(pData == NULL)
			return S_OK;

		if(GetElapsedTime() > m_ActionTime)
		{
			if(m_Action == false)
			{
				if(m_pResponse)
					m_pResponse->OnObjectAction(pData->index, pData);

				m_Action	= true;
			}
		}

		if(GetElapsedTime() > (float)GetPeriod())
		{
			if(m_pResponse)
				m_pResponse->OnObjectFinish(pData->index, pData);

			m_AnimationFinsh= true;
			m_Action		= false;

			SetElapsedTime(GetElapsedTime() - (float)GetPeriod());
		}
		return S_OK;
	}
};


	}
}


#endif
