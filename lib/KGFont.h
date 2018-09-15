#ifndef	_KG_FONT_H
#define	_KG_FONT_H

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
#ifndef	_KG_TYPE_H
	#include "KGType.h"
#endif
#ifndef	_KG_ARRAY_H
	#include "KGArray.h"
#endif


namespace KG
{


typedef KGArray<KGFontList>	KGArrayKGFontList;


class _DECLSPEC KGFont
{
protected:
	IDirect3DDevice9*		m_pd3dDevice;

	KGArrayKGFontList		m_FontList;


public:
	KGFont(IDirect3DDevice9* pd3dDevice);
	virtual ~KGFont();


public:
	ID3DXFont*				Get(int id = 0);

	int						height(int id = 0);
	UINT					width(int id = 0);
	UINT					weight(int id = 0);

	int						DrawText(LPD3DXSPRITE pSprite, LPCTSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color);
	int						DrawText(int id, LPD3DXSPRITE pSprite, LPCTSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color);

	void					Entry(int id, LPCTSTR pFacename, UINT Height, UINT Width, UINT Weight = FW_BOLD, UINT MipLevels = 1, BOOL Italic = false, DWORD CharSet = DEFAULT_CHARSET,
								  DWORD OutputPrecision = OUT_TT_ONLY_PRECIS, DWORD Quality = DEFAULT_QUALITY,
								  DWORD PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE);
	void					Entry(int id, const WCHAR* wsPathName, LPCTSTR pFacename, UINT Height, UINT Width, 
								  UINT Weight = FW_BOLD, UINT MipLevels = 1, BOOL Italic = false, DWORD CharSet = DEFAULT_CHARSET,
								  DWORD OutputPrecision = OUT_TT_ONLY_PRECIS, DWORD Quality = DEFAULT_QUALITY,
								  DWORD PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE);
	void					Remove(int id);


public:
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice = NULL, const D3DSURFACE_DESC* pBackBufferSurfaceDesc = NULL, void* pUserContext = NULL);
	void CALLBACK			OnLostDevice(void* pUserContext = NULL);
};


}


#endif
