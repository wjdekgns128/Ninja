#ifndef	_KG_WAVE_FILE_H
#define	_KG_WAVE_FILE_H

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
#else
#endif

#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif


namespace KG
{


#define WAVEFILE_READ		1
#define WAVEFILE_WRITE		2


class _DECLSPEC KGWaveFile
{
private:
    WAVEFORMATEX*			m_pwfx;

    HMMIO					m_hmmio;

    MMCKINFO				m_ck;
    MMCKINFO				m_ckRiff;
    
    MMIOINFO				m_mmioinfoOut;

	DWORD					m_dwSize;
    DWORD					m_dwFlags;

    BOOL					m_bIsReadingFromMemory;

    BYTE*					m_pbData;
    BYTE*					m_pbDataCur;

    ULONG					m_ulDataSize;

    CHAR*					m_pResourceBuffer;


protected:
    HRESULT					ReadMMIO();
    HRESULT					WriteMMIO(WAVEFORMATEX* pwfxDest);


public:
    KGWaveFile();
    virtual ~KGWaveFile();


public:
    HRESULT					Open(LPWSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags);
    HRESULT					OpenFromMemory(BYTE* pbData, ULONG ulDataSize, WAVEFORMATEX* pwfx, DWORD dwFlags);
    HRESULT					Close();
    HRESULT					Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead);
    HRESULT					Write(UINT nSizeToWrite, BYTE* pbData, UINT* pnSizeWrote);
	HRESULT					ResetFile();

    DWORD					GetSize();

    WAVEFORMATEX*			GetFormat() {return m_pwfx;};
};


}


#endif
