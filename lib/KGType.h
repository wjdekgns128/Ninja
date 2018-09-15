#ifndef _KG_TYPE_H
#define	_KG_TYPE_H

#ifndef UNICODE
	#error "KG-Emotion requires a Unicode build. See the nearby comments for details"
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

	#ifndef _D3D9_H_
		#include <d3d9.h>
		#pragma comment(lib, "d3d9.lib")
	#endif

	#ifndef __D3DX9_H__
		#include <d3dx9.h>
		#if defined(DEBUG) || defined(_DEBUG)
			#pragma comment(lib, "d3dx9d.lib")
		#else
			#pragma comment(lib, "d3dx9.lib")
		#endif
	#endif
#else
#endif


namespace KG
{


#define KG_MIN_WINDOW_SIZE_X	200
#define KG_MIN_WINDOW_SIZE_Y	200

#undef min 
#undef max 

typedef IDirect3D9*			(WINAPI *LPDIRECT3DCREATE9)(UINT);
typedef INT					(WINAPI *LPD3DPERF_BEGINEVENT)(D3DCOLOR, LPCWSTR);
typedef INT					(WINAPI *LPD3DPERF_ENDEVENT)(void);
typedef VOID				(WINAPI *LPD3DPERF_SETMARKER)(D3DCOLOR, LPCWSTR);
typedef VOID				(WINAPI *LPD3DPERF_SETREGION)(D3DCOLOR, LPCWSTR);
typedef BOOL				(WINAPI *LPD3DPERF_QUERYREPEATFRAME)(void);
typedef VOID				(WINAPI *LPD3DPERF_SETOPTIONS)(DWORD dwOptions);
typedef DWORD				(WINAPI *LPD3DPERF_GETSTATUS)(void);
typedef UINT				(WINAPI *LPTIMEBEGINPERIOD)(UINT uPeriod);

#define KG_ERR_NODIRECT3D              MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0901)
#define KG_ERR_NOCOMPATIBLEDEVICES     MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0902)
#define KG_ERR_MEDIANOTFOUND           MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0903)
#define KG_ERR_NONZEROREFCOUNT         MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0904)
#define KG_ERR_CREATINGDEVICE          MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0905)
#define KG_ERR_RESETTINGDEVICE         MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0906)
#define KG_ERR_CREATINGDEVICEOBJECTS   MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0907)
#define KG_ERR_RESETTINGDEVICEOBJECTS  MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0908)
#define KG_ERR_INCORRECTVERSION        MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0909)

typedef struct _KGDeviceSettings_tag
{
	UINT					AdapterOrdinal;
	D3DDEVTYPE				DeviceType;
	D3DFORMAT				AdapterFormat;
	DWORD					BehaviorFlags;
	D3DPRESENT_PARAMETERS	pp;
} KGDeviceSettings;

typedef bool	(CALLBACK *KGCALLBACKISDEVICEACCEPTABLE)(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext);
typedef bool	(CALLBACK *KGCALLBACKMODIFYDEVICESETTINGS)(KGDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext);
typedef HRESULT	(CALLBACK *KGCALLBACKDEVICECREATED)(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
typedef HRESULT	(CALLBACK *KGCALLBACKDEVICERESET)(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
typedef void	(CALLBACK *KGCALLBACKDEVICEDESTROYED)(void* pUserContext);
typedef void    (CALLBACK *KGCALLBACKDEVICELOST)(void* pUserContext);
typedef void    (CALLBACK *KGCALLBACKFRAMEMOVE)(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
typedef void    (CALLBACK *KGCALLBACKFRAMERENDER)(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
typedef void    (CALLBACK *KGCALLBACKKEYBOARD)(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
typedef void    (CALLBACK *KGCALLBACKMOUSE)(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
typedef LRESULT (CALLBACK *KGCALLBACKMSGPROC)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
typedef void    (CALLBACK *KGCALLBACKTIMER)(UINT idEvent, void* pUserContex);

enum KG_MATCH_TYPE
{
    KG_MT_IGNORE_INPUT		= 0, 
    KG_MT_PRESERVE_INPUT,
    KG_MT_CLOSEST_TO_INPUT
};

enum KG_ANIMATE_TYPE
{
	KG_ANIMATE_OK				= 0,
	KG_ANIMATE_FINISH,
	KG_ANIMATE_LOOP,
	KG_ANIMATE_WAIT,
	KG_ANIMATE_EMPTY,
	KG_ANIMATE_SHOW_FALSE
};

#define	KG_MIRROR_NONE		0x00
#define	KG_MIRROR_V			0x01
#define	KG_MIRROR_H			0x02

#define	KG_LERP_NONE		0x00
#define	KG_LERP_RIGHT		0x01
#define	KG_LERP_LEFT		0x02
#define	KG_LERP_TOP			0x04
#define	KG_LERP_BOTTOM		0x08

typedef struct _KGMatchOptions_tag
{
    KG_MATCH_TYPE			eAdapterOrdinal;
    KG_MATCH_TYPE			eDeviceType;
    KG_MATCH_TYPE			eWindowed;
    KG_MATCH_TYPE			eAdapterFormat;
    KG_MATCH_TYPE			eVertexProcessing;
    KG_MATCH_TYPE			eResolution;
    KG_MATCH_TYPE			eBackBufferFormat;
    KG_MATCH_TYPE			eBackBufferCount;
    KG_MATCH_TYPE			eMultiSample;
    KG_MATCH_TYPE			eSwapEffect;
    KG_MATCH_TYPE			eDepthFormat;
    KG_MATCH_TYPE			eStencilFormat;
    KG_MATCH_TYPE			ePresentFlags;
    KG_MATCH_TYPE			eRefreshRate;
    KG_MATCH_TYPE			ePresentInterval;
} KGMatchOptions;

typedef struct _KGTimerList_tag
{
    KGCALLBACKTIMER			pCallbackTimer;
    void*					pCallbackUserContext;
    float					fTimeoutInSecs;
    float					fCountdown;
    bool					bEnabled;
} KGTimerList;

typedef struct _KGFontList_tag
{
	D3DXFONT_DESCW			Desc;
	ID3DXFont*				pd3dxFont;
	UINT					id;
} KGFontList;


#define WM_THREAD_POS		(WM_USER + 4000)


}


#endif