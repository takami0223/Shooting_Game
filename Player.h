//#ifndef _PLAYER_H_
//#define _PLAYER_H_

#pragma once

#include "define.h"
#include "Effect_Pdead.h"
#include "Ball.h"

enum StatusData
{
	GRAZE,
	STOCK,
	HP,
	SPEED,
	SPEED_LIMIT,
	POWER,
	POWER_LIMIT,
	RAPIDFIRE
};

struct Shot
{
	bool flag;         //�e�����˒����ǂ���
	double x;		   //����x���W
	double y;          //����y���W
	int gh;            //���̃O���t�B�b�N�n���h���ϐ�
	int width, height; //�摜��
	double rad;		   //�p�x
	int type;		   //�e�̎��(0�Ȃ�ʏ�A1�Ȃ�ǔ�
};

class Player
{
private:

	Effect_Pdead effect_Pdead;
	Ball ball;

	Shot shot[PSHOT_NUM];

	int playerImgWidth, playerImgHeight;  //�摜��
	int playerGh[12];         //�O���t�B�b�N�n���h���i�[�p�z��
	float move;         //�ړ��W��
	int xcount, ycount; //������,�c�����̃J�E���g��
	int ix, iy, result; //�Y���p�ϐ�

	static int chargeEffectHandle; //�`���[�W�G�t�F�N�g�n���h��

	int graze;			//�O���C�Y��
	int stock;			//�c�@��
	int life;           //�̗�
	int speed;			//�X�s�[�h�A�C�e���擾��
	int power;			//�p���[�A�C�e���擾��
	int powerLimit;
	int speedLimit;

	//�A�C�e�����ɉ����ĕω�����X�e�[�^�X
	double playerSpeed; //�v���C���[�̃X�s�[�h
	int rapidfire;		//�A�ˈ����ɂȂ�t���[����
	int shotInterval;		//�A�˂̍ۂ̒e�̊Ԋu�t���[����

	//�X�e�[�^�X�̍ō����
	double bestPlayerSpeed;
	int bestRapidfire;
	int bestShotInterval;

	//�X�e�[�^�X�̍Œ�ۏ�
	double initPlayerSpeed;
	int initRapidfire;
	int initShotinterval;

	int count;			//player�N���X�̎��s�t���[����
	int dcount;			//�_���[�W���̃J�E���g
	int ccount;			//�`���[�W���̃J�E���g

	bool dcountInitFlag;	//dcount�����������ꂽ��
	bool damageFlag;    //�_���[�W���󂯂����̃t���O
	bool damageZeroFlag;//���G��Ԃ��̃t���O
	bool deadFlag;		//���C�t��0�ɂȂ�A�Q�[���I�[�o�[�ɂȂ������̃t���O

	bool s_charge;		//�`���[�W���̃t���O
	bool s_chargeNow;  //�`���[�W���̃t���O
	bool s_chargeStop;	//�`���[�W�I�����̃t���O
	bool s_shot;	    //�e�𔭎˂��ꂽ���̃t���O


public:
	double x, y;	//�L�����N�^�[��x���W,y���W
	double e_x, e_y;//�G�̍��W
	double b_x, b_y;//�{�X�̍��W
	bool boss_flag;
	int nearindex;

private:
	void Move();
	void Shot();
	void Draw();

	void BallUpdate();
	void BallDraw();
	void BallShotSet( int index );

public:

	Player();

	//�l�̐ݒ�
	void AddStatus( StatusData data, int num );

	//�l�̎擾
	int GetStatus( StatusData data );
	void GetPosition( double *x, double *y );
	bool GetShotPosition( int index, double *x, double *y );

	//�t���O�̐ݒ�
	void SetShotFlag( int index, bool flag );
	void SetDamageFlag( int damage );

	//�t���O�̎擾
	bool GetDamageFlag();
	bool GetDamageZeroFlag();
	bool GetDeadFlag();
	bool isPlayShotSound();
	bool isPlayChargeSound();
	bool isPlayChargeStopSound();

	//All
	void Update_All();
	void Draw_All();
};

//#endif // !_PLAYER_H_