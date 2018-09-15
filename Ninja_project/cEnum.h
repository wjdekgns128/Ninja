#ifndef __CENUM_H__
#define __CENUM_H__

enum STATE {
	S_MOVE = 0,
	S_ATTACK,
	S_CUT,
	S_WAIT,
	S_SUFFER,
	S_STOP,
	S_DIE,
	S_DEFENCE,
	S_PUNG,
	S_AMAZE,
	S_AMOUNT,
};

enum KEY {
	K_CUT = 0,
	K_DEFENCE,
	K_ATTACK,
};

enum MENU_DIALOG
{
	GAME_START = 0,
	GAME_LOAD,
	GAME_HELP,
	EXIT,
};

enum BUTTON
{
	B_SKILL1 = 0,
	B_SKILL2,
	B_SKILL3,
	B_DART1,
	B_DART2,
	B_DART3,
	B_DART4,
};

enum DART_KIND
{
	D_NORMAL = 0,
	D_ENOMAL,
	D_PENETRATE,
	D_BOUNCE,
	D_BOOM,
	D_HALF,
};

enum ITEM
{
	I_NOITEM = 0,
	I_HIDE,
	I_THREEDART,
	I_SUM,
};

enum STOP_MENU
{
	B_RETUNR = 10,
	B_HELP,
	B_MENU,
};


typedef struct ScorePlus {
	bool			show;
	int				score;
	float			timer;
	float			alpha;
} _ScorePlus;

#endif