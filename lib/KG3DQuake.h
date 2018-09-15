#ifndef	_KG_QUAKE_H
#define	_KG_QUAKE_H


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
#ifndef	_KG_VECTOR_H
	#include "KGVector.h"
#endif
#ifndef	_KG_3D_SPLINE_H
	#include "KG3DSpline.h"
#endif


namespace KG
{
	namespace _3D
	{



class _DECLSPEC KG3DQuake : public KG3DSpline
{
private:
	bool					m_Action;

	float					m_Time;


public:
	KG3DQuake();
	virtual ~KG3DQuake();


public:
	D3DXVECTOR3				GetPosition();


public:
	IMPLEMENT_SET_GET_NOLOCK(bool, Action);
	IMPLEMENT_GET_NOLOCK(float, Time);

	void					SetTime(float fElapsedTime);
};


	}
}


#endif
