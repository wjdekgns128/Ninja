#ifndef _KG_TIMER_H
#define _KG_TIMER_H

#ifndef UNICODE
	#error "KG-Emotion requires a Unicode build. See the nearby comments for details"
#endif

#if defined(KG_DLL_EXPORTS)
	#define	_DECLSPEC		__declspec(dllexport)
#else
	#define	_DECLSPEC
#endif

#define _WINSOCKAPI_
#ifndef	_INC_WINDOWS
	#include <windows.h>
#endif
#undef _WINSOCKAPI_


namespace KG
{


class _DECLSPEC KGTimer
{
public:
    KGTimer();

    void					Reset();
    void					Start();
    void					Stop();
    void					Advance();

    double					GetAbsoluteTime();
    double					GetTime();
    double					GetElapsedTime();

    bool					IsStopped();


protected:
    bool					m_bUsingQPF;
    bool					m_bTimerStopped;

    __int64					m_llQPFTicksPerSec;

    __int64					m_llStopTime;
    __int64					m_llLastElapsedTime;
    __int64					m_llBaseTime;
};


}


#endif


