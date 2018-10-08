//#ifndef _ENEMY_H_
//#define _ENEMY_H_

#pragma once

#include "define.h"

class Enemy
{
private:

	int gh[3];
	int width, height;

	//�����[�v�ڂœG���o�Ă��邩�A�~�܂邩�A�A�҂��邩�A���˃^�C�~���O
	int in_time, stop_time, out_time, shot_time;

	int type;	   //�G�̎��
	int stype;	   //�e�̎��
	int m_pattern; //�ړ��p�^�[��
	int s_pattern; //�V���b�g�p�^�[��
	int move_speed;//�ړ����x
	int hp;		   //HP
	int item;	   //�A�C�e��
	int count;	   //�G���o�����Ă���̃J�E���g
	int num;	   //���˂����e��
	double rad;	   //���˒���̃��W�A��
	bool s_shot;   //�e�����˂��ꂽ���̃t���O
	int s_sound;

	int ebarrier_gh; //�o���A�̃O���t�B�b�N�n���h��
	int ebarrier_hp; //�o���A��HP
	bool ebarrier_flag; //�o���A��\�邩
	bool deadflag; //�G���Ńt���O
	bool endflag;  //�G�N���X���Ńt���O

	E_Shot shot[ENEMY_SNUM]; //�e�\����
	bool sflag; //�V���b�g�����Ă�悤�ɂȂ������̃t���O
	int scount; //�V���b�g���łĂ�悤�ɂȂ��Ă���̃J�E���g

	int move_handle;

public:
	double x, y;
	double p_x, p_y;

private:
	void Move( int All_count );
	void Shot( int All_count );
	void Draw();

public:

	Enemy();
	Enemy( int type, int stype, int m_pattern, int s_pattern, int in_time, int stop_time, int shot_time, int out_time, int x, int y, int move_speed, int speed, int hp, int power, int barrier_hp, int item, int sound );
	virtual ~Enemy();
	Enemy( Enemy& a );
	void Update_All( int All_count );
	bool Draw_All();
	bool All( int All_count );

	bool OutCheck();
	bool ShotOutCheck( int i );

	void GetPosition( double *x, double *y );

	bool GetShotPosition( int index, double *x, double *y );
	void SetShotFlag( int index, bool flag );
	int GetShotType();
	int GetShotDamage( int index );

	void SetHp( int hp );
	int GetHp();

	int GetItemType();

	void SetGrazeFlag( int index );
	bool GetGrazeFlag( int index );

	void Add_BarrierHp( int hp );
	int GetBarrierHp();
	bool GetBarrierFlag();

	void SetDeadFlag();
	bool GetDeadFlag();

	bool isPlaySound();
	int GetPlaySound();

};

//#endif // !_ENEMY_H_


