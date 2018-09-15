#include "CMAIN.h"

IMPLEMENT_MAIN(CMAIN);

CMAIN::CMAIN() : KGEmotion(L"DirectX Setting", 1024, 768)
{
	m_pMain					= this;
	/*_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _CrtSetBreakAlloc(8340);*/
#if defined(NDEBUG)
	SetFullScreenBackBufferWidthAtModeChange(1024);
	SetFullScreenBackBufferHeightAtModeChange(768);
	SetOverrideWidth(1024);
	SetOverrideHeight(768);
	SetOverrideFullScreen(true);
	SetHandleAltEnter(true);
	SetHandleDefaultHotkeys(false);
	SetShowMsgBoxOnError(true);
	SetShowCursorWhenFullScreen(false);
#endif
}


CMAIN::~CMAIN()
{
}


void CMAIN::Create()
{
	Entry(L"game", new cGame);
	Entry(L"logo", new cLogo);
	Entry(L"menu", new cMenu);
}


void CMAIN::Init()
{
	Trans(L"logo");
}