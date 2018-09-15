#include "cDart.h"
#include "cEnum.h"
#include "cGame.h"

static WCHAR pungImgName[4][10] = {0,};

cDart::cDart()
{
	m_pSingle				= NULL;
	if(pungImgName[0][0] == 0) {
		memcpy(pungImgName, L"气1", sizeof(L"气1"));
		memcpy(pungImgName, L"气2", sizeof(L"气2"));
		memcpy(pungImgName, L"气3", sizeof(L"气3"));
		memcpy(pungImgName, L"气4", sizeof(L"气4"));
	}

	m_state					= S_WAIT;
	m_kind					= 0;
	
	m_radius				= 12;
	
	m_inclination			= 0.0;
	m_sections				= 0.0;
	m_rotation				= 0.0;
	m_speed					= 0.0;
	m_saveObject			= NULL;
}


cDart::~cDart()
{
	SAFE_DELETE(m_pSingle);
}


void cDart::Update(float time)
{
	if(m_state == S_WAIT)
		return;

	if(m_state == S_MOVE) {
		Move();
		if(m_kind == D_ENOMAL || m_kind == D_BOUNCE)
			m_rotation			+= 50.0;

		if(m_position.x < 0.0 || m_position.x > 1024.0 || m_position.y < 0.0 || m_position.y > 768.0)
			m_state				= S_WAIT;
		if(m_kind == D_ENOMAL && m_reach == false) {
			if(pow(m_startPoint.x - m_position.x, 2) + pow(m_startPoint.y - m_position.y, 2) > 140000) {
				m_reach			= true;
			}
		}
		else if(m_reach == true) {
			m_alpha -= 0.05;
			if(m_alpha <= 0.0)
				m_state = S_WAIT;
		}
	}
	else if(m_state == S_PUNG) {
		m_timer					+= time;
		if(m_timer > 3.0)
			m_state			= S_WAIT;
	}
}


void cDart::Render(KGSprite* sprite)
{
	if(m_state == S_MOVE)
		sprite->Render(m_imgName, m_position, D3DXToRadian(m_rotation), D3DXCOLOR(1,1,1,m_alpha));
}


void cDart::Create(D3DXVECTOR3 position, D3DXVECTOR3 point, int kind)
{
	m_startPoint			= position;
	m_position				= position;
	m_bounce				= 0;
	m_saveObject			= NULL;
	m_alpha					= 1.0;
	m_frame					= 0;
	m_timer					= 0.0;
	m_reach					= false;
	m_kind					= kind;

	switch(kind) {
		case D_NORMAL:
			m_displacement	= 7.0;
			memcpy(m_imgName, L"normalDart", sizeof(L"normalDart"));
			break;
		case D_ENOMAL:
			m_displacement	= 4.0;
			memcpy(m_imgName, L"EDart", sizeof(L"EDart"));
			break;
		case D_PENETRATE:
			memcpy(m_imgName, L"penetrateDart", sizeof(L"penetrateDart"));
			break;
		case D_BOUNCE:
			m_displacement	= 7.0;
			memcpy(m_imgName, L"bounceDart", sizeof(L"bounceDart"));
			break;
		case D_BOOM:
			m_displacement	= 6.0;
			memcpy(m_imgName, L"boomDart", sizeof(L"boomDart"));
			break;
		case D_HALF:
			m_displacement	= 8.0;
			memcpy(m_imgName, L"halfDart", sizeof(L"halfDart"));
			break;
	}
	SetMoveData(point);
	for(int i = 0; i < 4; i++)	Move();
}


void cDart::Bounce(int num)
{
	switch(m_kind)
	{
	case D_NORMAL:
	case D_ENOMAL:
	case D_HALF:
		m_state				= S_WAIT;
		break;
	case D_PENETRATE:
		if(m_bounce == 2)
			m_state			= S_WAIT;
		break;
	case D_BOUNCE:
		if(m_bounce == 1) {
			m_state			= S_WAIT;
			break;
		}
		SetMoveData(Sensing(num));
		break;
	case D_BOOM:
		{
			cGame* pGame	= (cGame*)cMain()->GetCurrent();

			for(int i = 0; i < ENEMY_AMOUNT; i++) {
				if(pGame->m_pEnemy[i]->m_state == S_DIE || pGame->m_pEnemy[i]->m_state == S_SUFFER)
					continue;
				if(i == num)
					if(pGame->m_pEnemy[i]->m_state == S_SUFFER)
					continue;
				if(pGame->m_pEnemy[i]->Collision(m_position, 50))
					pGame->m_pEnemy[i]->Die();
			}
			m_state			= S_PUNG;
			if(m_pSingle == NULL) m_pSingle = new KGRenderSingle(pGame->m_pAnimate);
			m_pSingle->Entry(L"boom", m_position, true, 1);
			m_pSingle->SetMove(m_position);
		}
		break;
	}
	m_bounce++;
}


D3DXVECTOR3 cDart::Sensing(int _num)
{
	cGame* pGame		= (cGame*)cMain()->GetCurrent();
	int num = 0;
	float dis = 1000000;
	float temp = 0;
	D3DXVECTOR3 point;
	for(int i = 0; i < pGame->m_maxEnemy; i++) {
		if(pGame->m_pEnemy[i]->m_state == S_DIE || i == _num)
			continue;
		point = pGame->m_pEnemy[i]->m_position;
		temp = pow(point.x - m_position.x,2) + pow(point.y - m_position.y,2);
		if(temp < 625.0)
			continue;
		if(dis > temp) {
			dis = temp;
			num = i;
		}
	}
	if(dis == 1000000)
		return D3DXVECTOR3(rand()%1024, rand()%768, 0);
	return pGame->m_pEnemy[num]->m_position;
}