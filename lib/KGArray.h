#ifndef	_KG_ARRAY_H
#define	_KG_ARRAY_H


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
	#include <assert.h>
	#ifndef _INC_NEW
		#include <new.h>
	#endif
#else
#endif


namespace KG
{


template<typename TYPE>
class _DECLSPEC KGArray
{
public:
    KGArray()				{m_pData = NULL; m_nSize = 0; m_nMaxSize = 0;}
    KGArray(const KGArray<TYPE>& a)	{for(int i = 0; i < a.m_nSize; i++) Add(a.m_pData[i]);}
    ~KGArray()				{RemoveAll();}


public:
    const TYPE& operator[](int nIndex) const	{return GetAt(nIndex);}
    TYPE& operator[](int nIndex)	{return GetAt(nIndex);}

    KGArray& operator=(const KGArray<TYPE>& a)	{if(this == &a) return *this; RemoveAll(); for(int i = 0; i < a.m_nSize; i++) Add(a.m_pData[i]); return *this;}

    HRESULT					SetSize(int nNewMaxSize);
    HRESULT					Add(const TYPE& value);
    HRESULT					insert(int nIndex, const TYPE& value);
    HRESULT					SetAt(int nIndex, const TYPE& value);
    TYPE&					GetAt(int nIndex)	{assert(nIndex >= 0 && nIndex < m_nSize); return m_pData[nIndex];}
    int						GetSize() const		{return m_nSize;}
    TYPE*					GetData()			{return m_pData;}
    bool					Contains(const TYPE& value)	{return (-1 != IndexOf(value));}
	bool					IsEmpty()			{return (m_nSize == 0);}

    int						IndexOf(const TYPE& value)	{return (m_nSize > 0) ? IndexOf(value, 0, m_nSize) : -1;}
    int						IndexOf(const TYPE& value, int iStart)	{return IndexOf(value, iStart, m_nSize - iStart);}
    int						IndexOf(const TYPE& value, int nIndex, int nNumElements);

    int						LastIndexOf(const TYPE& value)	{return (m_nSize > 0) ? LastIndexOf(value, m_nSize - 1, m_nSize) : -1;}
    int						LastIndexOf(const TYPE& value, int nIndex)	{return LastIndexOf(value, nIndex, nIndex+1);}
    int						LastIndexOf(const TYPE& value, int nIndex, int nNumElements);

    HRESULT					Remove(int nIndex);
    void					RemoveAll()	{SetSize(0);}


protected:
    TYPE*					m_pData;
    int						m_nSize;
    int						m_nMaxSize;

    HRESULT					SetSizeInternal(int nNewMaxSize);
};


template<typename TYPE>
HRESULT KGArray<TYPE>::SetSizeInternal(int nNewMaxSize)
{
    if(nNewMaxSize < 0)
    {
        assert(false);
        return E_INVALIDARG;
    }

    if(nNewMaxSize == 0)
    {
        if(m_pData)
        {
            free(m_pData);
            m_pData			= NULL;
        }

        m_nMaxSize			= 0;
        m_nSize				= 0;
    }
    else if(m_pData == NULL || nNewMaxSize > m_nMaxSize)
    {
        int					nGrowBy	= (m_nMaxSize == 0) ? 16 : m_nMaxSize;

        nNewMaxSize			= __max(nNewMaxSize, m_nMaxSize + nGrowBy);

        TYPE*				pDataNew	= (TYPE*)realloc(m_pData, nNewMaxSize * sizeof(TYPE));

        if(pDataNew == NULL)
            return E_OUTOFMEMORY;

        m_pData				= pDataNew;
        m_nMaxSize			= nNewMaxSize;
    }

    return S_OK;
}


template<typename TYPE>
HRESULT KGArray<TYPE>::SetSize(int nNewMaxSize)
{
    int						nOldSize	= m_nSize;

    if(nOldSize > nNewMaxSize)
    {
        for(int i = nNewMaxSize; i < nOldSize; ++i)
            m_pData[i].~TYPE();
    }

    HRESULT					hr	= SetSizeInternal(nNewMaxSize);

    if(nOldSize < nNewMaxSize)
    {
        for(int i = nOldSize; i < nNewMaxSize; ++i)
            ::new (&m_pData[i]) TYPE;
    }

    return hr;
}


template<typename TYPE>
HRESULT KGArray<TYPE>::Add(const TYPE& value)
{
    HRESULT					hr;

    if(FAILED(hr = SetSizeInternal(m_nSize + 1)))
        return hr;

    ::new (&m_pData[m_nSize]) TYPE;

    m_pData[m_nSize]		= value;

    ++m_nSize;

    return S_OK;
}


template<typename TYPE>
HRESULT KGArray<TYPE>::insert(int nIndex, const TYPE& value)
{
    HRESULT					hr;

    if(nIndex < 0 || nIndex > m_nSize)
    {
        assert(false);
        return E_INVALIDARG;
    }

    if(FAILED(hr = SetSizeInternal(m_nSize + 1)))
        return hr;

    MoveMemory(&m_pData[nIndex+1], &m_pData[nIndex], sizeof(TYPE) * (m_nSize - nIndex));

    ::new (&m_pData[nIndex]) TYPE;

    m_pData[nIndex]			= value;

    ++m_nSize;

    return S_OK;
}


template<typename TYPE>
HRESULT KGArray<TYPE>::SetAt(int nIndex, const TYPE& value)
{
    if(nIndex < 0 || nIndex >= m_nSize)
    {
        assert(false);
        return E_INVALIDARG;
    }

    m_pData[nIndex]			= value;

    return S_OK;
}


template<typename TYPE>
int KGArray<TYPE>::IndexOf(const TYPE& value, int iStart, int nNumElements)
{
    if(iStart < 0 || iStart >= m_nSize || nNumElements < 0 || iStart + nNumElements > m_nSize)
    {
        assert(false);
        return -1;
    }

    for(int i = iStart; i < (iStart + nNumElements); i++)
    {
        if(value == m_pData[i])
            return i;
    }

    return -1;
}


template<typename TYPE>
int KGArray<TYPE>::LastIndexOf(const TYPE& value, int iEnd, int nNumElements)
{
    if(iEnd < 0 || iEnd >= m_nSize || nNumElements < 0 || iEnd - nNumElements < 0)
    {
        assert(false);
        return -1;
    }

    for(int i = iEnd; i > (iEnd - nNumElements); i--)
    {
        if(value == m_pData[i])
            return i;
    }

    return -1;
}


template<typename TYPE>
HRESULT KGArray<TYPE>::Remove(int nIndex)
{
    if(nIndex < 0 || nIndex >= m_nSize)
    {
        assert(false);
        return E_INVALIDARG;
    }

    m_pData[nIndex].~TYPE();

    MoveMemory(&m_pData[nIndex], &m_pData[nIndex+1], sizeof(TYPE) * (m_nSize - (nIndex+1)));

    --m_nSize;

    return S_OK;
}


}


#endif
