#include "Item.h"
#include "DxLib.h"

int Item::gh[ITEM_TYPE_NUM] = { 0,0,0,0 };
int Item::ghs[ITEM_TYPE_NUM] = { 0,0,0,0 };

Item::Item()
{
	if (gh[0] == 0)
	{
		/*
		0:�X�R�A�v���X
		1:�p���[�A�b�v
		2:�X�s�[�h�A�b�v
		3:HP��
		*/

		/*�w�i*/
		gh[0] = LoadGraph( "../images/item2.png" );
		gh[1] = LoadGraph( "../images/item5.png" );
		gh[2] = LoadGraph( "../images/item3.png" );
		gh[3] = LoadGraph( "../images/item4.png" );
		/*�A�C�e���\��*/
		ghs[0] = LoadGraph( "../images/items6.png" );
		ghs[1] = LoadGraph( "../images/items9.png" );
		ghs[2] = LoadGraph( "../images/items8.png" );
		ghs[3] = LoadGraph( "../images/items10.png" );

	}

	x = y = 0;
	rad = 0;
	count = 0;
	fall_flag = false;
	flag = false;
}

void Item::Move()
{
	double tempy;

	//0.04���W�A��(��2�x)����]������B
	rad = 0.04*count;

	++count;

	if (!fall_flag)
	{
		tempy = y;
		y += (y - prev_y) + 1;
		//���_�܂ł�������t���O���Ă�
		if ((y - prev_y) + 1 == 0)
		{
			fall_flag = true;
		}
		prev_y = tempy;
	}
	else
	{
		//�������͈�葬�x�ŗ���
		y += 1.5;
	}

	//��ʂ̊O�ɂ͂ݏo����t���O��߂��B
	if (y > 500)
	{
		Delete();
	}
}

void Item::Draw()
{
	DrawRotaGraph( x, y, 1.0, rad, gh[type], TRUE );
	DrawRotaGraph( x, y, 1.0, 0, ghs[type], TRUE );
}

void Item::GetPosition( double *x, double *y )
{
	*x = this->x;
	*y = this->y;
}

int Item::GetType()
{
	return type;
}

void Item::SetFlag( double x, double y, int type )
{
	this->x = x;
	this->y = y - 8;
	prev_y = y;
	this->type = type;

	flag = true;
}

bool Item::GetFlag()
{
	return flag;
}

void Item::Delete()
{
	count = 0;
	fall_flag = false;
	flag = false;
}

void Item::Update_All()
{
	if (flag)
	{
		Move();
	}
}

void Item::Draw_All()
{
	if (flag)
	{
		Draw();
	}
}

void Item::All()
{
	Move();
	Draw();
}