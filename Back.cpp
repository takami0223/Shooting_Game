#include "Back.h"
#include "define.h"
#include "DxLib.h"

Back::Back()
{
	gh = LoadGraph( "../images/back1.png" );

	x = y = MARGIN;
}

void Back::Draw()
{
	DrawGraph( x, y, gh, FALSE );
	DrawGraph( x, y - 460, gh, FALSE );

	//一番下までスクロールしたら初期値に戻す
	if (y == 460 + MARGIN) y = MARGIN;
}

void Back::Move()
{
	y += SCROLL_SPEED;
}

void Back::Update_All()
{
	Move();
}

void Back::Draw_All()
{
	Draw();
}

void Back::All()
{
	Move();
	Draw();
}