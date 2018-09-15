#ifndef	_KG_MAPPER_H
#define	_KG_MAPPER_H


#ifndef	_KG_STRING_H
	#include "KGString.h"
#endif


namespace KG
{


class _DECLSPEC KGNode
{
public:
	KGNode*					pNext;
	KGNode*					pSeq;
	KGNode*					pCenter;
	
	KGString				wsName;

	void*					pData;

	KGNode()
	{		
		pNext				= NULL;
		pSeq				= NULL;
		pCenter				= NULL;

		pData				= NULL;
	}

	~KGNode()
	{
		pNext				= NULL;
		pSeq				= NULL;
		pCenter				= NULL;

		pData				= NULL;
	}
};


class _DECLSPEC KGMapper
{
public:
	struct iterator
	{
		KGNode*				pNode;

		iterator()
		{
			pNode			= NULL;
		}

		iterator& operator ++ ()
		{
			if(pNode)
				pNode		= pNode->pSeq;

			return *this;
		}

		iterator& operator ++ (int)
		{
			if(pNode)
				pNode		= pNode->pSeq;

			return *this;
		}

		bool operator != (const iterator& itr)
		{
			return (pNode != itr.pNode);
		}

		bool operator == (const iterator& itr)
		{
			return (pNode == itr.pNode);
		}

		void* operator * () const
		{
			if(pNode)
				return pNode->pData;

			return NULL;
		}
	};


private:
	size_t					m_Node;
	size_t					m_Size;

	KGNode*					m_pHead;
	KGNode*					m_pSeq;

	KGString				m_wsName;


public:
	KGMapper();
	~KGMapper();


private:
	void					Remove(KGNode* pNode);
	void					RemoveCenter(KGNode* pNode);


public:
	void					insert(KGString& wsName, void* pData);
	void					insert(size_t key, void* pData);
	void*					find(const char* szName);
	void*					find(const WCHAR* wsName);
	void*					find(KGString& wsName);
	void*					find_key(size_t key);

	iterator				find_itr(KGString& wsName);
	iterator				find_itr(size_t key);

	iterator				begin();
	iterator				end();

	bool					empty();

	size_t					size();

	void					clear();
};


}


#endif
