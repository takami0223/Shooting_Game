#pragma once

#include "define.h"

class Effect_Pcharge
{
private:

	int gauge = 0;
	int gauge_width = 0;
	int now_charge = 0;

	double h;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	static int gauge_cover, gauge_base;  //グラフィックハンドル格納用配列

public:
	double x, y;
	int max_charge = 0;

private:
	void Move();
	void Draw();

public:

	Effect_Pcharge();

	void Update_All();
	void Draw_All();
	void All();

};