#ifndef	_KG_SQUEUE_H
#define	_KG_SQUEUE_H


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


namespace KG
{


class KGSNODE
{
private:
	BYTE*					m_pData;

	int						m_size;
	int						m_max;


public:
	KGSNODE*				pNext;


public:
	KGSNODE(int queueSize = 1024);
	virtual ~KGSNODE();


public:
	void					reset();
	void					push(BYTE* pData, int size);

	int						pop(BYTE* pData);
};


class KGSQUEUE
{
private:
	int						m_max;
	int						m_size;
	int						m_depth;

	KGSNODE**				m_ppHead;
	KGSNODE**				m_ppTail;
	KGSNODE*				m_pHead;
	KGSNODE*				m_pTail;

	CRITICAL_SECTION		m_csLock;


public:
	KGSQUEUE(int size = 1024);
	virtual ~KGSQUEUE();


public:
	int						push(BYTE* pData, int size);
	int						pop(BYTE* pData);
	int						getPushDepth();
	int						getPopDepth();
	int						size();
	int						depth();

	bool					empty();

	void					clear();
};


}


#endif