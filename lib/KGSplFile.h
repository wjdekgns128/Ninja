#ifndef	_KG_SPL_FILE_H
#define	_KG_SPL_FILE_H

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


namespace KG
{


class _DECLSPEC KGSplFile
{
private:
	KGMapper*				m_pMapper;

	CRITICAL_SECTION		m_csLock;


public:
	KGSplFile(KGMapper* pMapper);
	virtual ~KGSplFile();


public:
	void					Entry(const WCHAR* wsFileName, WORD _type = 0x2010, WORD _version = 0x0001);
};


}


#endif
