#pragma once

#include "define.h"

class Item
{
private:
	//グラフィックハンドル
	static int gh[ITEM_TYPE_NUM], ghs[ITEM_TYPE_NUM];

	//どっちのアイテムかを示す変数
	//int item_type;
	//int effect_type;
	int type;

	//座標
	double x, y;
	double prev_y;

	//回転角度
	double rad;

	//カウント
	int count;

	//アイテムが落下し始めるフラグ
	bool fall_flag;

	//出現中かどうかのフラグ
	bool flag;

private:
	void Move();
	void Draw();

public:
	Item();
	void SetFlag( double x, double y, int type );
	bool GetFlag();
	void Delete();
	void GetPosition( double *x, double *y );
	int  GetType();
	void Update_All();
	void Draw_All();
	void All();
};