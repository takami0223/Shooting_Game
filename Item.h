#pragma once

#include "define.h"

class Item
{
private:
	//�O���t�B�b�N�n���h��
	static int gh[ITEM_TYPE_NUM], ghs[ITEM_TYPE_NUM];

	//�ǂ����̃A�C�e�����������ϐ�
	//int item_type;
	//int effect_type;
	int type;

	//���W
	double x, y;
	double prev_y;

	//��]�p�x
	double rad;

	//�J�E���g
	int count;

	//�A�C�e�����������n�߂�t���O
	bool fall_flag;

	//�o�������ǂ����̃t���O
	bool flag;

private:
	void Move();
	void Draw();

public:
	Item();
	void SetFlag( double x, double y, int type );
	bool GetFlag();
	void Delete();
	void GetPosition( double *x, double *y );
	int  GetType();
	void Update_All();
	void Draw_All();
	void All();
};