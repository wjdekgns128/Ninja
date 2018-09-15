#ifndef _CGAME_H
#define _CGAME_H


#include "cEnum.h"
#include "cDefine.h"
#include "cHero.h"
#include "cEnemy.h"
#include "cStateWindow.h"
#include "cHelp.h"
#include "string.h"
class cHero;
class cEnemy;
class cStateWindow;
class cHelp;

using namespace KG;
using namespace std;
class cGame : public KGScene, public KGResponseDialog
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
	wstring					m_string;
	KGDialog*				m_pStopmenu;

	cHero*					m_pHero;
	cEnemy*					m_pEnemy[ENEMY_AMOUNT];
	cStateWindow*			m_pStateWindow;
	cHelp*					m_pHelp;

	bool					m_stop;
	bool					m_nameWrite;

	float					m_timer;
	float					m_max;
	float					m_accelerate;
	float					m_accelTimer;
	float					m_fapl;
	float					m_gameapl;

	int						m_gamecheck;
	int						m_maxEnemy;
	int						m_score;
	int						m_bestScore;
	int						m_bestLevel;
	int						m_level;
	int						m_curExp;
	int						m_expMax;
	int						m_hexp;

	WCHAR					m_name[10];
	WCHAR					m_bestName[10];

	bool					m_showLvUp;
	bool					m_showHelp;
	bool					m_showStateWindow;
	bool					m_guideTouch;
	bool					m_enterCheck;
	bool					m_gamestop;
	
	float					m_enterTimer;
	float					m_enterAlpha;
	float					m_stateTimer;
	float					m_stateAlpha;
	float					m_UIAlpha[2];
	float					m_UITimer;
	float					m_etime;
	

	_ScorePlus				m_scorePlus[8];

public:
	cGame();
	~cGame();

	void EnemyUpdate(float fElapsedTime);
	void Collsion();
	float Distance(D3DXVECTOR3 point1, D3DXVECTOR3 point2);
	void ExpManage(int exp);
	void SaveScore(int score);
	void ScoreAccumulate(int score);
	void ShowEnter(float fElapsedTime);
	void StateWindow(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void UIDraw();
	void TextDraw();
	void UIVisible();
	void GameNM(float time);
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