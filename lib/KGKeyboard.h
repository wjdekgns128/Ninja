#ifndef	_KG_KEYBOARD_H
#define	_KG_KEYBOARD_H

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


class _DECLSPEC KGKeyboard : public KGResponseKeyboard
{
private:
	CRITICAL_SECTION		m_csLock;


protected:
	STICKYKEYS*				m_pStartupStickyKeys;
	TOGGLEKEYS*				m_pStartupToggleKeys;
	FILTERKEYS*				m_pStartupFilterKeys;

	bool					m_AllowShortcutKeysWhenFullscreen;
	bool					m_AllowShortcutKeysWhenWindowed;
	bool					m_AllowShortcutKeys;

	bool*					m_pKeys;

	HHOOK					m_KeyboardHook;


public:
	static KGKeyboard*		m_pKeyboard;


protected:
	IMPLEMENT_SET_GET(bool, AllowShortcutKeysWhenFullscreen);
	IMPLEMENT_SET_GET(bool, AllowShortcutKeysWhenWindowed);
	IMPLEMENT_SET_GET(bool, AllowShortcutKeys);

	IMPLEMENT_PSET_PGET(bool*, Keys);

	IMPLEMENT_SET_GET(HHOOK, KeyboardHook);


protected:
	void					AllowShortcutKeys(bool bAllowKeys);


public:
	static LRESULT CALLBACK	LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);


public:
	KGKeyboard();
	virtual ~KGKeyboard();
};


}


#endif


