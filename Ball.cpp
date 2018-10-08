#include "Ball.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>

Ball::Ball()
{
	x = y = 0;

	gh = LoadGraph( "../images/awa.png" );

	angle = 0;
	toggle = false;
	raise = 2;
}

void Ball::Move( double px, double py )
{
	angle += raise;

	x = px;
	y = py + sin( angle*M_PI / 180 )*BALL_SHAKE;

	if (angle == 90)
	{
		toggle = true;
	}
	else if (angle == -90)
	{
		toggle = false;
	}

	if (toggle)
	{
		raise = -2;
	}
	else
	{
		raise = 2;
	}
}

void Ball::Draw()
{
	DrawRotaGraph( x + BALL_INITX, y + BALL_INITY, 1.0, 0, gh, TRUE );
	DrawRotaGraph( x - BALL_INITX, y + BALL_INITY, 1.0, 0, gh, TRUE );
}

double Ball::GetPosition()
{
	return y;
}

void Ball::Update_All( double px, double py )
{
	Move( px, py );
}

void Ball::Draw_All()
{
	Draw();
}

void Ball::All( double px, double py )
{
	Move( px, py );
	Draw();
}