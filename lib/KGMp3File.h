#ifndef _KG_MP3_FILE_H
#define _KG_MP3_FILE_H

#ifndef UNICODE
	#error "KG-Emotion requires a Unicode build. See the nearby comments for details"
#endif

#if defined(KG_DLL_EXPORTS)
	#define	_DECLSPEC		__declspec(dllexport)
#else
	#define	_DECLSPEC
#endif

#ifndef __wmsdkidl_h__
	#include <wmsdk.h>
	#pragma comment(lib, "wmvcore.lib")
#endif

#ifndef _INC_MMSYSTEM
	#include <mmsystem.h>
	#pragma comment(lib, "winmm.lib")
#endif

#ifndef __DSOUND_INCLUDED__
	#include <dsound.h>
	#pragma comment(lib, "dsound.lib")
#endif

#include <string>


namespace KG
{

	
#define	DECODING_BUFFER_ERROR	8192


class WMAStream : public IStream
{
public:
    WMAStream();
    virtual ~WMAStream();


public:
    void					Clear();
    void					Close();

	HRESULT __stdcall		QueryInterface(const struct _GUID& guid , void** ppInterface);
    ULONG   __stdcall		AddRef();
    ULONG   __stdcall		Release();

    HRESULT __stdcall		Open(const WCHAR* wsFileName);

    HRESULT __stdcall		Read(void* pv, ULONG cb, ULONG* pcbRead);
    HRESULT __stdcall		Write(const void* pv, ULONG cb, ULONG* pcbWritten);
    HRESULT __stdcall		Seek(LARGE_INTEGER dlibMove , DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition);
    HRESULT __stdcall		SetSize(ULARGE_INTEGER libNewSize);
    HRESULT __stdcall		CopyTo(IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten);
    HRESULT __stdcall		Commit(DWORD grfCommitFlags);
    HRESULT __stdcall		Revert();
    HRESULT __stdcall		LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
    HRESULT __stdcall		UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
    HRESULT __stdcall		Stat(STATSTG* pstatstg, DWORD grfStatFlag);
    HRESULT __stdcall		Clone(IStream **ppstm);


private:
    INT                     m_iRefCount;
	HANDLE					m_hFile ;
};


class _DECLSPEC KGMp3File : public IWMReaderCallback , public IWMReaderCallbackAdvanced
{
public:
    KGMp3File(IDirectSound8* pDS = NULL);
    virtual ~KGMp3File();


public:
    void					SetDevice(IDirectSound8* pDS) {m_pDirectSound = pDS;}
	void                    Close();

    IDirectSoundBuffer*     Open(const WCHAR* pFileName);


public:
    bool                    Read(BYTE* pDestBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead);
	bool                    PreOpen();
    bool                    PostOpen();
    bool                    IsEOF();

    DWORD                   GetSize();
    WAVEFORMATEX*           GetFormat();

    void                    Clear();
    void                    Destroy();

    HRESULT                 GetHeaderAttribute(LPCWSTR pwszName , BYTE** ppbValue);

    HRESULT __stdcall		QueryInterface(const struct _GUID& guid , void** ppInterface);
    ULONG   __stdcall       AddRef();
    ULONG   __stdcall       Release();

    HRESULT __stdcall		OnStatus(WMT_STATUS  Status, HRESULT hr, WMT_ATTR_DATATYPE dwType, BYTE *pValue, void *pvContext);
    HRESULT __stdcall		OnSample(DWORD dwOutputNum, QWORD cnsSampleTime, QWORD cnsSampleDuration, DWORD dwFlags, INSSBuffer* pSample, void* pvContext);
    HRESULT __stdcall		OnStreamSample(WORD wStreamNum, QWORD cnsSampleTime, QWORD cnsSampleDuration, DWORD dwFlags, INSSBuffer __RPC_FAR* pSample, void __RPC_FAR* pvContext);
    HRESULT __stdcall		OnTime(QWORD qwCurrentTime, void __RPC_FAR* pvContext);
    HRESULT __stdcall		OnStreamSelection(WORD wStreamCount, WORD __RPC_FAR* pStreamNumbers, WMT_STREAM_SELECTION __RPC_FAR* pSelections, void __RPC_FAR* pvContext);
    HRESULT __stdcall		OnOutputPropsChanged(DWORD dwOutputNum, WM_MEDIA_TYPE __RPC_FAR* pMediaType, void __RPC_FAR* pvContext);
    HRESULT __stdcall		AllocateForOutput(DWORD dwOutputNum, DWORD cbBuffer, INSSBuffer __RPC_FAR* __RPC_FAR* ppBuffer, void __RPC_FAR* pvContext);
    HRESULT __stdcall		AllocateForStream(WORD wStreamNum, DWORD cbBuffer, INSSBuffer __RPC_FAR* __RPC_FAR* ppBuffer, void __RPC_FAR* pvContext);


public:
    IDirectSound8*          m_pDirectSound;

    IWMReader*              m_pReader;
    IWMReaderAdvanced*      m_pReaderAdvanced;
    IWMReaderAdvanced2*     m_pReaderAdvanced2;
    IWMHeaderInfo*          m_pHeaderInfo;

    WAVEFORMATEX            m_WaveFormatEx;

    HANDLE                  m_hWaitEvent;
    HANDLE                  m_hRespondEvent;

    bool                    m_bOpen;

    HRESULT                 m_hrCallbackResult;

    DWORD                   m_nStreamSize;
    DWORD                   m_nBytesRead;

    bool                    m_bFirstRead;
    BYTE*                   m_pBuffer;
    DWORD                   m_nBufferSize;
    DWORD                   m_nWritePtr;
    DWORD                   m_nTargetPtr;
    bool                    m_bEOF;
    DWORD                   m_qwTime;

    CRITICAL_SECTION        m_csTerm;

    WMAStream*              m_pFileStream;

    LONG                    m_iRefCount;
    HANDLE                  m_hReadComplete;
};


}


#endif 
