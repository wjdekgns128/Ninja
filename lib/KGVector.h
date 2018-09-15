#ifndef	_KG_VECTOR_H
#define	_KG_VECTOR_H

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
#else
#endif


namespace KG
{


class _DECLSPEC KGVector
{
public:
	struct iterator
	{
		void**				ppNode;

		size_t				size;
		size_t				pos;

		iterator()
		{
			ppNode			= (void**)0;
			size			= 0;
			pos				= 0;
		}

		iterator& operator ++ ()
		{
			pos++;

			return *this;
		}

		iterator& operator ++ (int)
		{
			pos++;

			return *this;
		}

		bool operator != (const iterator& itr)
		{
			return (pos < size);
		}

		void* operator * () const
		{
			if(pos < size)
				return ppNode[pos];

			return (void*)0;
		}
	};


private:
	size_t					m_Max;
	size_t					m_Size;

	void**					m_ppTail;
	void**					m_ppTable;
	void**					m_ppBuffer;

	HANDLE					m_hHandle;


public:
	KGVector();
	KGVector(const KGVector& _vector);
	~KGVector();


public:
	void* operator [] (int pos) const;
	KGVector& operator = (const KGVector& _vector);


private:
	void					resize(size_t size);


public:
	void					push_back(void* pData);
	void					insert(void* pBegin, size_t size);
	void					reserve(size_t size);
	void					clear();

	void					erase(void* pData);
	void					erase(iterator& itr);
	void					swap();

	bool					empty();

	iterator				begin();
	iterator				end();

	size_t					size();
};


}


#endif

