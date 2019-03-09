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

	//�O���t�B�b�N�n���h��
	int g_board[6];		//���p
	int g_number[10];	//�����p(�f�t�H���g)
	int g_hi_grazenumber[10]; //�O���C�Y�̍ō����B�p
	int g_hi_hpnumber[10];    //HP�̍ō����B�p
	int g_hi_speednumber[10]; //�X�s�[�h�̍ō����B�p
	int g_hi_powernumber[10]; //�p���[�̍ō����B�p
	int g_stock[12];	//�c�@�p
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

	static int gauge_cover, gauge_base;  //�O���t�B�b�N�n���h���i�[�p�z��

private:
	void Draw();

public:
	Score();
	void SetScore( ScoreData data, int val );
	int GetScore( ScoreData data );
	void All();

};