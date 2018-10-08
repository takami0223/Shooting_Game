#pragma once

#include "define.h"

struct Peffect_Expand
{
	double x, y;
	double rad;
	int speed;

};

class Effect_Pdead
{
private:
	//座標
	double x, y;

	//画像のサイズ
	int width[3];
	int height[3];

	//グラフィックハンドル
	static int gh[3];

	//拡大率
	double rate;

	//透明度
	int alpha;

	//パーティクルエフェクト構造体
	Peffect_Expand expand[EFFECT_PDEADNUM];

	//回転させる画像用の角度
	double rota;

	//カウント
	int count;

	//実行中かどうかのフラグ
	bool flag;

private:
	void Move();
	void Draw();
public:
	Effect_Pdead();
	void SetFlag( double x, double y );
	bool GetFlag();
	void Update_All();
	void Draw_All();
	void All();
};