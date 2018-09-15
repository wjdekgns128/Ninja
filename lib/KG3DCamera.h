#ifndef	_KG_3D_CAMERA_H
#define	_KG_3D_CAMERA_H

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
#endif


#ifndef	_KG_MISC_H
	#include "KGMisc.h"
#endif
#ifndef	_KG_STRING_H
	#include "KGString.h"
#endif
#ifndef	_KG_3D_SPLINE_H
	#include "KG3DSpline.h"
#endif


namespace KG
{
	namespace _3D
	{


class _DECLSPEC KG3DCamera : public KG3DSpline
{
private:
	IDirect3DDevice9*		m_pd3dDevice;

	float					m_fHeight;
	float					m_fWidth;
	float					m_fovy;
	float					m_Yaw;
	float					m_Pitch;
	float					m_Roll;
	float					m_Time;

	bool					m_Action;

#pragma warning(disable : 4251)
	D3DXVECTOR3				m_Position;
	D3DXVECTOR3				m_Up;
	D3DXVECTOR3				m_Look;
	D3DXVECTOR3				m_Right;
#pragma warning(default : 4251)

	CRITICAL_SECTION		m_csLock;


private:
	float					RestrictAngleTo360Range_NoLock(float angle) const;
	void					CalculateViewMatrix_NoLock(D3DXMATRIXA16* pMatrix);


public:
	KG3DCamera(IDirect3DDevice9* pd3dDevice);
	KG3DCamera(IDirect3DDevice9* pd3dDevice, D3DXVECTOR3 Position);
	KG3DCamera(const KG3DCamera& _camera);
	virtual ~KG3DCamera();


public:
	KG3DCamera& operator = (const KG3DCamera& _camera);


public:
	IMPLEMENT_GET(float, Yaw);
	IMPLEMENT_GET(float, Pitch);
	IMPLEMENT_GET(float, Roll);
	IMPLEMENT_GET_SET(float, Time);
	IMPLEMENT_GET_SET(D3DXVECTOR3, Position);
	IMPLEMENT_GET_SET(bool, Action);

	void					CalculateViewMatrix(D3DXMATRIXA16* pMatrix);
	void					SetYawPitchRoll(float Yaw, float Pitch, float Roll);

	void					SetMoveForward(float amount);
	void					SetMoveRight(float amount);
	void					SetMoveUp(float amount);

	void					SetYaw(float amount);
	void					SetPitch(float amount);
	void					SetRoll(float amount);

	void					BeginScene(float fElapsedTime);
	void					EndScene();
};


	}
}


#endif


