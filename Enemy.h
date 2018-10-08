//#ifndef _ENEMY_H_
//#define _ENEMY_H_

#pragma once

#include "define.h"

class Enemy
{
private:

	int gh[3];
	int width, height;

	//何ループ目で敵が出てくるか、止まるか、帰還するか、発射タイミング
	int in_time, stop_time, out_time, shot_time;

	int type;	   //敵の種類
	int stype;	   //弾の種類
	int m_pattern; //移動パターン
	int s_pattern; //ショットパターン
	int move_speed;//移動速度
	int hp;		   //HP
	int item;	   //アイテム
	int count;	   //敵が出現してからのカウント
	int num;	   //発射した弾数
	double rad;	   //発射直後のラジアン
	bool s_shot;   //弾が発射されたかのフラグ
	int s_sound;

	int ebarrier_gh; //バリアのグラフィックハンドル
	int ebarrier_hp; //バリアのHP
	bool ebarrier_flag; //バリアを貼るか
	bool deadflag; //敵消滅フラグ
	bool endflag;  //敵クラス消滅フラグ

	E_Shot shot[ENEMY_SNUM]; //弾構造体
	bool sflag; //ショットが撃てるようになったかのフラグ
	int scount; //ショットが打てるようになってからのカウント

	int move_handle;

public:
	double x, y;
	double p_x, p_y;

private:
	void Move( int All_count );
	void Shot( int All_count );
	void Draw();

public:

	Enemy();
	Enemy( int type, int stype, int m_pattern, int s_pattern, int in_time, int stop_time, int shot_time, int out_time, int x, int y, int move_speed, int speed, int hp, int power, int barrier_hp, int item, int sound );
	virtual ~Enemy();
	Enemy( Enemy& a );
	void Update_All( int All_count );
	bool Draw_All();
	bool All( int All_count );

	bool OutCheck();
	bool ShotOutCheck( int i );

	void GetPosition( double *x, double *y );

	bool GetShotPosition( int index, double *x, double *y );
	void SetShotFlag( int index, bool flag );
	int GetShotType();
	int GetShotDamage( int index );

	void SetHp( int hp );
	int GetHp();

	int GetItemType();

	void SetGrazeFlag( int index );
	bool GetGrazeFlag( int index );

	void Add_BarrierHp( int hp );
	int GetBarrierHp();
	bool GetBarrierFlag();

	void SetDeadFlag();
	bool GetDeadFlag();

	bool isPlaySound();
	int GetPlaySound();

};

//#endif // !_ENEMY_H_


