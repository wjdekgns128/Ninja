#ifndef	_KG_DIRECT3D_H
#define	_KG_DIRECT3D_H

#ifndef UNICODE
	#error "KG-Emotion requires a Unicode build. See the nearby comments for details"
#endif

#if defined(KG_DLL_EXPORTS)
	#define	_DECLSPEC		__declspec(dllexport)
#else
	#define	_DECLSPEC
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
	#ifndef _INC_COMMCTRL
		#include <commctrl.h>
		#pragma comment(lib, "comctl32.lib")
	#endif

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

#ifndef _KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_TIMER_H
	#include "KGTimer.h"
#endif
#ifndef _KG_RESPONSE_H
	#include "KGResponse.h"
#endif
#ifndef	_KG_TYPE_H
	#include "KGType.h"
#endif
#ifndef	_KG_RECT_H
	#include "KGRect.h"
#endif
#ifndef	_KG_ENUM_H
	#include "KGEnum.h"
#endif
#ifndef	_KG_KEYBOARD_H
	#include "KGKeyboard.h"
#endif
#ifndef _KG_MOUSE_H
	#include "KGMouse.h"
#endif
#ifndef	_KG_SCENE_MANAGER_H
	#include "KGSceneManager.h"
#endif


namespace KG
{


typedef KGArray<KGTimerList>	KGArrayKGTimerList;


class _DECLSPEC KGDirect3d : public KGKeyboard, public KGMouse, public KGSceneManager, public KGResponseWindow
{
private:
	CRITICAL_SECTION		m_csLock;


protected:
	bool					m_InitCalled;
	bool					m_Inited;
	bool					m_ShowMsgBoxOnError;
	bool					m_HandleDefaultHotkeys;
	bool					m_HandleAltEnter;
	bool					m_OverrideWindowed;
	bool					m_OverrideFullScreen;
	bool					m_OverrideForceHAL;
	bool					m_OverrideForceREF;
	bool					m_OverrideForcePureHWVP;
	bool					m_OverrideForceHWVP;
	bool					m_OverrideForceSWVP;
	bool					m_OverrideConstantFrameTime;
	bool					m_ConstantFrameTime;
	bool					m_NoStats;
	bool					m_OverrideRelaunchMCE;
	bool					m_Automation;
	bool					m_InsideDeviceCallback;
	bool					m_DeviceLost;
	bool					m_DeviceObjectsCreated;
	bool					m_DeviceObjectsReset;
	bool					m_DeviceCreateCalled;
	bool					m_RenderingPaused;
	bool					m_TimePaused;
	bool					m_IgnoreSizeChange;
	bool					m_bThreadSafe;
	bool					m_TopmostWhileWindowed;
	bool					m_DeviceCreated;
	bool					m_InsideMainloop;
	bool					m_AutoChangeAdapter;
	bool					m_WireframeMode;
	bool					m_Shutdown;
	
	int						m_ExitCode;
	int						m_OverrideForceVsync;
	int						m_OverrideAdapterOrdinal;
	int						m_OverrideWidth;
	int						m_OverrideHeight;
	int						m_OverrideStartX;
	int						m_OverrideStartY;
	int						m_OverrideQuitAfterFrame;
	int						m_PauseTimeCount;
	int						m_PauseRenderingCount;
	int						m_CurrentFrameNumber;

	UINT					m_FullScreenBackBufferWidthAtModeChange;
	UINT					m_FullScreenBackBufferHeightAtModeChange;
	UINT					m_WindowBackBufferWidthAtModeChange;
	UINT					m_WindowBackBufferHeightAtModeChange;

	DWORD					m_WindowedStyleAtModeChange;
	DWORD					m_LastStatsUpdateFrames;

	WINDOWPLACEMENT*		m_pWindowedPlacement;

	HMONITOR				m_AdapterMonitor;

	float					m_OverrideConstantTimePerFrame;
	float					m_TimePerFrame;
	float					m_ElapsedTime;
	float					m_FPS;

	double					m_Time;
	double					m_LastStatsUpdateTime;

    KGCALLBACKISDEVICEACCEPTABLE    m_IsDeviceAcceptableFunc;
    KGCALLBACKMODIFYDEVICESETTINGS  m_ModifyDeviceSettingsFunc;
    KGCALLBACKDEVICECREATED         m_DeviceCreatedFunc;
    KGCALLBACKDEVICERESET           m_DeviceResetFunc;
    KGCALLBACKDEVICELOST            m_DeviceLostFunc;
    KGCALLBACKDEVICEDESTROYED       m_DeviceDestroyedFunc;
    KGCALLBACKFRAMEMOVE             m_FrameMoveFunc;
    KGCALLBACKFRAMERENDER           m_FrameRenderFunc;
    KGCALLBACKKEYBOARD              m_KeyboardFunc;
    KGCALLBACKMOUSE                 m_MouseFunc;
    KGCALLBACKMSGPROC               m_WindowMsgFunc;

    void*                   m_IsDeviceAcceptableFuncUserContext; 
    void*                   m_ModifyDeviceSettingsFuncUserContext;
    void*                   m_DeviceCreatedUserContext; 
    void*                   m_DeviceCreatedFuncUserContext;
    void*                   m_DeviceResetFuncUserContext;
    void*                   m_DeviceLostFuncUserContext;
    void*                   m_DeviceDestroyedFuncUserContext;
    void*                   m_FrameMoveFuncUserContext;
    void*                   m_FrameRenderFuncUserContext;
    void*                   m_KeyboardFuncUserContext;
    void*                   m_MouseFuncUserContext;
    void*                   m_WindowMsgFuncUserContext;  

	IDirect3D9*				m_pD3D;
	IDirect3DDevice9*		m_pD3DDevice;

	D3DSURFACE_DESC*		m_pBackBufferSurfaceDesc;
	D3DCAPS9*				m_pCaps;

	KGDeviceSettings*		m_pCurrentDeviceSettings;

	KGTimer*				m_pTimer;
	KGD3DEnumeration*		m_pD3DEnumeration;

	WCHAR*					m_pDeviceStats;
	WCHAR*					m_pStaticFrameStats;
	WCHAR*					m_pFPSStats;
	WCHAR*					m_pFrameStats;

	KGArrayKGTimerList*		m_pTimerList;


protected:
	HMODULE					m_hModD3D9;

	LPDIRECT3DCREATE9		m_Direct3DCreate9;

	LPD3DPERF_BEGINEVENT	m_D3DPERF_BeginEvent;
	LPD3DPERF_ENDEVENT		m_D3DPERF_EndEvent;
	LPD3DPERF_SETMARKER		m_D3DPERF_SetMarker;
	LPD3DPERF_SETREGION		m_D3DPERF_SetRegion;
	LPD3DPERF_QUERYREPEATFRAME	m_D3DPERF_QueryRepeatFrame;
	LPD3DPERF_SETOPTIONS	m_D3DPERF_SetOptions;
	LPD3DPERF_GETSTATUS		m_D3DPERF_GetStatus;


public:
	static KGDirect3d*		m_pDirect3d;


public:
	KGDirect3d();
	virtual ~KGDirect3d();


public:
	IMPLEMENT_SET_GET(bool, InitCalled);
	IMPLEMENT_SET_GET(bool, Inited);
	IMPLEMENT_SET_GET(bool, ShowMsgBoxOnError);
	IMPLEMENT_SET_GET(bool, HandleDefaultHotkeys);
	IMPLEMENT_SET_GET(bool, HandleAltEnter);
	IMPLEMENT_SET_GET(bool, OverrideWindowed);
	IMPLEMENT_SET_GET(bool, OverrideFullScreen);
	IMPLEMENT_SET_GET(bool, OverrideForceHAL);
	IMPLEMENT_SET_GET(bool, OverrideForceREF);
	IMPLEMENT_SET_GET(bool, OverrideForcePureHWVP);
	IMPLEMENT_SET_GET(bool, OverrideForceHWVP);
	IMPLEMENT_SET_GET(bool, OverrideForceSWVP);
	IMPLEMENT_SET_GET(bool, OverrideConstantFrameTime);
	IMPLEMENT_SET_GET(bool, ConstantFrameTime);
	IMPLEMENT_SET_GET(bool, NoStats);
	IMPLEMENT_SET_GET(bool, OverrideRelaunchMCE);
	IMPLEMENT_SET_GET(bool, Automation);
	IMPLEMENT_SET_GET(bool, InsideDeviceCallback);
	IMPLEMENT_SET_GET(bool, DeviceLost);
	IMPLEMENT_SET_GET(bool, DeviceObjectsCreated);
	IMPLEMENT_SET_GET(bool, DeviceObjectsReset);
	IMPLEMENT_SET_GET(bool, DeviceCreateCalled);
	IMPLEMENT_SET_GET(bool, TimePaused);
	IMPLEMENT_SET_GET(bool, RenderingPaused);
	IMPLEMENT_SET_GET(bool, IgnoreSizeChange);
	IMPLEMENT_SET_GET(bool, TopmostWhileWindowed);
	IMPLEMENT_SET_GET(bool, DeviceCreated);
	IMPLEMENT_SET_GET(bool, InsideMainloop);
	IMPLEMENT_SET_GET(bool, AutoChangeAdapter);
	IMPLEMENT_SET_GET(bool, WireframeMode);
	IMPLEMENT_SET_GET(bool, Shutdown);

	IMPLEMENT_SET_GET(int, ExitCode);
	IMPLEMENT_SET_GET(int, OverrideAdapterOrdinal);
	IMPLEMENT_SET_GET(int, OverrideForceVsync);
	IMPLEMENT_SET_GET(int, OverrideWidth);
	IMPLEMENT_SET_GET(int, OverrideHeight);
	IMPLEMENT_SET_GET(int, OverrideStartX);
	IMPLEMENT_SET_GET(int, OverrideStartY);
	IMPLEMENT_SET_GET(int, OverrideQuitAfterFrame);
	IMPLEMENT_SET_GET(int, PauseTimeCount);
	IMPLEMENT_SET_GET(int, PauseRenderingCount);
	IMPLEMENT_SET_GET(int, CurrentFrameNumber);

	IMPLEMENT_SET_GET(UINT, FullScreenBackBufferWidthAtModeChange);
	IMPLEMENT_SET_GET(UINT, FullScreenBackBufferHeightAtModeChange);
	IMPLEMENT_SET_GET(UINT, WindowBackBufferWidthAtModeChange);
	IMPLEMENT_SET_GET(UINT, WindowBackBufferHeightAtModeChange);

	IMPLEMENT_SET_GET(DWORD, WindowedStyleAtModeChange);
	IMPLEMENT_SET_GET(DWORD, LastStatsUpdateFrames);

	IMPLEMENT_PSET_PGET(WINDOWPLACEMENT*, WindowedPlacement);

	IMPLEMENT_SET_GET(HMONITOR, AdapterMonitor);

	IMPLEMENT_SET_GET(float, OverrideConstantTimePerFrame);
	IMPLEMENT_SET_GET(float, TimePerFrame);
	IMPLEMENT_SET_GET(float, ElapsedTime);
	IMPLEMENT_SET_GET(float, FPS);

	IMPLEMENT_SET_GET(double, Time);
	IMPLEMENT_SET_GET(double, LastStatsUpdateTime);
	
	IMPLEMENT_PSET_PGET(IDirect3D9*, D3D);
	IMPLEMENT_PSET_PGET(IDirect3DDevice9*, D3DDevice);
	IMPLEMENT_PSET_PGET(KGDeviceSettings*, CurrentDeviceSettings);
	IMPLEMENT_PSET_PGET(D3DSURFACE_DESC*, BackBufferSurfaceDesc);
	IMPLEMENT_PSET_PGET(KGTimer*, Timer);
	IMPLEMENT_PSET_PGET(D3DCAPS9*, Caps);
	IMPLEMENT_PSET_PGET(KGD3DEnumeration*, D3DEnumeration);

	IMPLEMENT_PSET_PGET(STICKYKEYS*, StartupStickyKeys);
	IMPLEMENT_PSET_PGET(TOGGLEKEYS*, StartupToggleKeys);
	IMPLEMENT_PSET_PGET(FILTERKEYS*, StartupFilterKeys);

    IMPLEMENT_SET_GET(KGCALLBACKISDEVICEACCEPTABLE, IsDeviceAcceptableFunc);
    IMPLEMENT_SET_GET(KGCALLBACKMODIFYDEVICESETTINGS, ModifyDeviceSettingsFunc);
    IMPLEMENT_SET_GET(KGCALLBACKDEVICECREATED, DeviceCreatedFunc);
    IMPLEMENT_SET_GET(KGCALLBACKDEVICERESET, DeviceResetFunc);
    IMPLEMENT_SET_GET(KGCALLBACKDEVICELOST, DeviceLostFunc);
    IMPLEMENT_SET_GET(KGCALLBACKDEVICEDESTROYED, DeviceDestroyedFunc);
    IMPLEMENT_SET_GET(KGCALLBACKFRAMEMOVE, FrameMoveFunc);
    IMPLEMENT_SET_GET(KGCALLBACKFRAMERENDER, FrameRenderFunc);
    IMPLEMENT_SET_GET(KGCALLBACKKEYBOARD, KeyboardFunc);
    IMPLEMENT_SET_GET(KGCALLBACKMOUSE, MouseFunc);
    IMPLEMENT_SET_GET(KGCALLBACKMSGPROC, WindowMsgFunc);

    IMPLEMENT_SET_GET(void*, IsDeviceAcceptableFuncUserContext);
    IMPLEMENT_SET_GET(void*, ModifyDeviceSettingsFuncUserContext);
    IMPLEMENT_SET_GET(void*, DeviceCreatedFuncUserContext);
    IMPLEMENT_SET_GET(void*, DeviceResetFuncUserContext);
    IMPLEMENT_SET_GET(void*, DeviceLostFuncUserContext);
    IMPLEMENT_SET_GET(void*, DeviceDestroyedFuncUserContext);
    IMPLEMENT_SET_GET(void*, FrameMoveFuncUserContext);
    IMPLEMENT_SET_GET(void*, FrameRenderFuncUserContext);
    IMPLEMENT_SET_GET(void*, KeyboardFuncUserContext);
    IMPLEMENT_SET_GET(void*, MouseFuncUserContext);
    IMPLEMENT_SET_GET(void*, WindowMsgFuncUserContext);

	IMPLEMENT_PGET(WCHAR*, DeviceStats);
	IMPLEMENT_PGET(WCHAR*, StaticFrameStats);
	IMPLEMENT_PGET(WCHAR*, FPSStats);

	IMPLEMENT_PGET(KGArrayKGTimerList*, TimerList);


protected:
	IDirect3D9* WINAPI		Direct3DCreate9(UINT SDKVersion);

	int WINAPI				D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName);
	int WINAPI				D3DPERF_EndEvent();
	
	void WINAPI				D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName);
	void WINAPI				D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName);
	void WINAPI				D3DPERF_SetOptions(DWORD dwOptions);

	bool					EnsureD3DAPIs();
	BOOL WINAPI				D3DPERF_QueryRepeatFrame();

	DWORD WINAPI			D3DPERF_GetStatus();

	void					DisplayErrorMessage(HRESULT hr);
	void					ParseCommandLine();
	void					Shutdown(int nExitCode);


public:
	IDirect3D9*				GetD3DObject();
	D3DCAPS9*				GetDeviceCaps();
	KGD3DEnumeration*		PrepareEnumerationObject(bool bEnumerate = false);

	void					ConstantFrameTime(bool bEnabled, float fTimePerFrame = 0.0333f);
	void					UpdateBackBufferDesc();
	void					SetupCursor();
	void					UpdateDeviceStats(D3DDEVTYPE DeviceType, DWORD BehaviorFlags, D3DADAPTER_IDENTIFIER9* pAdapterIdentifier);
	void					BuildOptimalDeviceSettings(KGDeviceSettings* pOptimalDeviceSettings, KGDeviceSettings* pDeviceSettingsIn, KGMatchOptions* pMatchOptions);
	void					BuildValidDeviceSettings(KGDeviceSettings* pValidDeviceSettings, KGD3DEnumDeviceSettingsCombo* pBestDeviceSettingsCombo, KGDeviceSettings* pDeviceSettingsIn, KGMatchOptions* pMatchOptions);
	void					Pause(bool bPauseTime, bool bPauseRendering);
	void					Shutdown();
	void					UpdateDeviceSettingsWithOverrides(KGDeviceSettings* pDeviceSettings);
	void					Cleanup3DEnvironment(bool bReleaseSettings = true);
	void					UpdateStaticFrameStats();
	void					Render3DEnvironment();
	void					UpdateFrameStats();
	void					HandleTimers();
	void					CheckForWindowSizeChange();
	void					CheckForWindowChangingMonitors();

	bool					IsWindowed();
	bool					DoesDeviceComboMatchPreserveOptions(KGD3DEnumDeviceSettingsCombo* pDeviceSettingsCombo, KGDeviceSettings* pDeviceSettingsIn, KGMatchOptions* pMatchOptions);
	bool					IsRenderingPaused();
	bool					IsTimePaused();
	bool					IsActive();

	float					RankDeviceCombo(KGD3DEnumDeviceSettingsCombo* pDeviceSettingsCombo, KGDeviceSettings* pOptimalDeviceSettings, D3DDISPLAYMODE* pAdapterDesktopDisplayMode);

	HRESULT					Init(bool bParseCommandLine = true, bool bHandleDefaultHotkeys = true, bool bShowMsgBoxOnError = true, bool bHandleAltEnter = true);
	HRESULT					Create3DEnvironment(IDirect3DDevice9* pd3dDeviceFromApp);
	HRESULT					SetDeviceCursor(IDirect3DDevice9* pd3dDevice, HCURSOR hCursor, bool bAddWatermakr);
	HRESULT					CreateDevice(UINT AdapterOrdinal = D3DADAPTER_DEFAULT, bool bWindowed = true, int nSuggestedWidth = 0, int nSuggestedHeight = 0, KGCALLBACKISDEVICEACCEPTABLE pCallbackIsDeviceAcceptable = NULL, KGCALLBACKMODIFYDEVICESETTINGS pCallbackModifyDeviceSettings = NULL, void* pUserContext = NULL);
	HRESULT					FindValidDeviceSettings(KGDeviceSettings* pOut, KGDeviceSettings* pIn, KGMatchOptions* pMatchOptions);
	HRESULT					FindValidResolution(KGD3DEnumDeviceSettingsCombo* pBestDeviceSettingsCombo, D3DDISPLAYMODE displayModeIn, D3DDISPLAYMODE* pBestDisplayMode);
	HRESULT					ChangeDevice(KGDeviceSettings* pNewDeviceSettings, IDirect3DDevice9* pd3dDeviceFromApp, bool bForceRecreate, bool bClipWindowToSingleAdapter);
	HRESULT					Reset3DEnvironment();
	HRESULT					MainLoop(HACCEL hAccel = NULL);
	HRESULT					ToggleFullScreen();
	HRESULT					GetAdapterOrdinalFromMonitor(HMONITOR hMonitor, UINT* pAdapterOrdinal);
	HRESULT					ToggleREF();

	KGDeviceSettings		GetDeviceSettings();

	LPCWSTR					GetFrameStats(bool bShowFPS = true);
};


}


#endif

