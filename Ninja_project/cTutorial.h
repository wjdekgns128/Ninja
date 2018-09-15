#ifndef _CTUTORIAL_H
#define _CTUTORIAL_H


#include "cEnum.h"
#include "cDefine.h"
#include "cHero.h"
#include "cEnemy.h"
class cHero;
class cEnemy;

using namespace KG;

class cTutorial : public KGScene, public KGResponseDialog
{
public:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGRenderSingle*			m_pSingle;
	KGFont*					m_pFont;
	KGDialog*				m_pDialog;
	KGDialog*				m_pDialog2;
	KGDialog*				m_pName;
	KGCursor*				m_pCursor;
	KGSound*				m_pSound;

	cHero*					m_pHero;
	cEnemy*					m_pEnemy[ENEMY_AMOUNT];

	bool					m_stop;
	bool					m_nameWrite;

	float					m_timer;
	float					m_max;
	float					m_accelerate;
	float					m_accelTimer;
	int						m_maxEnemy;
	int						m_score;
	int						m_bestScore;
	int						m_level;
	
	WCHAR					m_name[10];
	WCHAR					m_bestName[10];
	int						m_curExp;
	int						m_expMax;
	
	bool					m_showLvUp;
	bool					m_showHelp;
	bool					m_showStateWindow;
	bool					m_guideTouch;

	float					m_enterTimer;
	float					m_enterAlpha;
	bool					m_enterCheck;

	_ScorePlus				m_scorePlus[3][4];
	
public:
	cTutorial();
	~cTutorial();

	void EnemyUpdate(float fElapsedTime);
	void Collsion();
	float Distance(D3DXVECTOR3 point1, D3DXVECTOR3 point2);
	void ExpManage(int exp);
	void ScoreAccumulate(int score);
	void TextDraw();

public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
	void CALLBACK			OnEvent(UINT id, int xPos, int yPos);

	LRESULT CALLBACK		OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
	
};

#endif