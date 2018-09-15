#ifndef	_KG_DIALOG_H
#define	_KG_DIALOG_H

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
		#pragma comment(lib, "d3d9.lib")
	#endif
	#ifndef _DXERR9_H_
		#include <dxerr9.h>
		#pragma comment(lib, "dxerr9.lib")
	#endif
#else
#endif


#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_STRING_H
	#include "KGString.h"
#endif
#ifndef	_KG_VECTOR_H
	#include "KGVector.h"
#endif
#ifndef	_KG_RECT_H
	#include "KGRect.h"
#endif
#ifndef	_KG_SPRITE_H
	#include "KGSprite.h"
#endif
#ifndef	_KG_ANIMATE_H
	#include "KGAnimate.h"
#endif
#ifndef	_KG_SOUND_H
	#include "KGSound.h"
#endif
#ifndef	_KG_RESPONSE_H
	#include "KGResponse.h"
#endif


namespace KG
{

#ifndef SAFE_ONFRAMEMOVE
	#define SAFE_ONFRAMEMOVE(p)		{if(p) {p->OnFrameMove(pd3dDevice, fTime, fElapsedTime, pUserContext);}}
#endif
#ifndef SAFE_ONFRAMEMOVE_0
	#define SAFE_ONFRAMEMOVE_0(p)	{if(p) {p->OnFrameMove(pd3dDevice, fTime, fElapsedTime, pUserContext);}}
#endif
#ifndef SAFE_ONFRAMEMOVE_1
	#define SAFE_ONFRAMEMOVE_1(p, v){if(p) {p->OnFrameMove(pd3dDevice, fTime, fElapsedTime, (void*)v);}}
#endif
#ifndef SAFE_ONFRAMERENDER
	#define SAFE_ONFRAMERENDER(p)	{if(p) {p->OnFrameRender(pd3dDevice, fTime, fElapsedTime, pUserContext);}}
#endif
#ifndef SAFE_ONKEYBOARD
	#define SAFE_ONKEYBOARD(p)		{if(p) {p->OnKeyboard(nChar, bKeyDown, bAltDown, pUserContext);}}
#endif
#ifndef SAFE_ONMOUSE
	#define SAFE_ONMOUSE(p)			{if(p) {p->OnMouse(bButtonDown, bLeftButtonDown, bRightButtonDown, bMiddleButtonDown, bSideButton1Down, bSideButton2Down, nMouseWheelDelta, xPos, yPos, pUserContext);}}
#endif
#ifndef SAFE_ONMSGPROC
	#define SAFE_ONMSGPROC(p)		{if(p) {p->OnMsgProc(hWnd, uMsg, wParam, lParam, pbNoFurtherProcessing, pUserContext);}}
#endif
#ifndef	SAFE_ONRESETDEVICE
	#define	SAFE_ONRESETDEVICE(p)	{if(p) {p->OnResetDevice(pd3dDevice, pBackBufferSurfaceDesc, pUserContext);}}
#endif
#ifndef	SAFE_ONLOSTDEVICE
	#define	SAFE_ONLOSTDEVICE(p)	{if(p) {p->OnLostDevice(pUserContext);}}
#endif
#ifndef	SAFE_ONRESETDEVICE_0
#define	SAFE_ONRESETDEVICE_0(p)		{if(p) {p->OnResetDevice();}}
#endif
#ifndef	SAFE_ONLOSTDEVICE_0
	#define	SAFE_ONLOSTDEVICE_0(p)	{if(p) {p->OnLostDevice();}}
#endif


typedef struct _KGDialogImage_tag
{
	KGString				wsName;

	D3DXVECTOR3				vPos;
	D3DXCOLOR				color;

	_KGDialogImage_tag(const WCHAR* _wsName, D3DXVECTOR3& _vPos, D3DXCOLOR& _color)
	{
		wsName				= _wsName;
		vPos				= _vPos;
		color				= _color;
	}
} KGDialogImage;


class _DECLSPEC KGDialogPixel
{
public:
	BYTE*					m_pImage;

	KGRect					m_rcImage;


public:
	KGDialogPixel();
	virtual ~KGDialogPixel();


public:
	void					GetTexImage(KGTextureChunk* pTexture, D3DXVECTOR3& vPos);

	bool					check(int xPos, int yPos);
};


class _DECLSPEC KGDialogResponseEvent
{
private:
	KGResponseDialog*	m_pResponseEvent;


public:
	KGDialogResponseEvent()			{m_pResponseEvent = NULL;}
	virtual ~KGDialogResponseEvent(){m_pResponseEvent = NULL;}


public:
	virtual void SetResponse(KGResponseDialog* pResponseEvent)
	{
		m_pResponseEvent	= pResponseEvent;
	}

	virtual KGResponseDialog* GetResponse()
	{
		return m_pResponseEvent;
	}
};


class KGDialog;


class _DECLSPEC KGDialogButton : public KGDialogResponseEvent, protected KGDialogPixel
{
private:
	KGSprite*				m_pSprite;
	KGSound*				m_pSound;

	KGString				m_wsDefault;
	KGString				m_wsClick;
	KGString				m_wsOver;
	KGString				m_wsDisable;
	KGString				m_wsRender;
	KGString				m_wsOverSound;
	KGString				m_wsClickSound;

#pragma warning(disable : 4251)
	D3DXCOLOR				m_Color;
	D3DXVECTOR3				m_vPos;
#pragma warning(default : 4251)

	KGRect					m_rcRect;

	bool					m_Show;
	bool					m_Disable;
	bool					m_Click;
	bool					m_Mask;
	bool					m_Overed;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogButton(KGSprite* pSprite, KGSound* pSound, UINT id,
				   const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable,
				   D3DXVECTOR3& vPos, KGResponseDialog* pResponseEvent, bool bMask);
	KGDialogButton(const KGDialogButton& Button);
	~KGDialogButton();


public:
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);


public:
	IMPLEMENT_SET_GET(bool, Show);
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_GET(bool, Overed);

	void					SetDisable(bool bDisable);
	void					SetSound(const WCHAR* wsClick, const WCHAR* wsOver);
	void					SetSprite(const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable);
};


class _DECLSPEC KGDialogAniButton : public KGDialogResponseEvent, protected KGDialogPixel
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGSound*				m_pSound;
	KGRenderSingle*			m_pRender;

	KGString				m_wsDefault;
	KGString				m_wsClick;
	KGString				m_wsOver;
	KGString				m_wsDisable;
	KGString				m_wsRender;
	KGString				m_wsOverSound;
	KGString				m_wsClickSound;
	KGString				m_wsMask;

#pragma warning(disable : 4251)
	D3DXCOLOR				m_Color;
	D3DXVECTOR3				m_vPos;
#pragma warning(default : 4251)

	KGRect					m_rcRect;

	bool					m_Show;
	bool					m_Disable;
	bool					m_Click;
	bool					m_Mask;
	bool					m_Overed;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogAniButton(KGAnimate* pAnimate, KGSound* pSound, UINT id,
				   const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable,
				   KGRect& rcRect, KGResponseDialog* pResponseEvent, const WCHAR* wsMask);
	KGDialogAniButton(const KGDialogAniButton& Button);
	~KGDialogAniButton();


public:
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);


public:
	IMPLEMENT_SET_GET(bool, Show);
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_GET(bool, Overed);

	void					SetDisable(bool bDisable);
	void					SetSound(const WCHAR* wsClick, const WCHAR* wsOver);
	void					SetSprite(const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable);
};


class _DECLSPEC KGDialogRadioButton : public KGDialogResponseEvent, protected KGDialogPixel
{
private:
	KGSprite*				m_pSprite;
	KGSound*				m_pSound;

	KGString				m_wsDefault;
	KGString				m_wsClick;
	KGString				m_wsOver;
	KGString				m_wsDisable;
	KGString				m_wsRender;
	KGString				m_wsOverSound;
	KGString				m_wsClickSound;

#pragma warning(disable : 4251)
	D3DXCOLOR				m_Color;
	D3DXVECTOR3				m_vPos;
#pragma warning(default : 4251)

	KGRect					m_rcRect;

	bool					m_Show;
	bool					m_Disable;
	bool					m_Click;
	bool					m_Mask;
	bool					m_Overed;
	bool					m_Select;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;
	UINT					m_group;


public:
	KGDialogRadioButton(KGSprite* pSprite, KGSound* pSound, UINT id, UINT group,
				        const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable,
				        D3DXVECTOR3& vPos, KGResponseDialog* pResponseEvent, bool bMask);
	KGDialogRadioButton(const KGDialogRadioButton& Button);
	~KGDialogRadioButton();


public:
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);


public:
	IMPLEMENT_SET_GET(bool, Show);
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_GET(bool, Mask);
	IMPLEMENT_GET(bool, Select);
	IMPLEMENT_GET(bool, Overed);

	void					SetDisable(bool bDisable);
	void					SetSound(const WCHAR* wsClick, const WCHAR* wsOver);
	void					SetSelect(bool bSelected);
	void					SetSprite(const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable);

	KGRect					GetRect()	{return m_rcRect;}
};


class _DECLSPEC KGDialogAniRadioButton : public KGDialogResponseEvent, protected KGDialogPixel
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGSound*				m_pSound;
	KGRenderSingle*			m_pRender;

	KGString				m_wsDefault;
	KGString				m_wsClick;
	KGString				m_wsOver;
	KGString				m_wsDisable;
	KGString				m_wsRender;
	KGString				m_wsOverSound;
	KGString				m_wsClickSound;
	KGString				m_wsMask;

#pragma warning(disable : 4251)
	D3DXCOLOR				m_Color;
	D3DXVECTOR3				m_vPos;
#pragma warning(default : 4251)

	KGRect					m_rcRect;

	bool					m_Show;
	bool					m_Disable;
	bool					m_Click;
	bool					m_Mask;
	bool					m_Overed;
	bool					m_Select;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;
	UINT					m_group;


public:
	KGDialogAniRadioButton(KGAnimate* pAnimate, KGSound* pSound, UINT id, UINT group,
						   const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable,
						   KGRect& rcRect, KGResponseDialog* pResponseEvent, const WCHAR* wsMask);
	KGDialogAniRadioButton(const KGDialogAniRadioButton& Button);
	~KGDialogAniRadioButton();


public:
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);


public:
	IMPLEMENT_SET_GET(bool, Show);
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_GET(bool, Mask);
	IMPLEMENT_GET(bool, Select);
	IMPLEMENT_GET(bool, Overed);

	void					SetDisable(bool bDisable);
	void					SetSound(const WCHAR* wsClick, const WCHAR* wsOver);
	void					SetSelect(bool bSelected);
	void					SetSprite(const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable);

	KGRect					GetRect()	{return m_rcRect;}
};


class _DECLSPEC KGDialogStatic
{
private:
	KGSprite*				m_pSprite;

	IDirect3DDevice9*		m_pd3dDevice;
	IDirect3DTexture9*		m_pTexture;
	IDirect3DSurface9*		m_pSurface;
	ID3DXRenderToSurface*	m_pRenderToSurface;
	ID3DXSprite*			m_pd3dSprite;
	ID3DXFont*				m_pFont;

	DWORD					m_Format;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_Pos;
	D3DXCOLOR				m_Color;
	D3DXCOLOR				m_ShadowColor;
#pragma warning(default : 4251)

	KGString				m_wsText;
	KGString				m_wsSprite;

	KGRect					m_rcRect;

	bool					m_Disable;
	bool					m_Visible;

	int						m_Shadow;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogStatic(KGSprite* pSprite, UINT id, ID3DXFont* pFont, const WCHAR* wsText, KGRect& rcRect, D3DXCOLOR& color, DWORD Format);
	~KGDialogStatic();


public:
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);


public:
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_SET_GET(bool, Visible);
	IMPLEMENT_SET_GET(D3DXVECTOR3, Pos);

	void					SetDisable(bool bDisable);
	void					SetText(const WCHAR* wsText, D3DXCOLOR& Color = D3DXCOLOR(1, 1, 1, 1));
	void					SetShadow(int Shadow, D3DXCOLOR& Color = D3DXCOLOR(0, 0, 0, 1));
};


class _DECLSPEC KGDialogTimeBar : public KGDialogResponseEvent
{
protected:
	KGSprite*				m_pSprite;

	KGString				m_wsTimeBar;
	KGString				m_wsBack;

	KGRect					m_rcRect;

	float					m_fTime;
	float					m_fElapsedTime;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_vRes;
	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3				m_vBack;
	D3DXCOLOR				m_Color;
#pragma warning(default : 4251)

	bool					m_Disable;
	bool					m_Visible;
	bool					m_bCallback;

	DWORD					m_LerpType;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogTimeBar(KGSprite* pSprite, UINT id,
					const WCHAR* wsTimeBar, const WCHAR* wsBack,
					D3DXVECTOR3& vPos, D3DXVECTOR3& vBack, float fTime, DWORD LerpType = KG_LERP_RIGHT, KGResponseDialog* pCallback = NULL);
	virtual ~KGDialogTimeBar();


public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	

public:
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_SET_GET(bool, Visible);
	IMPLEMENT_SET_GET(float, fTime);
	IMPLEMENT_SET_GET(float, fElapsedTime);

	void					Reset();
	void					SetDisable(bool bDisable);
	void					SetStep(float fElapsedTime);
	void					SetSprite(const WCHAR* wsTimeBar, const WCHAR* wsBack);

	D3DXVECTOR3				Delta();
};


class _DECLSPEC KGDialogProgress : public KGDialogResponseEvent
{
protected:
	KGSprite*				m_pSprite;

	KGString				m_wsTimeBar;
	KGString				m_wsBack;

	KGRect					m_rcRect;

	float					m_Range;
	float					m_Pos;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_vRes;
	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3				m_vBack;
	D3DXCOLOR				m_Color;
#pragma warning(default : 4251)

	bool					m_Disable;
	bool					m_Visible;
	bool					m_bCallback;

	DWORD					m_LerpType;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogProgress(KGSprite* pSprite, UINT id,
					 const WCHAR* wsTimeBar, const WCHAR* wsBack,
					 D3DXVECTOR3& vPos, D3DXVECTOR3& vBack, float fRange, DWORD LerpType = KG_LERP_RIGHT, KGResponseDialog* pCallback = NULL);
	virtual ~KGDialogProgress();



public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	

public:
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_SET_GET(bool, Visible);
	IMPLEMENT_SET_GET(float, Pos);
	IMPLEMENT_SET_GET(float, Range);

	void					Reset();
	void					SetDisable(bool bDisable);
	void					SetSprite(const WCHAR* wsTimeBar, const WCHAR* wsBack);

	D3DXVECTOR3				Delta();
};


class _DECLSPEC KGDialogGauge : public KGDialogResponseEvent
{
protected:
	KGAnimate*				m_pAnimate;
	KGSprite*				m_pSprite;
	KGRenderSingle*			m_pRender;

	KGString				m_wsGauge;
	KGString				m_wsBack;

	KGRect					m_rcRect;

	float					m_Range;
	float					m_Pos;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_vRes;
	D3DXCOLOR				m_Color;
#pragma warning(default : 4251)

	bool					m_Disable;
	bool					m_Visible;
	bool					m_bAnimate;
	bool					m_bCallback;

	DWORD					m_LerpType;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogGauge(KGSprite* pSprite, UINT id, const WCHAR* wsGauge,
				  KGRect& rcRect, float fRange, KGResponseDialog* pCallback = NULL);
	KGDialogGauge(KGSprite* pSprite, UINT id, const WCHAR* wsGauge, const WCHAR* wsBack,
				  KGRect& rcRect, float fRange, KGResponseDialog* pCallback = NULL);
	KGDialogGauge(KGAnimate* pAnimate, UINT id, const WCHAR* wsGauge,
				  KGRect& rcRect, float fRange, KGResponseDialog* pCallback = NULL);
	KGDialogGauge(KGAnimate* pAnimate, UINT id, const WCHAR* wsGauge, const WCHAR* wsBack,
				  KGRect& rcRect, float fRange, KGResponseDialog* pCallback = NULL);
	virtual ~KGDialogGauge();


public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	

public:
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_SET_GET(bool, Visible);
	IMPLEMENT_SET_GET(float, Pos);
	IMPLEMENT_SET_GET(float, Range);

	void					Reset();
	void					SetDisable(bool bDisable);
	void					SetSprite(const WCHAR* wsGauge);

	D3DXVECTOR3				Delta();
};


class _DECLSPEC KGDialogTimeGauge : public KGDialogResponseEvent
{
protected:
	KGAnimate*				m_pAnimate;
	KGSprite*				m_pSprite;
	KGRenderSingle*			m_pRender;

	KGString				m_wsGauge;
	KGString				m_wsBack;

	KGRect					m_rcRect;

	float					m_Range;
	float					m_Pos;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_vRes;
	D3DXCOLOR				m_Color;
#pragma warning(default : 4251)

	bool					m_Disable;
	bool					m_Visible;
	bool					m_bAnimate;
	bool					m_bCallback;

	DWORD					m_LerpType;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogTimeGauge(KGSprite* pSprite, UINT id, const WCHAR* wsGauge,
				  KGRect& rcRect, float fRange, KGResponseDialog* pCallback = NULL);
	KGDialogTimeGauge(KGSprite* pSprite, UINT id, const WCHAR* wsGauge, const WCHAR* wsBack,
				  KGRect& rcRect, float fRange, KGResponseDialog* pCallback = NULL);
	KGDialogTimeGauge(KGAnimate* pAnimate, UINT id, const WCHAR* wsGauge,
				  KGRect& rcRect, float fRange, KGResponseDialog* pCallback = NULL);
	KGDialogTimeGauge(KGAnimate* pAnimate, UINT id, const WCHAR* wsGauge, const WCHAR* wsBack,
				  KGRect& rcRect, float fRange, KGResponseDialog* pCallback = NULL);
	virtual ~KGDialogTimeGauge();


public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	

public:
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_SET_GET(bool, Visible);
	IMPLEMENT_SET_GET(float, Pos);
	IMPLEMENT_SET_GET(float, Range);

	void					Reset();
	void					SetDisable(bool bDisable);
	void					SetSprite(const WCHAR* wsGauge);

	D3DXVECTOR3				Delta();
};


class _DECLSPEC KGDialogListBox
{
private:
	KGSprite*				m_pSprite;

	IDirect3DDevice9*		m_pd3dDevice;
	IDirect3DTexture9*		m_pTexture;
	IDirect3DSurface9*		m_pSurface;
	ID3DXRenderToSurface*	m_pRenderToSurface;
	ID3DXSprite*			m_pd3dSprite;
	ID3DXFont*				m_pFont;

	KGRect					m_rcRect;

	int						m_iRow;
	int						m_iHeight;
	int						m_Shadow;

#pragma warning(disable : 4251)
	D3DXCOLOR				m_ShadowColor;
#pragma warning(default : 4251)

	bool					m_Disable;

	KGVector				m_Table;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogListBox(KGSprite* pSprite, UINT id, ID3DXFont* pFont, KGRect& rcRect);
	virtual ~KGDialogListBox();


public:
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);


public:
	IMPLEMENT_GET(bool, Disable);

	void					SetShadow(int Shadow, D3DXCOLOR& Color = D3DXCOLOR(0, 0, 0, 1));
	void					SetText(const WCHAR* wsText, D3DXCOLOR& Color = D3DXCOLOR(1, 1, 1, 1));
	void					SetDisable(bool bDisable);
	void					Clear();

	const wchar_t*			GetText(UINT id);
};


class _DECLSPEC KGDialogEditBox
{
private:
	KGSprite*				m_pSprite;

	IDirect3DDevice9*		m_pd3dDevice;
	IDirect3DTexture9*		m_pTexture;
	IDirect3DSurface9*		m_pSurface;
	ID3DXRenderToSurface*	m_pRenderToSurface;
	ID3DXSprite*			m_pd3dSprite;
	ID3DXFont*				m_pFont;

	DWORD					m_Format;

	KGRect					m_rcRect;
	KGString				m_Temp;
	KGString				m_Result;
	KGString				m_Composition;
	KGString				m_CompositionResult;

#pragma warning(disable : 4251)
	D3DXCOLOR				m_Color;
	D3DXCOLOR				m_ShadowColor;
#pragma warning(default : 4251)

	bool					m_Disable;
	bool					m_Acquire;
	bool					m_Password;

	int						m_iWidth;
	int						m_Shadow;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogEditBox(KGSprite* pSprite, UINT id, ID3DXFont* pFont, KGRect& rcRect, D3DXCOLOR& Color, DWORD Format);
	virtual ~KGDialogEditBox();


public:
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);

	LRESULT CALLBACK		OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);		


public:
	IMPLEMENT_SET_GET(D3DXCOLOR, Color);
	IMPLEMENT_SET_GET(bool, Disable);
	IMPLEMENT_GET(bool, Acquire);
	IMPLEMENT_GET(bool, Password);

	void					SetShadow(int Shadow, D3DXCOLOR& Color = D3DXCOLOR(0, 0, 0, 1));
	void					SetAcquire(bool bAcquire);
	void					SetPassword(bool bPassword);
	void					Clear();

	const wchar_t*			GetText();

	const KGRect&			GetRect();

	bool					empty();


private:
	void					Convert_NoLock(bool bCaret = true);
};


class _DECLSPEC KGDialogNumber
{
protected:
	KGSprite*				m_pSprite;

	CRITICAL_SECTION		m_csLock;

	DWORD					m_Format;

	float					m_fWidthTab;

	KGVector				m_Table;

	unsigned __int64		m_Number;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_vPos;
	D3DXCOLOR				m_Color;
#pragma warning(default : 4251)

	bool					m_Disable;
	bool					m_Visible;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogNumber(KGSprite* pSprite, UINT id, const WCHAR* wsPreName,
				   D3DXVECTOR3& vPos, float fWidthTab, DWORD Format);
	virtual ~KGDialogNumber();


protected:
	void					DrawTextLeft(unsigned __int64 _number, D3DXVECTOR3 vPos, float fWidthTab);
	void					DrawTextRight(unsigned __int64 _number, D3DXVECTOR3 vPos, float fWidthTab);
	void					DrawTextCenter(unsigned __int64 _number, D3DXVECTOR3 vPos, float fWidthTab);


public:
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	

public:
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_SET_GET(bool, Visible);
	IMPLEMENT_SET_GET(unsigned __int64, Number);

	void					SetDisable(bool bDisable);
	void					Reset(unsigned __int64 _number);
	void					Plus(unsigned __int64 _number);
	void					Minus(unsigned __int64 _number);
	void					SetSprite(const WCHAR* wsPreName);
};


class _DECLSPEC KGDialogCheckBox : public KGDialogResponseEvent, protected KGDialogPixel
{
private:
	KGSprite*				m_pSprite;
	KGSound*				m_pSound;

	KGString				m_wsDefault;
	KGString				m_wsClick;
	KGString				m_wsOver;
	KGString				m_wsDisable;
	KGString				m_wsRender;
	KGString				m_wsChecked;
	KGString				m_wsOverSound;
	KGString				m_wsClickSound;

#pragma warning(disable : 4251)
	D3DXCOLOR				m_Color;
	D3DXVECTOR3				m_vPos;
#pragma warning(default : 4251)

	KGRect					m_rcRect;

	bool					m_Show;
	bool					m_Disable;
	bool					m_Click;
	bool					m_Mask;
	bool					m_Overed;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogCheckBox(KGSprite* pSprite, KGSound* pSound, UINT id,
				     const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable,
				     D3DXVECTOR3& vPos, KGResponseDialog* pResponseEvent, bool bMask);
	KGDialogCheckBox(const KGDialogCheckBox& Button);
	~KGDialogCheckBox();


public:
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);


public:
	IMPLEMENT_SET_GET(bool, Show);
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_GET(bool, Overed);

	bool					GetChecked();

	void					SetChecked(bool bChecked);
	void					SetDisable(bool bDisable);
	void					SetSound(const WCHAR* wsClick, const WCHAR* wsOver);
	void					SetSprite(const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable);
};


class _DECLSPEC KGDialogAniCheckBox : public KGDialogResponseEvent, protected KGDialogPixel
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGSound*				m_pSound;
	KGRenderSingle*			m_pRender;
	KGRenderSingle*			m_pChecked;

	KGString				m_wsDefault;
	KGString				m_wsClick;
	KGString				m_wsOver;
	KGString				m_wsDisable;
	KGString				m_wsRender;
	KGString				m_wsChecked;
	KGString				m_wsOverSound;
	KGString				m_wsClickSound;
	KGString				m_wsMask;

#pragma warning(disable : 4251)
	D3DXCOLOR				m_Color;
	D3DXVECTOR3				m_vPos;
#pragma warning(default : 4251)

	KGRect					m_rcRect;

	bool					m_Show;
	bool					m_Disable;
	bool					m_Click;
	bool					m_Mask;
	bool					m_Overed;

	CRITICAL_SECTION		m_csLock;


	friend class KGDialog;


public:
	UINT					m_id;


public:
	KGDialogAniCheckBox(KGAnimate* pAnimate, KGSound* pSound, UINT id,
				   const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable,
				   KGRect& rcRect, KGResponseDialog* pResponseEvent, const WCHAR* wsMask);
	KGDialogAniCheckBox(const KGDialogAniCheckBox& Button);
	~KGDialogAniCheckBox();


public:
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);


public:
	IMPLEMENT_SET_GET(bool, Show);
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_GET(bool, Overed);

	bool					GetChecked();

	void					SetChecked(bool bChecked);
	void					SetDisable(bool bDisable);
	void					SetSound(const WCHAR* wsClick, const WCHAR* wsOver);
	void					SetSprite(const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable);
};


class _DECLSPEC KGDialog : public KGDialogResponseEvent
{
private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGSound*				m_pSound;
	KGRenderMulti*			m_pRenderMulti;

	KGVector				m_Sprite;
	KGVector				m_Static;
	KGVector				m_Button;
	KGVector				m_AniButton;
	KGVector				m_TimeBar;
	KGVector				m_Progress;
	KGVector				m_ListBox;
	KGVector				m_Gauge;
	KGVector				m_TimeGauge;
	KGVector				m_Number;
	KGVector				m_EditBox;
	KGVector				m_CheckBox;
	KGVector				m_AniCheckBox;

	KGMapper				m_RadioButton;
	KGMapper				m_AniRadioButton;

	bool					m_Visible;
	bool					m_Disable;
	bool					m_Return;
	bool					m_Tab;

	int						m_iEditBox;

	CRITICAL_SECTION		m_csLock;


public:
	KGDialog(KGSprite* pSprite, KGSound* pSound = NULL, KGResponseDialog* pResponseEvent = NULL);
	KGDialog(KGAnimate* pAnimate, KGSound* pSound = NULL, KGResponseDialog* pResponseEvent = NULL);
	virtual ~KGDialog();


public:
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

	LRESULT CALLBACK		OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);


public:
	IMPLEMENT_PGET(KGSprite*, Sprite);
	IMPLEMENT_PGET(KGAnimate*, Animate);
	IMPLEMENT_PGET(KGSound*, Sound);

	IMPLEMENT_SET_GET(bool, Visible);
	IMPLEMENT_GET(bool, Disable);
	IMPLEMENT_SET_GET(bool, Return);
	IMPLEMENT_SET_GET(bool, Tab);

	void					SetSprite(const WCHAR* wsName, D3DXVECTOR3& vPos, D3DXCOLOR& color);
	void					SetSprite(UINT id, const WCHAR* wsName, D3DXVECTOR3& vPos, D3DXCOLOR& color);
	void					SetAnimate(const WCHAR* wsName, D3DXVECTOR3& vPos, bool bPlay = true, int iLoop = -1);
	void					SetResponse(KGResponseDialog* pResponseEvent);
	void					SetDisable(bool bDisable);


public:
	void					AddButton(UINT id, const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable, D3DXVECTOR3& vPos, bool bMask = false);
	void					AddAniButton(UINT id, const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable, KGRect& rcRect, const WCHAR* wsMask = NULL);
	void					AddRadioButton(UINT id, UINT group, const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable, D3DXVECTOR3& vPos, bool bSelected = false, bool bMask = false);
	void					AddAniRadioButton(UINT id, UINT group, const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable, KGRect& rcRect, bool bSelected = false, const WCHAR* wsMask = NULL);
	void					AddStatic(UINT id, ID3DXFont* pFont, const WCHAR* wsText, KGRect& rcRect, D3DXCOLOR& color = D3DXCOLOR(1, 1, 1, 1), DWORD Format = DT_LEFT);
	void					AddTimeBar(UINT id, const WCHAR* wsTimeBar, D3DXVECTOR3& vPos, float fTime, DWORD LerpType = KG_LERP_RIGHT);
	void					AddTimeBar(UINT id, const WCHAR* wsTimeBar, const WCHAR* wsBack, D3DXVECTOR3& vPos, D3DXVECTOR3& vBack, float fRange, DWORD LerpType = KG_LERP_RIGHT);
	void					AddProgress(UINT id, const WCHAR* wsTimeBar, D3DXVECTOR3& vPos, float fTime, DWORD LerpType = KG_LERP_RIGHT);
	void					AddProgress(UINT id, const WCHAR* wsTimeBar, const WCHAR* wsBack, D3DXVECTOR3& vPos, D3DXVECTOR3& vBack, float fRange, DWORD LerpType = KG_LERP_RIGHT);
	void					AddGauge(UINT id, const WCHAR* wsGauge, const WCHAR* wsBack, KGRect& rcRect, float fRange);
	void					AddGauge(UINT id, const WCHAR* wsGauge, KGRect& rcRect, float fRange);
	void					AddTimeGauge(UINT id, const WCHAR* wsGauge, const WCHAR* wsBack, KGRect& rcRect, float fRange);
	void					AddTimeGauge(UINT id, const WCHAR* wsGauge, KGRect& rcRect, float fRange);
	void					AddListBox(UINT id, ID3DXFont* pFont, KGRect& rcRect);
	void					AddNumber(UINT id, const WCHAR* wsPreName, D3DXVECTOR3& vPos, float fWidthTab = 0.f, DWORD Format = DT_LEFT);
	void					AddEditBox(UINT id, ID3DXFont* pFont, KGRect& rcRect, D3DXCOLOR& color, DWORD Format = DT_LEFT | DT_VCENTER);
	void					AddCheckBox(UINT id, const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable, D3DXVECTOR3& vPos, bool bMask = false);
	void					AddAniCheckBox(UINT id, const WCHAR* wsDefault, const WCHAR* wsClick, const WCHAR* wsOver, const WCHAR* wsDisable, KGRect& rcRect, const WCHAR* wsMask = NULL);

	KGDialogButton*			GetButton(UINT id);
	KGDialogAniButton*		GetAniButton(UINT id);
	KGDialogTimeBar*		GetTimeBar(UINT id);
	KGDialogProgress*		GetProgress(UINT id);
	KGDialogGauge*			GetGauge(UINT id);
	KGDialogTimeGauge*		GetTimeGauge(UINT id);
	KGDialogRadioButton*	GetRadioButton(UINT id);
	KGDialogAniRadioButton*	GetAniRadioButton(UINT id);
	KGDialogListBox*		GetListBox(UINT id);
	KGDialogNumber*			GetNumber(UINT id);
	KGDialogEditBox*		GetEditBox(UINT id);
	KGDialogStatic*			GetStatic(UINT id);
	KGDialogCheckBox*		GetCheckBox(UINT id);
	KGDialogAniCheckBox*	GetAniCheckBox(UINT id);
};


}


#endif
