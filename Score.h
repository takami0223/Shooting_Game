#pragma once

#include "define.h"

enum ScoreData
{
	HIGH_SCORE,
	CURRENT_SCORE,
	GRAZE_SCORE,
	STOCK_SCORE,
	LIFE_SCORE,
	POWER_SCORE,
	POWER_LIMIT_SCORE,
	SPEED_SCORE,
	SPEED_LIMIT_SCORE
};

class Score
{
private:

	//グラフィックハンドル
	int g_board[6];		//文用
	int g_number[10];	//数字用(デフォルト)
	int g_hi_grazenumber[10]; //グレイズの最高到達用
	int g_hi_hpnumber[10];    //HPの最高到達用
	int g_hi_speednumber[10]; //スピードの最高到達用
	int g_hi_powernumber[10]; //パワーの最高到達用
	int g_stock[12];	//残機用
	int high_score, score, graze, stock, life, power, speed;
	int power_limit, speed_limit;

	int grazeGauge = 0;
	double g_h;
	unsigned int g_r;
	unsigned int g_g;
	unsigned int g_b;

	int lifeGauge = 0;
	double l_h;
	unsigned int l_r;
	unsigned int l_g;
	unsigned int l_b;

	int speedGauge = 0;
	double s_h;
	unsigned int s_r;
	unsigned int s_g;
	unsigned int s_b;

	int powerGauge = 0;
	double p_h;
	unsigned int p_r;
	unsigned int p_g;
	unsigned int p_b;

	int gauge_width = 0;

	static int gauge_cover, gauge_base;  //グラフィックハンドル格納用配列

private:
	void Draw();

public:
	Score();
	void SetScore( ScoreData data, int val );
	int GetScore( ScoreData data );
	void All();

};