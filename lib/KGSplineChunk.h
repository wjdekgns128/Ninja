#ifndef	_KG_SPLINE_CHUNK_H
#define	_KG_SPLINE_CHUNK_H

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
#else
#endif


#ifndef	_KG_3D_SPLINE_H
	#include "KG3DSpline.h"
#endif


namespace KG
{


typedef struct _KGSplineChunk_tag
{
	float					fTime;

	KG::_3D::KG3DSpline		Spline;

	_KGSplineChunk_tag()
	{
		fTime				= 0.f;
	}
} KGSplineChunk;


}


#endif

