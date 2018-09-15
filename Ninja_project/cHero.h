#ifndef _CHERO_H
#define _CHERO_H


#include "cInclude.h"
#include "cNinja.h"


class cNinja;
using namespace KG;

class cHero : public cNinja
{
public:
	bool					m_hide;
	bool					m_blink;
	bool					m_sum;
	bool					m_sumTouch;
	bool					m_sumDirection;
	float					m_sumSpeed;
	float					m_sumInclination;
	float					m_sumSections;
	float					m_sumTimer;
	float					m_hideTimer;
	float					m_levelUpTimer;
	float					m_levelUpValue;
	float					m_blinkTimer;
	float					m_maxBlinkTimer;
	D3DXVECTOR2				m_linePoint[2];
	D3DXVECTOR3				m_sumSavePoint;

	bool					m_keyState;		//false ÀÏ¶§ Ä®
	int						m_life;
	int						m_skillInven;
	int						m_inven[2];
	
public:
	cHero(KGAnimate* animate, KGSprite* sprite);
	~cHero();

	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);

	void ReSet();
	void Update(float fElapsedTime);
	void Key(char key);
	void Mouse(bool direction, D3DXVECTOR3 point);
	void Cut(D3DXVECTOR3 point);
	void Wield(D3DXVECTOR3 point);
	void Defence();
	void Suffer();
	void Hide();
	void EndHide();
	void Eat(int item);
	void LevelUp();
	bool Skill(int item);
	void SThreeDart();
	void SetSum(D3DXVECTOR3 point);
	void Sum(float time);
	void HideBlink(float fElapsedTime);
};

#endif