#ifndef	_KG_RECT_H
#define	_KG_RECT_H


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
	#ifndef _D3D9X_H_
		#include <d3dx9.h>
		#pragma comment(lib, "d3dx9.lib")
	#endif
#endif


namespace KG
{


typedef struct _DECLSPEC KGRect
{
#ifdef __cplusplus
public:
    KGRect() {}
    KGRect(CONST FLOAT*);
    KGRect(CONST D3DXFLOAT16*);
	KGRect::KGRect(int fleft, int ftop, int fright, int fbottom);
    KGRect(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom);

    operator				FLOAT* ();
    operator CONST			FLOAT* () const;
	operator				RECT*  ();
	operator CONST			RECT*  () const;

    KGRect&					operator -= (FLOAT);
    KGRect&					operator += (FLOAT);
	KGRect&					operator *= (FLOAT);
    KGRect&					operator /= (FLOAT);
	KGRect&					operator += (D3DXVECTOR2&);
	KGRect&					operator -= (D3DXVECTOR2&);
	KGRect&					operator *= (D3DXVECTOR2&);
	KGRect&					operator /= (D3DXVECTOR2&);
	KGRect&					operator /= (D3DXVECTOR3&);
	KGRect&					operator *= (D3DXVECTOR3&);
	KGRect&					operator += (D3DXVECTOR3&);
	KGRect&					operator -= (D3DXVECTOR3&);
	KGRect&					operator -= (KGRect&);
	KGRect&					operator += (KGRect&);
	KGRect&					operator /= (KGRect&);
	KGRect&					operator *= (KGRect&);

	KGRect					operator +  (const D3DXVECTOR2&);
	KGRect					operator -  (const D3DXVECTOR2&);
	KGRect					operator /  (const D3DXVECTOR2&);
	KGRect					operator *  (const D3DXVECTOR2&);
	KGRect					operator +  (const D3DXVECTOR3&);
	KGRect					operator -  (const D3DXVECTOR3&);
	KGRect					operator /  (const D3DXVECTOR3&);
	KGRect					operator *  (const D3DXVECTOR3&);
	KGRect					operator +  (const KGRect&);
	KGRect					operator -  (const KGRect&);
	KGRect					operator /  (const KGRect&);
	KGRect					operator *  (const KGRect&);
	KGRect&					operator =  (const RECT&);

	bool					operator == (const KGRect&);

	float					width();
	float					height();
	float					HalfWidth();
	float					HalfHeight();

	RECT&					rect();

	bool					isOverlap(int, int);
	bool					isOverlap(float, float);
	bool					isOverlap(const D3DXVECTOR2&);
	bool					isOverlap(const D3DXVECTOR3&);
	bool					isOverlap(const KGRect&);

	static bool				isOverlap(const KGRect&, const KGRect&);

	bool					isZero();

	static KGRect			lerp(const KGRect&, const KGRect&, float);
#endif


public:
	float					left;
	float					top;
	float					right;
	float					bottom;

	RECT					rc;
} KGRect, *LPKGRect;


extern "C++" _DECLSPEC int KGRand(int iMin, int iMax);
extern "C++" _DECLSPEC float KGRand(float fMin, float fMax);


}


#endif