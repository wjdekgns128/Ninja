#ifndef	_KG_THREAD_H
#define	_KG_THREAD_H


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
	#ifndef _DXERR9_H_
		#include <dxerr9.h>
		#pragma comment(lib, "dxerr9.lib")
	#endif
#else
#endif

#ifndef	_KG_TYPE_H
	#include "KGType.h"
#endif
#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_RESPONSE_H
	#include "KGResponse.h"
#endif


namespace KG
{


class _DECLSPEC KGThread
{
private:
	void*					m_pUserContext;

	HANDLE					m_hThread;

	UINT					m_Pos;
	UINT					m_Limit;

	bool					m_Finish;

	CRITICAL_SECTION		m_csLock;


public:
	KGThread();
	virtual ~KGThread();


protected:
	static int WINAPI		pThread(void* pUserContext);


protected:
	virtual void CALLBACK	OnThread(void* pUserContext)			{};
	virtual void CALLBACK	OnThreadFinish(void* pUserContext)		{};


protected:
	void					SetStart(void* pUserContext);
	void					SetPos(HWND hWnd, UINT Pos, UINT Limit);

	IMPLEMENT_SET_GET(bool, Finish);
};


}



#endif

