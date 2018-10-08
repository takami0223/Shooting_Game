#pragma once

#include "define.h"

struct Peffect_Expand
{
	double x, y;
	double rad;
	int speed;

};

class Effect_Pdead
{
private:
	//���W
	double x, y;

	//�摜�̃T�C�Y
	int width[3];
	int height[3];

	//�O���t�B�b�N�n���h��
	static int gh[3];

	//�g�嗦
	double rate;

	//�����x
	int alpha;

	//�p�[�e�B�N���G�t�F�N�g�\����
	Peffect_Expand expand[EFFECT_PDEADNUM];

	//��]������摜�p�̊p�x
	double rota;

	//�J�E���g
	int count;

	//���s�����ǂ����̃t���O
	bool flag;

private:
	void Move();
	void Draw();
public:
	Effect_Pdead();
	void SetFlag( double x, double y );
	bool GetFlag();
	void Update_All();
	void Draw_All();
	void All();
};