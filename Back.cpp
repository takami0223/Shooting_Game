#include "Back.h"
#include "define.h"
#include "DxLib.h"

Back::Back()
{
	gh[0] = LoadGraph( "../images/back1-2.png" );
	gh[1] = LoadGraph( "../images/back3.png" );
	gh[2] = LoadGraph( "../images/back4.png" );

	x = y = MARGIN;
	now_stage = 0;
}

void Back::Draw()
{
	DrawGraph( x, y, gh[now_stage], FALSE );
	DrawGraph( x, y - 460, gh[now_stage], FALSE );

	//一番下までスクロールしたら初期値に戻す
	if (y == 460 + MARGIN) y = MARGIN;
}

void Back::Move()
{
	y += SCROLL_SPEED;
}

void Back::SetNowStage( int now_stage )
{
	this->now_stage = now_stage;
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