#ifndef	_KG_KALMAN_H
#define	_KG_KALMAN_H

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
#else
#endif


namespace KG
{


class _DECLSPEC KGKalman
{
private:
	double					m_fx;
	double					m_fsd;


public:
	KGKalman(double fx = 0.f, double fsd = 0.f);
	virtual ~KGKalman();


public:
	double					Normal(double fx, double fsd);
};


}


#endif
