#ifndef _CMAIN_H
#define _CMAIN_H

#include <KGEmotion.h>
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif

//#ifdef _DEBUG
//#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
//#endif

#include "cGame.h"
#include "cLogo.h"
#include "cMenu.h"

using namespace KG;

class CMAIN : public KGEmotion
{
public:
	CMAIN();
	~CMAIN();


public:
	static CMAIN*			m_pMain;


public:
	void					Create();
	void					Init();
};

static CMAIN* cMain()
{
	return CMAIN::m_pMain;
}

#endif