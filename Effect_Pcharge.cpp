#include "Effect_Pcharge.h"
#include "Keyboard.h"
#include "DxLib.h"

int Effect_Pcharge::gauge_cover = 0;
int Effect_Pcharge::gauge_base = 0;

Effect_Pcharge::Effect_Pcharge()
{

	if (gauge_cover == 0 || gauge_base == 0)
	{
		gauge_cover = LoadGraph( "../images/gauge_cover02.png" );
		gauge_base = LoadGraph( "../images/gauge_base01.png" );
	}

	x = 0;
	y = 0;

	gauge = 0;
	gauge_width = 88;
	now_charge = 0;
	max_charge = 0;

	h = 0;
	r = g = b = 0;

}

void Effect_Pcharge::Move()
{
	now_charge = Keyboard_Get( KEY_INPUT_Z );
	if (max_charge < now_charge) now_charge = max_charge;

	gauge = gauge_width * now_charge / max_charge;

}

void Effect_Pcharge::Draw()
{
	h = now_charge * (512.0f / max_charge) - 100;
	r = min( max( (384 - h), 0 ), 0xff );
	g = min( max( (h + 64), 0 ), 0xff );
	b = max( (h - 384), 0 );

	DrawGraph( x - 50, y + 30, gauge_base, true );
	DrawBox( x - 46, y + 35, x - 46 + gauge, y + 40, GetColor( r, g, b ), true );
	DrawGraph( x - 50, y + 30, gauge_cover, true );


}

void Effect_Pcharge::Update_All()
{
	Move();
}

void Effect_Pcharge::Draw_All()
{
	Draw();
}

void Effect_Pcharge::All()
{
	Move();
	Draw();
}