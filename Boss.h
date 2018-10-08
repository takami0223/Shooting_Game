#pragma once

#include "define.h"

enum BOSS_MOVE_TYPE
{
	BOSS_MOVE_START,
	BOSS_MOVE_PATTERN1,
	BOSS_MOVE_PATTERN2,
	BOSS_MOVE_PATTERN3,
	BOSS_MOVE_DEFAULT,

	BOSS_MOVE_TYPE_NUM
};

enum BOSS_SHOT_TYPE
{
	BOSS_SHOT_LINE,
	BOSS_SHOT_SHOTTING,
	BOSS_SHOT_CIRCLE,
	BOSS_SHOT_CIRCLE_LINE,

	BOSS_SHOT_TYPE_NUM
};

class Boss
{
private:
	//座標
	double prev_x, prev_y;

	//グラフィックハンドル
	int gh_face[2];
	int gh_shot[3];

	//現在の移動パターン
	int move_pattern;
	//現在のショットパターン
	int shot_pattern;

	int prev_move_pattern;
	int prev_shot_pattern;

	//弾構造体
	E_Shot shot[BOSS_SHOTNUM];

	//合計角度と増加量
	int angle, raise;

	//横移動時の増加量
	int raise2;
	int waitcount;
	bool wait;

	//次の移動場所までの距離
	double movex, movey;
	int p3_state;

	bool shotflag;
	int count;
	int scount;
	int temp_scount;
	bool s_shot;



	//ダメージを負ったかどうかのフラグ
	bool damageflag;

	//ダメージを負わないフラグ
	bool no_damageflag;

	//生きてるかどうかのフラグ
	bool flag;
	int hp;
	int prev_hp;

	int stage_num;

	//bool scflag;

public:
	double x, y;
	double p_x, p_y;

private:
	void MoveInit( double bx, double by, int state );
	void Move();
	void Shot();
	void Appear();
	void MovePattern1();
	void MovePattern2();
	void MovePattern3();
	void Draw();
	int ShotSearch();
	bool ShotOutCheck( int i );
	void MoveToDefault();
	void SetMovePattern( int pattern );
	void SetShotPattern( int pattern );

public:
	Boss( int stage_num );
	//void SetDamageFlag();
	//void SetFlag( bool f );
	//bool GetFlag();

	void GetPosition( double *x, double *y );
	bool GetShotPosition( int index, double *x, double *y, int * type );
	void SetShotFlag( int index, bool flag );
	int GetShotDamage( int index );
	bool GetGrazeFlag( int index );
	void SetGrazeFlag( int index );
	void SetDamageSetting();
	bool GetDamageFlag();
	bool GetNodamageFlag();
	void SetFlag( bool flag );
	bool GetFlag();

	void SetHp( int damage );
	int GetHp();
	int GetPrevHp();

	void Update_All();
	void Draw_All();
	void All();
};