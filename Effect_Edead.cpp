#include "Effect_Edead.h"
#include "DxLib.h"
#include <time.h>

int Effect_Edead::gh[3] = { 0,0,0 };

Effect_Edead::Effect_Edead()
{
	//乱数を初期化
	srand( (unsigned int)time( NULL ) );

	x = y = 0;

	//画像読み込み。初回だけ
	if (gh[0] == 0)
	{
		gh[0] = LoadGraph( "../images/effect1.png" );
		gh[1] = LoadGraph( "../images/effect2.png" );
		gh[2] = LoadGraph( "../images/effect3.png" );
	}
	rad = 0;

	rate = 1;

	alpha = 255;

	count = 0;

	flag = false;

	index = 0;

}

void Effect_Edead::Move()
{
	if (flag)
	{

		//初回だけ角度と添字セット
		if (count == 0)
		{
			rad = rand() % 624 / 100;
			index = rand() % 3;
		}


		rate = 0.5 + count * 0.05;

		alpha = 255 - 255 / 30 * count;


		++count;

		if (count == 30)
		{
			count = 0;
			flag = false;
		}
	}
}

void Effect_Edead::Draw()
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, alpha );
	DrawRotaGraph( x, y, rate, rad, gh[index], TRUE );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
}

void Effect_Edead::SetFlag( double x, double y )
{
	this->x = x;
	this->y = y;

	flag = true;
}

bool Effect_Edead::GetFlag()
{
	return flag;

}

void Effect_Edead::Update_All()
{
	if (flag)
	{
		Move();
	}
}

void Effect_Edead::Draw_All()
{
	if (flag)
	{
		Draw();
	}
}

void Effect_Edead::All()
{
	Move();
	Draw();
}