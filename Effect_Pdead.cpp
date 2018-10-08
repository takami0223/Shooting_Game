
#include "Effect_Pdead.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>

int Effect_Pdead::gh[3] = { 0,0,0 };

Effect_Pdead::Effect_Pdead()
{
	//������������
	srand( (unsigned int)time( NULL ) );

	if (gh[0] == 0)
	{
		gh[0] = LoadGraph( "../images/playereffect1.png" );
		gh[1] = LoadGraph( "../images/playereffect2.png" );
		gh[2] = LoadGraph( "../images/playereffect3.png" );
	}

	for (int i = 0; i < 3; i++)
	{
		GetGraphSize( gh[i], &width[i], &height[i] );
	}

	rate = 1;
	alpha = 255;
	count = 0;
	flag = false;

}

void Effect_Pdead::Move()
{
	//���񂾂��p�x��ۑ�
	if (count == 0)
	{
		for (int i = 0; i < EFFECT_PDEADNUM; ++i)
		{
			expand[i].rad = rand() % 628 / 100;
			expand[i].speed = rand() % 10;
			expand[i].x = x;
			expand[i].y = y;
		}
	}


	rate = 0.5 + (count*0.05);


	alpha = 255 - (255 / 40)*count;


	rota = 0.05*count;


	//���W�̈ړ�
	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		expand[i].x += cos( expand[i].rad )*expand[i].speed;
		expand[i].y += sin( expand[i].rad )*expand[i].speed;
	}


	++count;

	if (count == 40)
	{
		flag = false;
		count = 0;
	}
}

void Effect_Pdead::Draw()
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, alpha );
	//�~�`�̃G�t�F�N�g�`��
	DrawRotaGraph( x, y, rate, 0, gh[0], TRUE );

	//�~�Ղ̃G�t�F�N�g�`��(2��)
	DrawRotaGraph( x, y, 1.0, rota, gh[1], TRUE );
	DrawRotaGraph( x, y, 1.0, 6.28 - rota, gh[1], TRUE );

	//�p�[�e�B�N���G�t�F�N�g�`��
	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		DrawGraph( expand[i].x - width[2] / 2, expand[i].y - height[2] / 2, gh[2], TRUE );
	}
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
}

void Effect_Pdead::SetFlag( double x, double y )
{
	count = 0;

	this->x = x;
	this->y = y;

	flag = true;
}

bool Effect_Pdead::GetFlag()
{
	return flag;
}

void Effect_Pdead::Update_All()
{
	if (flag)
	{
		Move();
	}
}

void Effect_Pdead::Draw_All()
{
	if (flag)
	{
		Draw();
	}
}

void Effect_Pdead::All()
{
	//�t���O�����Ă�Ƃ��������s
	if (flag)
	{
		Move();
		Draw();
	}
}