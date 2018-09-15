#ifndef	_KG_SCENE_H
#define	_KG_SCENE_H

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

#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_TYPE_H
	#include "KGType.h"
#endif


namespace KG
{


class _DECLSPEC KGScene
{
public:
	virtual bool CALLBACK	IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext){return true;}
	virtual bool CALLBACK	ModifyDeviceSettings(KGDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext)							{return true;}
	virtual HRESULT CALLBACK	OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)			{return 0;}
	virtual HRESULT CALLBACK	OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)			{return 0;}
	virtual void CALLBACK	OnLostDevice(void* pUserContext)																							{}
	virtual void CALLBACK	OnDestroyDevice(void* pUserContext)																							{}
	virtual void CALLBACK	OnNetwork(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)								{}
	virtual void CALLBACK	OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)								{}
	virtual void CALLBACK	OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)							{}
	virtual void CALLBACK	OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)													{}
	virtual void CALLBACK	OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)	{}
	virtual LRESULT CALLBACK	OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)			{return uMsg;}
	

public:
	KGScene()				{}
	virtual ~KGScene()		{}
};


}


#endif
