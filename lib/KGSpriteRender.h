#ifndef	_KG_SPRITE_RENDER_H
#define	_KG_SPRITE_RENDER_H


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
#ifndef	_KG_RECT_H
	#include "KGRect.h"
#endif
#ifndef	_KG_3D_QUAKE_H
	#include "KG3DQuake.h"
#endif


namespace KG
{


class _DECLSPEC KGSpriteRender : public KG::_3D::KG3DQuake
{
public:
	typedef struct _KGVertices_tag
	{
		enum {FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1};

		D3DXVECTOR3			p;
		D3DXVECTOR3			n;
		D3DXVECTOR2			t;

		_KGVertices_tag()
		{
			memset(this, 0, sizeof(_KGVertices_tag));
		}

		_KGVertices_tag(const D3DXVECTOR3& _p, const D3DXVECTOR2& _t, const D3DXVECTOR3& _n)
		{
			p				= _p;
			t				= _t;
			n				= _n;
		}
	} KGVertices;


protected:
	IDirect3DDevice9*		m_pd3dDevice;
	IDirect3DVertexBuffer9*	m_pVertexBuffer;

	KGVertices*				m_pVertices;

	float					m_fWidth;
	float					m_fHeight;
	float					m_fovy;

	D3DMATERIAL9            m_alphaMaterial;


private:
	CRITICAL_SECTION		m_csLock;


public:
	KGSpriteRender(IDirect3DDevice9* pd3dDevice);
	virtual ~KGSpriteRender();


private:
	void					Set_NoLock(KGRect _p, KGRect _t, D3DXCOLOR _c);
	void					Camera_NoLock(D3DXVECTOR3& eye = D3DXVECTOR3(0, 0, -2.41f), D3DXVECTOR3& at = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3& up = D3DXVECTOR3(0, 1, 0));

	bool					CreateVertexBuffer_NoLock();


protected:
	void					Set(KGRect _p, KGRect _t, D3DXCOLOR _c);
	void					Camera(D3DXVECTOR3& eye = D3DXVECTOR3(0, 0, -2.41f), D3DXVECTOR3& at = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3& up = D3DXVECTOR3(0, 1, 0));

	bool					CreateVertexBuffer();


public:
	virtual void			Render(IDirect3DTexture9* pTexture, D3DXVECTOR3& vPos, D3DXCOLOR& Color);
	virtual void			Render(IDirect3DTexture9* pTexture, KGRect& rcSrc, KGRect& rcDst, D3DXCOLOR& Color);


public:
	virtual void CALLBACK	OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
};


}


#endif

