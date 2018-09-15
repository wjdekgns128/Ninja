#include "cDust.h"

cDust::cDust()
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	m_pSingle				= new KGRenderSingle(pGame->m_pAnimate);
	m_single				= true;
	
	int a = rand()%4;
	switch(a) {
		case 0:
			m_position		= D3DXVECTOR3(0.0, 0.0, 0.0);
			m_vector		= D3DXVECTOR3(2 + rand()%51/10.0, 1 + rand()%31/10.0, 0);
			break;
		case 1:
			m_position		= D3DXVECTOR3(1024.0, 0.0, 0.0);
			m_vector		= D3DXVECTOR3(-2 - rand()%51/10.0, 1 + rand()%31/10.0, 0);
			break;
		case 2:
			m_position		= D3DXVECTOR3(0.0, 768.0, 0.0);
			m_vector		= D3DXVECTOR3(2 + rand()%51/10.0, -1 - rand()%31/10.0, 0);
			break;
		case 3:
			m_position		= D3DXVECTOR3(1024.0, 768.0, 0.0);
			m_vector		= D3DXVECTOR3(-2 - rand()%51/10.0, -1 - rand()%31/10.0, 0);
			break;
	}
	m_pSingle->Entry(L"dust", m_position, true, -1);

	cParticle::Register();
}


cDust::~cDust()
{
	
}


void cDust::Update(float fElapsedTime)
{
	if(m_die)
		return;

	m_position.x			+= m_vector.x;
	m_position.y			+= m_vector.y;

	m_pSingle->SetMove(m_position);

	if(m_position.x < 0.0 || m_position.x > 1024.0 || m_position.y < 0.0 || m_position.y > 768.0)
		m_die				= true;
}