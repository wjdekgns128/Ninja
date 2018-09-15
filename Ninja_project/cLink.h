#ifndef _CLINK_H
#define _CLINK_H

#include "cInclude.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace KG;

class cLink
{
public:
	vector<void*>			m_List;
	vector<int>				m_removeList;

private: 
	cLink();
public:
	~cLink();
public:
	static cLink* GetInstance()  
	{  
		static cLink* Instance = NULL;  
		if( Instance == NULL )  
			Instance = new cLink();
		return Instance;
	}  
	void Update(float fElapsedTime);
	virtual void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void end();
	void CreateDust(float fElapsedTime);
};

#endif