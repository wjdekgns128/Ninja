#ifndef	_KG_STRING_H
#define	_KG_STRING_H

#ifndef UNICODE
	#error "KG-Kamma requires a Unicode build. See the nearby comments for details"
#endif

#if defined(KG_DLL_EXPORTS)
	#define	_DECLSPEC		__declspec(dllexport)
#else
	#define	_DECLSPEC
#endif

#ifdef WIN32
	#define _CRT_SECURE_NO_DEPRECATE
	#ifndef	_INC_WCHAR
		#include <wchar.h>
	#endif
	#ifndef	_INC_WINDOWS
		#include <windows.h>
	#endif
#else
#endif


namespace KG
{

#undef	max


class _DECLSPEC KGString
{
private:
	size_t					m_Size;
	size_t					m_Max;

	char*					m_pStuff;

	WCHAR*					m_pBuffer;
	WCHAR*					m_pTemp;

	HANDLE					m_hHandle;


private:
	size_t					Square(size_t sqr);


protected:
	void					Resize(size_t Size);

	bool					Compare(const WCHAR* _string);
	bool					Compare(KGString& _string);


public:
	size_t					size();
	size_t					length();
	size_t					max();

	bool					isEmpty();
	bool					empty();

	void					insert(size_t pos, const WCHAR* _string);
	void					clear();
	void					upper();
	void					lower();
	void					backspace();
	void					password();

	const WCHAR*			c_str();

	size_t					key();


public:
	KGString();
	KGString(const char*, ...);
	KGString(const WCHAR*, ...);
	KGString(const KGString&);
	~KGString();


public:
	WCHAR					operator [] (int pos) const;

	operator				char*	();
	operator const			char*	() const;
	operator				WCHAR*  ();
	operator const			WCHAR*  () const;

	KGString&				operator = (const char*);
	KGString&				operator = (const WCHAR*);
	KGString&				operator = (const KGString&);
	KGString&				operator += (const WCHAR*);
	KGString&				operator += (const KGString&);

	bool					operator != (const WCHAR*);
	bool					operator == (const WCHAR*);
	bool					operator != (KGString&);
	bool					operator == (KGString&);
};


}


#endif
