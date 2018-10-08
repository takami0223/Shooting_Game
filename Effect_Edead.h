#pragma once

#include "define.h"

class Effect_Edead
{
private:
	//座標
	double x, y;

	//グラフィックハンドル
	static int gh[3];

	//エフェクト画像の角度
	double rad;

	//拡大率
	double rate;

	//透明度
	int alpha;

	//どの画像を使うかの添字
	int index;

	//カウント
	int count;
	//実行中かどうかのフラグ
	bool flag;

private:
	void Move();
	void Draw();

public:
	Effect_Edead();
	bool GetFlag();
	void SetFlag( double x, double y );
	void Update_All();
	void Draw_All();
	void All();
};

//int Effect_Edead::gh[3] = { 0,0,0 };
