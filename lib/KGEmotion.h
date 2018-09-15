#ifndef	_KG_EMOTION_H
#define	_KG_EMOTION_H

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
#endif
#ifndef	_KG_WINDOW_H
	#include "KGWindow.h"
#endif
#ifndef	_KG_FONT_H
	#include "KGFont.h"
#endif
#ifndef	_KG_RECT_H
	#include "KGRect.h"
#endif
#ifndef	_KG_KALMAN_H
	#include "KGKalman.h"
#endif
#ifndef	_KG_VECTOR_H
	#include "KGVector.h"
#endif
#ifndef	_KG_SPRITE_H
	#include "KGSprite.h"
#endif
#ifndef	_KG_ANIMATE_H
	#include "KGAnimate.h"
#endif
#ifndef	_KG_DIALOG_H
	#include "KGDialog.h"
#endif
#ifndef	_KG_SOUND_H
	#include "KGSound.h"
#endif
#ifndef	_KG_CURSOR_H
	#include "KGCursor.h"
#endif
#ifndef	_KG_RS232_H
	#include "KGRS232.h"
#endif
#ifndef	_KG_3D_ANIMATION_H
	#include "KG3DAnimation.h"
#endif
#ifndef	_KG_3D_SPLINE_H
	#include "KG3DSpline.h"
#endif
#ifndef	_KG_RENDER_TARGET_H
	#include "KGRenderTarget.h"
#endif
#ifndef	_KG_THREAD_H
	#include "KGThread.h"
#endif
#ifndef	_KG_SPLINE_H
	#include "KGSpline.h"
#endif


namespace KG
{


#if defined(_DEBUG) || defined(DEBUG)
	#define IMPLEMENT_MAIN(className) \
		className * className::m_pMain = (className*)0; \
		KGEmotion* KGEmotionCreate() \
		{ \
			className::m_pMain = new className();\
			return (KGEmotion*)className::m_pMain;\
		}\
		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)\
		{\
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);\
			KGEmotion*     pFrame = (KGEmotion*)0;\
			pFrame			= KGEmotionCreate();\
			pFrame->Create();\
			pFrame->Init();\
			pFrame->MainLoop();\
			delete pFrame;\
			return 0;\
		}

#else
	#define IMPLEMENT_MAIN(className) \
		className * className::m_pMain = (className*)0; \
		KGEmotion* KGEmotionCreate() \
		{ \
			className::m_pMain = new className();\
			return (KGEmotion*)className::m_pMain;\
		}\
		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)\
		{\
			KGEmotion*     pFrame = (KGEmotion*)0;\
			pFrame			= KGEmotionCreate();\
			pFrame->Create();\
			pFrame->Init();\
			pFrame->MainLoop();\
			delete pFrame;\
			return 0;\
		}
#endif


class _DECLSPEC KGEmotion : public KGWindow
{
public:
	virtual void			Create()	{};
	virtual void			Init()		{};


public:
	KGEmotion(const WCHAR* strWindowTitle = L"KG-Emotion Window", int nDefaultWidth = 640, int nDefaultHeight = 480);
	virtual ~KGEmotion();
};


}


#endif