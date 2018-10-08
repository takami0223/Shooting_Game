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

private:
	void Draw();

public:
	Score();
	void SetScore( ScoreData data, int val );
	int GetScore( ScoreData data );
	void All();

};