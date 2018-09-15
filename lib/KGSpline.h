#ifndef	_KG_SPLINE_H
#define	_KG_SPLINE_H

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


#ifndef	_KG_MAPPER_H
	#include "KGMapper.h"
#endif
#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_SPL_FILE_H
	#include "KGSplFile.h"
#endif
#ifndef	_KG_SPLINE_CHUNK_H
	#include "KGSplineChunk.h"
#endif


namespace KG
{


class _DECLSPEC KGSpline : public KGSplFile
{
private:
	CRITICAL_SECTION		m_csLock;


protected:
	KGMapper				m_Table;


public:
	KGSpline(const WCHAR* wsFileName = NULL, WORD _type = 0x2010, WORD _version = 0x0001);
	virtual ~KGSpline();


public:
	void					Entry(const WCHAR* wsFileName, WORD _type = 0x2010, WORD _version = 0x0001);

	KGSplineChunk*			Trans(const WCHAR* wsName);

	KG::_3D::KG3DSpline*	GetSpline(const WCHAR* wsName);

	float					GetTime(const WCHAR* wsName);
};


}


#endif