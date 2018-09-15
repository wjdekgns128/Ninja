#ifndef	_KG_RESPONSE_H
#define	_KG_RESPONSE_H

#ifndef UNICODE
	#error "KG-Emotion requires a Unicode build. See the nearby comments for details"
#endif

#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif


namespace KG
{


#undef CreateWindow

typedef struct _DECLSPEC _KGResponseWindow_tag
{
	IMPLEMENT_VSET_VGET(HWND, hWnd);
	IMPLEMENT_VSET_VGET(HWND, hWndFocus);
	IMPLEMENT_VSET_VGET(HWND, hWndDeviceFullScreen);
	IMPLEMENT_VSET_VGET(HWND, hWndDeviceWindowed);

	IMPLEMENT_VSET_VGET(HMENU, Menu);

	IMPLEMENT_VSET_VGET(WCHAR*, WindowTitle);

	IMPLEMENT_VSET_VGET(bool, WindowCreated);
	IMPLEMENT_VSET_VGET(bool, WindowCreateCalled);
	IMPLEMENT_VSET_VGET(bool, ClipCursorWhenFullScreen);
	IMPLEMENT_VSET_VGET(bool, ShowCursorWhenFullScreen);
	IMPLEMENT_VSET_VGET(bool, WindowCreatedWithDefaultPositions);
	IMPLEMENT_VSET_VGET(bool, Active);

	virtual HRESULT			CreateWindow(const WCHAR* strWindowTitle = L"KG-Emotion Window", HINSTANCE hInstance = NULL, HICON hIcon = NULL, HMENU hMenu = NULL, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT)	{return NULL;};
} KGResponseWindow;

typedef struct _DECLSPEC _KGResponseKeyboard_tag
{
	IMPLEMENT_VSET_VGET(STICKYKEYS*, StartupStickyKeys);
	IMPLEMENT_VSET_VGET(TOGGLEKEYS*, StartupToggleKeys);
	IMPLEMENT_VSET_VGET(FILTERKEYS*, StartupFilterKeys);
} KGResponseKeyboard;

typedef struct _DECLSPEC _KGResponseDialog_tag
{
	virtual void CALLBACK	OnEvent(UINT id, int xPos, int yPos)	{};
} KGResponseDialog;

typedef struct _DECLSPEC _KGResponseClass_tag
{
	virtual void CALLBACK	OnClassFinish(void* pUserContext)		{};
	virtual void CALLBACK	OnClassDone(void* pUserContext)			{};
	virtual void CALLBACK	OnClassClose(void* pUserContext)		{};
	virtual void CALLBACK	OnClassDestroy(void* pUserContext)		{};
	virtual void CALLBACK	OnClassFail(void* pUserContext)			{};
	virtual void CALLBACK	OnClassFault(void* pUserContext)		{};
	virtual void CALLBACK	OnClassSuccess(void* pUserContext)		{};
	virtual void CALLBACK	OnClassError(void* pUserContext)		{};
	virtual void CALLBACK	OnClassCreate(void* pUserContext)		{};
	virtual void CALLBACK	OnClassInit(void* pUserContext)			{};
	virtual void CALLBACK	OnClassSend(void* pUserContext)			{};
	virtual void CALLBACK	OnClassRecv(void* pUserContext)			{};
	virtual void CALLBACK	OnClassProc(void* pUserContext)			{};
} KGResponseClass;

typedef struct _DECLSPEC _KGResponseObject_tag
{
	virtual void CALLBACK	OnObjectFinish(int index, void* pUserContext)		{};
	virtual void CALLBACK	OnObjectAction(int index, void* pUserContext)		{};
} KGResponseObject;

typedef struct _DECLSPEC _KGResponseThread_tag
{
	virtual void CALLBACK	OnThread(void* pUserContext)			{};
	virtual void CALLBACK	OnThreadFinish(void* pUserContext)		{};
} KGResponseThread;


}


#endif
