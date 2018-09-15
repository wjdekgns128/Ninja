#ifndef	_KG_3D_SPLINE_H
#define	_KG_3D_SPLINE_H


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
#ifndef	_KG_VECTOR_H
	#include "KGVector.h"
#endif


namespace KG
{
	namespace _3D
	{


typedef struct _DECLSPEC _KG3DTcbSpline_tag
{
#pragma warning(disable : 4251)
	D3DXVECTOR3				vPoint;
#pragma warning(default : 4251)

	float					fTime;
	float					fTension;
	float					fContinuity;
	float					fBias;

	_KG3DTcbSpline_tag(D3DXVECTOR3 _vPoint = D3DXVECTOR3(0, 0, 0), float _fTime = 0.f, float _fTension = -1, float _fContinuity = 0, float _fBias = 0)
	{
		vPoint				= _vPoint;
		fTime				= _fTime;
		fTension			= _fTension;
		fContinuity			= _fContinuity;
		fBias				= _fBias;
	}
} KG3DTcbSpline;


class _DECLSPEC KG3DSpline
{
private:
	KGVector				m_Table;

	KGVector				m_vA;
	KGVector				m_vB;
	KGVector				m_vC;
	KGVector				m_vD;


private:
	void					ComputePoly(int, int, int, int);
	void					GetKeyInfo(float, int&, float&);

	bool					Initialize();

	
public:
	KG3DSpline();
	KG3DSpline(KG3DSpline& _spline);
	virtual ~KG3DSpline();


public:
	D3DXVECTOR3				GetPosition(float);

	void					push_back(KG3DTcbSpline& _spline);
	void					clear();

	int						size();

	bool					isReady();

	KG3DTcbSpline*			GetTable(int pos);


public:

	KG3DSpline&				operator = (KG3DSpline& _spline);
};


	}
}



#endif
