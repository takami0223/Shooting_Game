#include "Graze.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>

int Graze::gh = 0;

Graze::Graze()
{
	srand( (unsigned)time( NULL ) );

	x, y = 0;

	//‰‰ñ‚¾‚¯“Ç‚Þ
	if (gh == 0)
	{
		gh = LoadGraph( "../images/graze.png" );
	}

	rad = rate = 0;

	alpha = 255;

	flag = false;

	count = 0;

}

void Graze::Move()
{
	//‰‰ñ‚¾‚¯Šp“xÝ’è
	if (count == 0)
	{
		rad = rand() % 628 / 100;
	}

	alpha = 255 - (255 / 20)*count;

	rate = 1.0 - 0.05*count;

	x += cos( rad ) * 6;
	y += sin( rad ) * 6;

	++count;

	if (count == 20)
	{
		count = 0;
		flag = false;
	}
}

void Graze::Draw()
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, alpha );

	DrawRotaGraph( x, y, rate, 1, gh, TRUE );

	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
}

bool Graze::GetFlag()
{
	return flag;
}

void Graze::SetFlag( double x, double y )
{
	this->x = x;
	this->y = y;
	flag = true;
}

void Graze::Update_All()
{
	if (flag)
	{
		Move();
	}
}

void Graze::Draw_All()
{
	if (flag)
	{
		Draw();
	}
}

void Graze::All()
{
	if (flag)
	{
		Move();
		Draw();
	}
}