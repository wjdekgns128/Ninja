#include "cLink.h"
#include "cParticle.h"
#include "cDust.h"
#include "cGame.h"
#include "CMAIN.h"


cLink::cLink()
{
	
}


cLink::~cLink()
{
	if(m_List.empty() == false)
	for(int i = 0; i < m_List.size(); i++)
		delete ((cParticle*)m_List[i]);
	m_List.clear();
	m_removeList.clear();
}


void cLink::Update(float fElapsedTime)
{
	if(m_List.empty() == false) {
		for(int i = 0; i < m_List.size(); i++) {
			((cParticle*)m_List[i])->Update(fElapsedTime);
			if(((cParticle*)m_List[i])->m_die == true) {
				m_removeList.push_back(i);
			}
		}
		if(m_removeList.empty() == false) {
			for(int i = m_removeList.size()-1; i >= 0; i--) {
				delete ((cParticle*)m_List[m_removeList[i]]);
				m_List.erase(m_List.begin() + m_removeList[i]);
			}
			m_removeList.clear();
		}
	}
	//CreateDust(fElapsedTime);
}


void cLink::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	if(m_List.empty() == false) {
		for(int i = 0; i < m_List.size(); i++) {
			if(((cParticle*)m_List[i])->m_single == true) {
				SAFE_ONFRAMERENDER(((cParticle*)m_List[i])->m_pSingle);
			}
			else {
				((cParticle*)m_List[i])->Render(pGame->m_pSprite);
			}
		}
	}
}


void cLink::end()
{
	if(m_List.empty() == false)
	for(int i = 0; i < m_List.size(); i++)
		delete ((cParticle*)m_List[i]);
	m_List.clear();
	m_removeList.clear();
}


void cLink::CreateDust(float fElapsedTime)
{
	static double timer = rand()%20;

	timer += fElapsedTime;
	if(timer > 10.0) {
		cDust* dust = new cDust();
		timer = 0.0;
	}
}