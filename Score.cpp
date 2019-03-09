#include "Score.h"
#include "Keyboard.h"
#include "DxLib.h"
#include <cstdio>
//#include <stdio.h>
//#include "define.h"

int Score::gauge_base = 0;
int Score::gauge_cover = 0;


Score::Score()
{

	//LoadDivGraph( "../images/board2.png", 4, 1, 4, 160, 32, g_board );
	LoadDivGraph( "../images/board3.png", 6, 1, 6, 160, 35, g_board );
	LoadDivGraph( "../images/number.png", 10, 10, 1, 19, 27, g_number );
	LoadDivGraph( "../images/number04.png", 10, 10, 1, 19, 27, g_hi_grazenumber );
	LoadDivGraph( "../images/number03.png", 10, 10, 1, 19, 27, g_hi_hpnumber );
	LoadDivGraph( "../images/number02.png", 10, 10, 1, 19, 27, g_hi_speednumber );
	LoadDivGraph( "../images/number01.png", 10, 10, 1, 19, 27, g_hi_powernumber );
	LoadDivGraph( "../images/shot_chara1.png", 12, 3, 4, 29, 40, g_stock );

	if (gauge_cover == 0 || gauge_base == 0)
	{
		gauge_cover = LoadGraph( "../images/gauge_cover02.png" );
		gauge_base = LoadGraph( "../images/gauge_base01.png" );
	}

	high_score = 0;
	score = 0;
	graze = 0;
	stock = 0;
	life = 0;
	power = 0;
	power_limit = POWER_DEFAULT_LIMIT;
	speed = 0;
	speed_limit = SPEED_DEFAULT_LIMIT;

	grazeGauge = lifeGauge = speedGauge = powerGauge = 0;
	gauge_width = 88;

	g_h = l_h = s_h = p_h = 0;

	g_r = g_g = g_b = 0;
	l_r = l_g = l_b = 0;
	s_r = s_g = s_b = 0;
	p_r = p_g = p_b = 0;

}

void Score::SetScore( ScoreData data, int val )
{
	switch (data)
	{
		case HIGH_SCORE:
			high_score += val;
			break;

		case CURRENT_SCORE:
			score += val;
			break;

		case GRAZE_SCORE:
			graze = val;
			break;

		case STOCK_SCORE:
			stock = val;
			break;

		case LIFE_SCORE:
			life = val;
			if (life < 0) life = 0;
			break;

		case POWER_SCORE:
			power = val;
			break;

		case POWER_LIMIT_SCORE:
			power_limit = val;
			break;

		case SPEED_SCORE:
			speed = val;
			break;

		case SPEED_LIMIT_SCORE:
			speed_limit = val;
			break;

		default:
			break;
	}
}

int Score::GetScore( ScoreData data )
{
	switch (data)
	{
		case HIGH_SCORE:
			return high_score;
			break;

		case CURRENT_SCORE:
			return score;
			break;

		case GRAZE_SCORE:
			return graze;
			break;

		case STOCK_SCORE:
			return stock;
			break;

		case LIFE_SCORE:
			return life;
			break;

		case POWER_SCORE:
			return power;
			break;

		case POWER_LIMIT_SCORE:
			return power_limit;
			break;

		case SPEED_SCORE:
			return speed;
			break;

		case SPEED_LIMIT_SCORE:
			return speed_limit;
			break;

		default:
			break;
	}

	//該当しないときは-1を返す
	return -1;
}

void Score::Draw()
{
	char buf[100] = {};
	int num = 0;

	//スコアボードの文字描写
	DrawGraph( SCORE_X, 10, g_board[0], TRUE );
	DrawGraph( SCORE_X, 70, g_board[1], TRUE );
	DrawGraph( SCORE_X, 130, g_board[2], TRUE );
	DrawGraph( SCORE_X, 160, g_board[3], TRUE );
	DrawGraph( SCORE_X, 190, g_board[4], TRUE );
	DrawGraph( SCORE_X, 220, g_board[5], TRUE );


	//ハイスコア描画
	num = snprintf( buf, sizeof( buf ), "%d", high_score );
	for (int i = 0; i < num; ++i)
	{
		DrawGraph( SCORE_X + 20 + i * 19, 35, g_number[(buf[i] - '0')], TRUE );
	}

	//スコア描画
	num = snprintf( buf, sizeof( buf ), "%d", score );
	for (int i = 0; i < num; ++i)
	{
		DrawGraph( SCORE_X + 20 + i * 19, 95, g_number[(buf[i] - '0')], TRUE );
	}

	//グレイズ数描画
	grazeGauge = gauge_width * (graze % BARRIER_OPEN_NUM) / BARRIER_OPEN_NUM;
	g_h = (graze % BARRIER_OPEN_NUM) * (512.0f / BARRIER_OPEN_NUM) - 100;
	g_r = min( max( (384 - g_h), 0 ), 0xff );
	g_g = min( max( (g_h + 64), 0 ), 0xff );
	g_b = max( (g_h - 384), 0 );
	DrawBox( SCORE_X + 110, 137, SCORE_X + 110 + grazeGauge, 156, GetColor( g_r, g_g, g_b ), true );

	num = snprintf( buf, sizeof( buf ), "%d", graze );
	if (graze >= GRAZE_LINIT)
	{
		for (int i = 0; i < num; ++i)
		{
			DrawGraph( SCORE_X + 110 + i * 19, 133, g_hi_grazenumber[(buf[i] - '0')], TRUE );
		}
	}
	else
	{
		for (int i = 0; i < num; ++i)
		{
			DrawGraph( SCORE_X + 110 + i * 19, 133, g_number[(buf[i] - '0')], TRUE );
		}
	}

	//ライフ数描画
	lifeGauge = gauge_width * life / LIFE_LIMIT;
	l_h = life * (512.0f / LIFE_LIMIT) - 100;
	l_r = min( max( (384 - l_h), 0 ), 0xff );
	l_g = min( max( (l_h + 64), 0 ), 0xff );
	l_b = max( (l_h - 384), 0 );
	DrawBox( SCORE_X + 110, 167, SCORE_X + 110 + lifeGauge, 186, GetColor( l_r, l_g, l_b ), true );

	num = snprintf( buf, sizeof( buf ), "%d", life );
	if (life >= LIFE_LIMIT)
	{
		for (int i = 0; i < num; ++i)
		{
			DrawGraph( SCORE_X + 110 + i * 19, 163, g_hi_hpnumber[(buf[i] - '0')], TRUE );
		}
	}
	else
	{
		for (int i = 0; i < num; ++i)
		{
			DrawGraph( SCORE_X + 110 + i * 19, 163, g_number[(buf[i] - '0')], TRUE );
		}
	}

	//スピード数描画
	speedGauge = gauge_width * speed / speed_limit;
	s_h = speed * (512.0f / speed_limit) - 100;
	s_r = min( max( (384 - s_h), 0 ), 0xff );
	s_g = min( max( (s_h + 64), 0 ), 0xff );
	s_b = max( (s_h - 384), 0 );
	DrawBox( SCORE_X + 110, 197, SCORE_X + 110 + speedGauge, 216, GetColor( s_r, s_g, s_b ), true );

	num = snprintf( buf, sizeof( buf ), "%d", speed );
	if (speed >= speed_limit)
	{
		for (int i = 0; i < num; ++i)
		{
			DrawGraph( SCORE_X + 110 + i * 19, 193, g_hi_speednumber[(buf[i] - '0')], TRUE );

		}
	}
	else
	{
		for (int i = 0; i < num; ++i)
		{
			DrawGraph( SCORE_X + 110 + i * 19, 193, g_number[(buf[i] - '0')], TRUE );
		}
	}

	//パワー数描画
	powerGauge = gauge_width * power / power_limit;
	p_h = power * (512.0f / power_limit) - 100;
	p_r = min( max( (384 - p_h), 0 ), 0xff );
	p_g = min( max( (p_h + 64), 0 ), 0xff );
	p_b = max( (p_h - 384), 0 );

	//DrawGraph( SCORE_X + 110, 240, gauge_base, true );
	DrawBox( SCORE_X + 110, 227, SCORE_X + 110 + powerGauge, 246, GetColor( p_r, p_g, p_b ), true );
	//DrawGraph( SCORE_X + 110, 240, gauge_cover, true );

	num = snprintf( buf, sizeof( buf ), "%d", power );
	if (power >= power_limit)
	{
		for (int i = 0; i < num; ++i)
		{
			DrawGraph( SCORE_X + 110 + i * 19, 223, g_hi_powernumber[(buf[i] - '0')], TRUE );

		}
	}
	else
	{
		for (int i = 0; i < num; ++i)
		{
			DrawGraph( SCORE_X + 110 + i * 19, 223, g_number[(buf[i] - '0')], TRUE );

		}
	}

	//ストック数描画
	for (int i = 0; i < stock; ++i)
	{
		DrawGraph( SCORE_X + 20 + i * 29, 300, g_stock[7], TRUE );
	}

	//ｘが押されているフレーム数
	num = snprintf( buf, sizeof( buf ), "%d", Keyboard_Get( KEY_INPUT_Z ) );
	for (int i = 0; i < num; ++i)
	{
		DrawGraph( SCORE_X + 20 + i * 19, 400, g_number[(buf[i] - '0')], TRUE );

	}
}

void Score::All()
{
	Draw();
}