#ifndef	_KG_WINDOW_H
#define	_KG_WINDOW_H

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
	#if defined(DEBUG) || defined(_DEBUG)
		#ifndef _INC_CRTDBG
			#include <crtdbg.h>
		#endif
	#endif
#else
#endif

#ifndef _KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_DIRECT3D_H
	#include "KGDirect3d.h"
#endif


namespace KG
{


#undef CreateWindow

class _DECLSPEC KGWindow : public KGDirect3d
{
private:
	CRITICAL_SECTION		m_csLock;


protected:
	HINSTANCE				m_hInstance;

	HWND					m_hWnd;
	HWND					m_hWndFocus;
	HWND					m_hWndDeviceFullScreen;
	HWND					m_hWndDeviceWindowed;

	HMENU					m_Menu;

	HANDLE					m_hMutex;

	bool					m_WindowCreated;
	bool					m_WindowCreateCalled;
	bool					m_ClipCursorWhenFullScreen;
	bool					m_ShowCursorWhenFullScreen;
	bool					m_WindowCreatedWithDefaultPositions;
	bool					m_Active;
	bool					m_CallDefWindowProc;
	bool					m_Minimized;
	bool					m_Maximized;
	bool					m_InSizeMove;
	bool					m_MinimizedWhileFullScreen;

	WCHAR*					m_pWindowTitle;

	int						m_nDefaultWidth;
	int						m_nDefaultHeight;


public:
	static KGWindow*		m_pWindow;


public:
	KGWindow(int nDefaultWidth = 640, int nDefaultHeight = 480);
	virtual ~KGWindow();


public:
	IMPLEMENT_SET_GET(HWND, hWnd);
	IMPLEMENT_SET_GET(HWND, hWndFocus);
	IMPLEMENT_SET_GET(HWND, hWndDeviceFullScreen);
	IMPLEMENT_SET_GET(HWND, hWndDeviceWindowed);

	IMPLEMENT_SET_GET(HINSTANCE, hInstance);

	IMPLEMENT_SET_GET(HMENU, Menu);

	IMPLEMENT_SET_GET(bool, WindowCreated);
	IMPLEMENT_SET_GET(bool, WindowCreateCalled);
	IMPLEMENT_SET_GET(bool, ClipCursorWhenFullScreen);
	IMPLEMENT_SET_GET(bool, ShowCursorWhenFullScreen);
	IMPLEMENT_SET_GET(bool, WindowCreatedWithDefaultPositions);
	IMPLEMENT_SET_GET(bool, Active);
	IMPLEMENT_SET_GET(bool, CallDefWindowProc);
	IMPLEMENT_SET_GET(bool, Minimized);
	IMPLEMENT_SET_GET(bool, Maximized);
	IMPLEMENT_SET_GET(bool, InSizeMove);
	IMPLEMENT_SET_GET(bool, MinimizedWhileFullScreen);

	IMPLEMENT_PGET(WCHAR*, WindowTitle);

	void					SetWindowTitle(const WCHAR* strWindowTitle = L"KG-Emotion Window");
	void					CloseWindow();

	HRESULT					CreateWindow(const WCHAR* strWindowTitle = L"KG-Emotion Window", HINSTANCE hInstance = NULL, HICON hIcon = NULL, HMENU hMenu = NULL, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT);
	HRESULT					SetWindow(HWND hWndFocus, HWND hWndDeviceFullScreen, HWND hWndDeviceWindowed, bool bHandleMessage);


public:
	static LRESULT CALLBACK	WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


}


#endif



