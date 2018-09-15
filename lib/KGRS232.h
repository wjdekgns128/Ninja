#ifndef	_KG_RS232_H
#define	_KG_RS232_H


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
#endif

#ifndef	_KG_SQUEUE_H
	#include "KGSQueue.h"
#endif
#ifndef	_KG_RESPONSE_H
	#include "KGResponse.h"
#endif


namespace KG
{


#define	RS232_BUFFER_SIZE	4096


class _DECLSPEC KGRS232
{
private:
	WCHAR					m_wsPortName[32];

	HANDLE					m_hHandle;
	HANDLE					m_hRecv;
	HANDLE					m_hSend;

	OVERLAPPED				m_osRead;
	OVERLAPPED				m_osWrite;

	volatile bool			m_bConnected;

	KGSQUEUE*				m_pRecvQ;
	KGSQUEUE*				m_pSendQ;

	KG::KGResponseClass*	m_Response;

	CRITICAL_SECTION		m_csLock;


public:
	KGRS232(KG::KGResponseClass* pResponse = NULL);
	virtual ~KGRS232();


public:
	void					Close();

	bool					Open(const WCHAR* wsPortName = L"COM1", DWORD dwBaud = CBR_9600, BYTE bySize = 8, BYTE byStop = ONESTOPBIT, BYTE byParity = NOPARITY);

	int						recv(BYTE* pData);
	int						send(BYTE* pData, int Size);


protected:
	DWORD					Write(BYTE* pData, DWORD nToWrite);
	DWORD					Read(BYTE* pData, DWORD nToRead);


public:
	static DWORD			pRecv(KGRS232* pThis);
	static DWORD			pSend(KGRS232* pThis);

	IMPLEMENT_SET_GET(KG::KGResponseClass*, Response);
};


}


#endif
