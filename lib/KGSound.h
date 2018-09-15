#ifndef	_KG_SOUND_H
#define	_KG_SOUND_H

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
	#ifndef __DSOUND_INCLUDED__
		#include <dsound.h>
	#endif
#else
#endif

#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef _KG_MAPPER_H
	#include "KGMapper.h"
#endif
#ifndef	_KG_WAVE_FILE_H
	#include "KGWaveFile.h"
#endif
#ifndef	_KG_MP3_FILE_H
	#include "KGMp3File.h"
#endif


namespace KG
{


class _DECLSPEC KGSound : protected KGMp3File
{
protected:
    IDirectSound8*			m_pDirectSound;

	KGMapper				m_Table;


public:
	KGSound(HWND hWnd, DWORD dwCoopLevel = DSSCL_PRIORITY);
	~KGSound();


protected:
	IDirectSoundBuffer*	Create(const WCHAR* pFileName, DWORD dwCreationFlags = 0, GUID guid3DAlgorithm = GUID_NULL);

	HRESULT					FillBufferWithSound(IDirectSoundBuffer* pDirectSoundBuffer, KGWaveFile* pWaveFile, bool bRepeatWavIfBufferLarger);
	HRESULT					RestoreBuffer(IDirectSoundBuffer* pDirectSoundBuffer, bool* pbWasRestored);


public:
	void					Entry(const WCHAR* wsName, const WCHAR* pFileName);

	IDirectSoundBuffer*		Trans(const WCHAR* wsName);


public:
	bool					Play(const WCHAR* wsName, bool bReset = true, DWORD dwPriority = 0, DWORD dwFlags = 0);

	void					Stop();
	void					Stop(const WCHAR* wsName);

	bool					isPlay(const WCHAR* wsName);
};


}


#endif
