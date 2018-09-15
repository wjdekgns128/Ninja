#ifndef	_KG_MISC_H
#define	_KG_MISC_H

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
	#ifndef _XINPUT_H_
		#include <xinput.h>
	#endif
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


namespace KG
{


#undef FALSE
#undef TRUE
#undef NULL

#define FALSE   0
#define TRUE    1
#define NULL    0

#ifndef SAFE_DELETE
	#define SAFE_DELETE(p)			{if(p) {delete (p);     (p)=NULL;}}
#endif    
#ifndef SAFE_DELETE_ARRAY
	#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p);   (p)=NULL;}}
#endif    
#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(p)			{if(p) {(p)->Release(); (p)=NULL;}}
#endif
#ifndef MIN
	#undef min
	#define MIN(a, b)		((a) < (b) ? (a) : (b))
#endif
#ifndef	MAX
	#undef max
	#define MAX(a, b)		((a) > (b) ? (a) : (b))
#endif

#define KG_MAX_CONTROLLERS	4

extern "C++" _DECLSPEC void	KGOutputDebugStringW(LPCWSTR strMsg, ...);
extern "C++" _DECLSPEC void	KGOutputDebugStringA(LPCSTR strMsg, ...);
extern "C++" _DECLSPEC HRESULT	KGTrace(const CHAR* strFile, DWORD dwLine, HRESULT hr, const WCHAR* strMsg, bool bPopMsgBox);


#ifdef UNICODE
	#define KGOutputDebugString KGOutputDebugStringW
#else
	#define KGOutputDebugString KGOutputDebugStringA
#endif


#if defined(DEBUG) || defined(_DEBUG)
	#define KG_ERR(str,hr)			KGTrace( __FILE__, (DWORD)__LINE__, hr, str, false )
	#define KG_ERR_MSGBOX(str,hr)	KGTrace( __FILE__, (DWORD)__LINE__, hr, str, true )
	#define KGTRACE					KGOutputDebugString
#else
	#define KG_ERR(str,hr)			(hr)
	#define KG_ERR_MSGBOX(str,hr)	(hr)
	#define KGTRACE					(__noop)
#endif

#if defined(DEBUG) || defined(_DEBUG)
	#ifndef V
		#define V(x)        { hr = x; if( FAILED(hr) ) { KG::KGTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true ); } }
	#endif
	#ifndef V_RETURN
		#define V_RETURN(x) { hr = x; if( FAILED(hr) ) { return KG::KGTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true ); } }
	#endif
#else
	#ifndef V
		#define V(x)        { hr = x; }
	#endif
	#ifndef V_RETURN
		#define V_RETURN(x) { hr = x; if( FAILED(hr) ) { return hr; } }
	#endif
#endif

#if defined(WIN32)
class _DECLSPEC KGLock
{
private:
	CRITICAL_SECTION*		m_csLock;


public:
	KGLock(CRITICAL_SECTION* csLock)	{m_csLock = csLock; EnterCriticalSection(m_csLock);}
	~KGLock()							{LeaveCriticalSection(m_csLock); m_csLock = (CRITICAL_SECTION*)0;}
};


class _DECLSPEC KGUnLock
{
private:
	CRITICAL_SECTION*		m_csLock;


public:
	KGUnLock(CRITICAL_SECTION* csLock)	{m_csLock = csLock; LeaveCriticalSection(m_csLock);}
	~KGUnLock()							{EnterCriticalSection(m_csLock); m_csLock = (CRITICAL_SECTION*)0;}
};
#endif


#define IMPLEMENT_SET(x, y)	void Set##y(x t) {KG::KGLock cLock(&m_csLock); m_##y = t;};
#define IMPLEMENT_GET(x, y)	x Get##y() {KG::KGLock cLock(&m_csLock); return m_##y;};
#define	IMPLEMENT_SET_GET(x, y)	IMPLEMENT_SET(x, y) IMPLEMENT_GET(x, y)
#define	IMPLEMENT_GET_SET(x, y)	IMPLEMENT_SET(x, y) IMPLEMENT_GET(x, y)

#define IMPLEMENT_PSET(x, y)	void Set##y(x t) {KG::KGLock cLock(&m_csLock); m_p##y = t;};
#define IMPLEMENT_PGET(x, y)	x Get##y() {KG::KGLock cLock(&m_csLock); return m_p##y;};
#define	IMPLEMENT_PSET_PGET(x, y)	IMPLEMENT_PSET(x, y) IMPLEMENT_PGET(x, y)
#define	IMPLEMENT_PGET_PSET(x, y)	IMPLEMENT_PSET(x, y) IMPLEMENT_PGET(x, y)

#define IMPLEMENT_SET_NOLOCK(x, y)	void Set##y(x t) {m_##y = t;};
#define IMPLEMENT_GET_NOLOCK(x, y)	x Get##y() {return m_##y;};
#define	IMPLEMENT_SET_GET_NOLOCK(x, y)	IMPLEMENT_SET_NOLOCK(x, y) IMPLEMENT_GET_NOLOCK(x, y)
#define	IMPLEMENT_GET_SET_NOLOCK(x, y)	IMPLEMENT_SET_NOLOCK(x, y) IMPLEMENT_GET_NOLOCK(x, y)

#define IMPLEMENT_PSET_NOLOCK(x, y)	void Set##y(x t) {m_p##y = t;};
#define IMPLEMENT_PGET_NOLOCK(x, y)	x Get##y() {return m_p##y;};
#define	IMPLEMENT_PSET_PGET_NOLOCK(x, y)	IMPLEMENT_PSET_NOLOCK(x, y) IMPLEMENT_PGET_NOLOCK(x, y)
#define	IMPLEMENT_PGET_PSET_NOLOCK(x, y)	IMPLEMENT_PSET_NOLOCK(x, y) IMPLEMENT_PGET_NOLOCK(x, y)

#define	IMPLEMENT_VSET(x, y)	virtual void Set##y(x t) {};
#define	IMPLEMENT_VGET(x, y)	virtual x Get##y() {return NULL;};
#define IMPLEMENT_VSET_VGET(x, y)	IMPLEMENT_VSET(x, y) IMPLEMENT_VGET(x, y)
#define IMPLEMENT_VGET_VSET(x, y)	IMPLEMENT_VSET(x, y) IMPLEMENT_VGET(x, y)

#define	IMPLEMENT_LOCK		KG::KGLock cLock(&m_csLock);
#define	IMPLEMENT_UNLOCK	KG::KGUnLock cLock(&m_csLock);


extern "C++" _DECLSPEC bool KGIsNextArg(WCHAR*& strCmdLine, WCHAR* strArg);
extern "C++" _DECLSPEC bool KGCmdParam(WCHAR*& strCmdLine, WCHAR* strFlag);
extern "C++" _DECLSPEC LPCWSTR KGD3DFormatToString(D3DFORMAT format, bool bWithPrefix);
extern "C++" _DECLSPEC DWORD KGD3DFormatToSize(D3DFORMAT format);
extern "C++" _DECLSPEC bool KGReLaunchMediaCenter();
extern "C++" _DECLSPEC HRESULT KGStopRumbleOnAllControllers();

extern "C++" _DECLSPEC HRESULT KGFindDXSDKMediaFileCch(WCHAR* strDestPath, int cchDest, LPCWSTR strFilename);
extern "C++" _DECLSPEC bool KGFindMediaSearchTypicalDirs(WCHAR* strSearchPath, int cchSearch, LPCWSTR strLeaf, WCHAR* strExePath, WCHAR* strExeName);
extern "C++" _DECLSPEC bool KGFindMediaSearchParentDirs(WCHAR* strSearchPath, int cchSearch, WCHAR* strStartAt, WCHAR* strLeafName);

extern "C++" _DECLSPEC UINT KGRegReadInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, INT nDefault);
extern "C++" _DECLSPEC bool KGRegReadString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpDefault, LPTSTR lpRet, DWORD nSize);
extern "C++" _DECLSPEC bool KGRegWriteInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, UINT nData);
extern "C++" _DECLSPEC bool KGRegWriteString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData);


}


#endif

