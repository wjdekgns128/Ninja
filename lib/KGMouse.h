#ifndef	_KG_MOUSE_H
#define	_KG_MOUSE_H

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
#else
#endif

#ifndef _KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef _KG_RESPONSE_H
	#include "KGResponse.h"
#endif


namespace KG
{


class _DECLSPEC KGMouse
{
private:
	CRITICAL_SECTION		m_csLock;


protected:
	bool*					m_pMouseButtons;


public:
	IMPLEMENT_PSET_PGET(bool*, MouseButtons);


public:
	KGMouse();
	virtual ~KGMouse();
};


}


#endif

