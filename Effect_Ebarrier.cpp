#include "Effect_Ebarrier.h"
#include "DxLib.h"

int Effect_Ebarrier::gh = 0;

Effect_Ebarrier::Effect_Ebarrier()
{
	if (gh == 0)
	{
		gh = LoadGraph( "../images/barrier01.png" );
	}

	x = y = 0;
	flag = false;
}

void Effect_Ebarrier::Move()
{

}

void Effect_Ebarrier::Draw()
{
	DrawGraph( x - 50, y - 50, gh, true );
}

void Effect_Ebarrier::All()
{
	Move();
	Draw();
}


void Effect_Ebarrier::SetFlag( double x, double y )
{
	this->x = x;
	this->y = y;

	flag = true;
}

/*
void Effect_Ebarrier::SetFlag()
{
	flag = true;
}
*/
bool Effect_Ebarrier::GetFlag()
{
	return flag;
}