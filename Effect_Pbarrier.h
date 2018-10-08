#pragma once

#include "define.h"

class Effect_Pbarrier
{
private:
	static int gh_1; //バリアのグラフィックハンドル
	static int gh_2;
	static int gauge_cover, gauge_base; //バリアゲージのグラフィックハンドル
	static int move_handle;
	static int break_handle;

	int gauge;
	int gauge_width;

	double h;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	int barrier_hp;    //バリアの耐久値
	bool barrier_flag; //バリアが貼ってあるか
	bool barrier_break_flag; //バリアが割れたか
	bool full_barrier_flag; //最高のバリアが貼ってあるか

	bool barrier_break_time;


private:
	void Move();
	void Draw();

public:
	double x, y;

	Effect_Pbarrier();

	void SetBarrierFlag( int barrierhp );
	bool GetBarrierFlag();

	void Add_BarrierHp( int hp );
	int GetBarrierHp();

	void Update_All();
	void Draw_All();
	void All();
};