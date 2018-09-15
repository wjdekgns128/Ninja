#ifndef	_KG_ENUM_H
#define	_KG_ENUM_H

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
	#ifndef _D3D9_H_
		#include <d3d9.h>
	#endif
#else
#endif

#ifndef	_KG_ARRAY_H
	#include "KGArray.h"
#endif
#ifndef	_KG_TYPE_H
	#include "KGType.h"
#endif
#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif


namespace KG
{


typedef KGArray<D3DFORMAT>	KGArrayD3DFORMAT;
typedef KGArray<D3DMULTISAMPLE_TYPE>	KGArrayD3DMULTISAMPLE_TYPE;
typedef KGArray<UINT>		KGArrayUINT;
typedef KGArray<D3DDISPLAYMODE>	KGArrayD3DDISPLAYMODE;
typedef KGArray<DWORD>		KGArrayDWORD;
typedef KGArray<int>		KGArrayINT;

typedef struct _KGD3DEnumDSMSConflict_tag
{
	D3DFORMAT				DSFormat;
	D3DMULTISAMPLE_TYPE		MSType;
} KGD3DEnumDSMSConflict;

typedef KGArray<KGD3DEnumDSMSConflict>	KGArrayD3DEnumDSMSConflict;

class KGD3DEnumAdapterInfo;
class KGD3DEnumDeviceInfo;

typedef struct _KGD3DEnumDeviceSettingsCombo_tag
{
	UINT					AdapterOrdinal;
	D3DDEVTYPE				DeviceType;
	D3DFORMAT				AdapterFormat;
	D3DFORMAT				BackBufferFormat;
	BOOL					Windowed;

	KGArrayD3DFORMAT		depthStencilFormatList;
	KGArrayD3DMULTISAMPLE_TYPE	multiSampleTypeList;
	KGArrayDWORD			multiSampleQualityList;
	KGArrayUINT				presentIntervalList;
	KGArrayD3DEnumDSMSConflict	DSMSConflictList;

	KGD3DEnumAdapterInfo*	pAdapterInfo;
	KGD3DEnumDeviceInfo*	pDeviceInfo;
} KGD3DEnumDeviceSettingsCombo;

typedef KGArray<KGD3DEnumDeviceSettingsCombo*>	KGArrayD3DEnumDeviceSettingsCombo;

class KGD3DEnumDeviceInfo
{
public:
	~KGD3DEnumDeviceInfo();

	UINT					AdapterOrdinal;
	D3DDEVTYPE				DeviceType;
	D3DCAPS9				Caps;

	KGArrayD3DEnumDeviceSettingsCombo	deviceSettingsComboList;
};

typedef KGArray<KGD3DEnumDeviceInfo*>	KGArrayD3DEnumDeviceInfo;

class KGD3DEnumAdapterInfo
{
public:
	~KGD3DEnumAdapterInfo();

	UINT					AdapterOrdinal;
	D3DADAPTER_IDENTIFIER9	AdapterIdentifier;
	WCHAR					szUniqueDescription[256];

	KGArrayD3DDISPLAYMODE	displayModeList;
	KGArrayD3DEnumDeviceInfo	deviceInfoList;
};

typedef KGArray<KGD3DEnumAdapterInfo*>	KGArrayD3DEnumAdapterInfo;

class KGD3DEnumeration
{
public:
    void					SetRequirePostPixelShaderBlending(bool bRequire)	{m_bRequirePostPixelShaderBlending = bRequire;}
    void					SetResolutionMinMax(UINT nMinWidth, UINT nMinHeight, UINT nMaxWidth, UINT nMaxHeight);  
    void					SetRefreshMinMax(UINT nMin, UINT nMax);
    void					SetMultisampleQualityMax(UINT nMax);    
    void					GetPossibleVertexProcessingList(bool* pbSoftwareVP, bool* pbHardwareVP, bool* pbPureHarewareVP, bool* pbMixedVP);
    void					SetPossibleVertexProcessingList(bool bSoftwareVP, bool bHardwareVP, bool bPureHarewareVP, bool bMixedVP);

    KGArrayD3DFORMAT*		GetPossibleDepthStencilFormatList();   
    KGArrayD3DMULTISAMPLE_TYPE* GetPossibleMultisampleTypeList();   
    KGArrayUINT*			GetPossiblePresentIntervalList();

    void					ResetPossibleDepthStencilFormats();
    void					ResetPossibleMultisampleTypeList();
    void					ResetPossiblePresentIntervalList();

    HRESULT					Enumerate(HWND hWndFocus = NULL, IDirect3D9* pD3D = NULL, KGCALLBACKISDEVICEACCEPTABLE IsDeviceAcceptableFunc = NULL, void* pIsDeviceAcceptableFuncUserContext = NULL);

    KGArrayD3DEnumAdapterInfo*	GetAdapterInfoList();  

    KGD3DEnumAdapterInfo*           GetAdapterInfo(UINT AdapterOrdinal);  
    KGD3DEnumDeviceInfo*            GetDeviceInfo(UINT AdapterOrdinal, D3DDEVTYPE DeviceType);    
    KGD3DEnumDeviceSettingsCombo*	GetDeviceSettingsCombo(KGDeviceSettings* pDeviceSettings) {return GetDeviceSettingsCombo(pDeviceSettings->AdapterOrdinal, pDeviceSettings->DeviceType, pDeviceSettings->AdapterFormat, pDeviceSettings->pp.BackBufferFormat, pDeviceSettings->pp.Windowed);}
    KGD3DEnumDeviceSettingsCombo*	GetDeviceSettingsCombo(UINT AdapterOrdinal, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL Windowed);  


public:
	KGD3DEnumeration(HWND hWndFocus, IDirect3D9* pD3D);
    ~KGD3DEnumeration();


private:
    IDirect3D9*				m_pD3D;                                    

    KGCALLBACKISDEVICEACCEPTABLE	m_IsDeviceAcceptableFunc;

    void*					m_pIsDeviceAcceptableFuncUserContext;

    bool					m_bRequirePostPixelShaderBlending;

    KGArrayD3DFORMAT		m_DepthStecilPossibleList;

    KGArrayD3DMULTISAMPLE_TYPE	m_MultiSampleTypeList;

    KGArrayUINT				m_PresentIntervalList;

    bool					m_bSoftwareVP;
    bool					m_bHardwareVP;
    bool					m_bPureHarewareVP;
    bool					m_bMixedVP;

    UINT					m_nMinWidth;
    UINT					m_nMaxWidth;
    UINT					m_nMinHeight;
    UINT					m_nMaxHeight;
    UINT					m_nRefreshMin;
    UINT					m_nRefreshMax;
    UINT					m_nMultisampleQualityMax;

    KGArrayD3DEnumAdapterInfo	m_AdapterInfoList;  

	HWND					m_hWndFocus;


private:
    HRESULT					EnumerateDevices(KGD3DEnumAdapterInfo* pAdapterInfo, KGArrayD3DFORMAT* pAdapterFormatList);
    HRESULT					EnumerateDeviceCombos(KGD3DEnumAdapterInfo* pAdapterInfo, KGD3DEnumDeviceInfo* pDeviceInfo, KGArrayD3DFORMAT* pAdapterFormatList);

    void					BuildDepthStencilFormatList(KGD3DEnumDeviceSettingsCombo* pDeviceCombo);
    void					BuildMultiSampleTypeList(KGD3DEnumDeviceSettingsCombo* pDeviceCombo);
    void					BuildDSMSConflictList(KGD3DEnumDeviceSettingsCombo* pDeviceCombo);
    void					BuildPresentIntervalList(KGD3DEnumDeviceInfo* pDeviceInfo, KGD3DEnumDeviceSettingsCombo* pDeviceCombo);
    void					ClearAdapterInfoList();
};


extern "C++" _DECLSPEC UINT KGColorChannelBits(D3DFORMAT fmt);
extern "C++" _DECLSPEC UINT KGAlphaChannelBits(D3DFORMAT fmt);
extern "C++" _DECLSPEC UINT KGDepthBits(D3DFORMAT fmt);
extern "C++" _DECLSPEC UINT KGStencilBits(D3DFORMAT fmt);


}


#endif



