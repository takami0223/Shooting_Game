#include "Enemy.h"
//#include "Game.h"
#include "Keyboard.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>

Enemy::Enemy()
{
}

Enemy::Enemy( int type, int stype, int m_pattern, int s_pattern, int in_time, int stop_time, int shot_time, int out_time, int x, int y, int move_speed, int speed, int hp, int power, int barrier_hp, int item, int sound )
{

	srand( (unsigned int)time( NULL ) );

	width = 27;
	height = 25;

	p_x = 0;
	p_y = 0;

	s_shot = false;

	//�G�̎��
	this->type = type;

	//�e�̎��
	this->stype = stype;

	//�ړ��p�^�[���ƃV���b�g�p�^�[��
	this->m_pattern = m_pattern;
	this->s_pattern = s_pattern;

	//�ړ��X�s�[�h
	this->move_speed = move_speed;

	//���W�Z�b�g
	this->x = x;
	this->y = y;

	//�o���A��~�A���ˁA�A�Ҏ��ԃZ�b�g
	this->in_time = in_time;
	this->stop_time = stop_time;
	this->shot_time = shot_time;
	this->out_time = out_time;

	//hp�ƃA�C�e�����
	this->hp = hp;
	this->item = item;

	this->ebarrier_hp = barrier_hp;

	if (this->ebarrier_hp > 0) this->ebarrier_flag = true;
	else this->ebarrier_flag = false;

	//this->ebarrier_flag = barrier_flag;

	ebarrier_gh = LoadGraph( "../images/barrier02.png" );

	//�G�摜�ƃT�C�Y�擾
	switch (type)
	{
		case ENEMY_0:
			LoadDivGraph( "../images/enemy00.png", 3, 1, 3, 27, 25, gh );
			break;

		case ENEMY_1:
			LoadDivGraph( "../images/enemy01.png", 3, 1, 3, 27, 25, gh );
			break;

		case ENEMY_2:
			LoadDivGraph( "../images/enemy02.png", 3, 1, 3, 27, 25, gh );
			break;

		default:
			LoadDivGraph( "../images/enemy00.png", 3, 1, 3, 27, 25, gh );
			break;

	}

	//�e�摜�ǂݍ���(+)
	int i_temp = 0;
	switch (stype)
	{
		case BALL_LINE:
			i_temp = LoadGraph( "../images/enemyshot1.png" );
			break;
		case BALL_RAPIDFIRE:
			i_temp = LoadGraph( "../images/enemyshot2.png" );
			break;
		case BALL_SHOOTING:
			i_temp = LoadGraph( "../images/enemyshot3.png" );
			break;
	}
	int w, h;
	GetGraphSize( i_temp, &w, &h );

	//���ˉ��ǂݍ���(+)
	s_sound = 0;
	switch (sound)
	{
		case SOUND_LINE:
			s_sound = LoadSoundMem( "../sounds/beam-gun01.mp3" );
			break;
		case SOUND_HOMING_LINE1:
			s_sound = LoadSoundMem( "../sounds/beam-gun02.mp3" );
			break;
		case SOUND_HOMING_LINE3:
			s_sound = LoadSoundMem( "../sounds/beam-gun04.mp3" );
			break;
		case SOUND_HOMING_SHOOTING:
			s_sound = LoadSoundMem( "../sounds/beam-gun05.mp3" );
			break;
		default:
			break;
	}

	//�e�̏�����
	for (int i = 0; i < ENEMY_SNUM; ++i)
	{
		shot[i].flag = false;
		shot[i].x = x;
		shot[i].y = y;
		shot[i].gh = i_temp;
		shot[i].sh = s_sound;
		shot[i].width = w;
		shot[i].height = h;
		shot[i].pattern = s_pattern;
		shot[i].speed = speed;
		shot[i].power = power;
		shot[i].gflag = false;
	}

	count = 0;
	scount = 0;
	num = 0;
	rad = 0;

	deadflag = false;
	endflag = false;
	sflag = false;

	//move_handle = LoadGraph( "../sounds/nc150093.mp4" );
	//PlayMovieToGraph( move_handle );

}

Enemy::~Enemy()
{

}

Enemy::Enemy( Enemy& a )
{

}

void Enemy::Move( int All_count )
{
	if (!deadflag)
	{
		//�G�̓������p�^�[��(+)
		switch (m_pattern)
		{
			//�r���Ŏ~�܂��āA���̂܂܌��ɋA��p�^�[��
			case MOVE_LINEDOWN:
				//�o�Ă��Ă���~�܂鎞�Ԃ܂ł̊ԂȂ牺�Ɉړ�
				if (in_time < All_count && All_count < stop_time)
				{
					y += move_speed;
					//�A�Ҏ��Ԃ��߂�����߂�B
				}
				else if (All_count > out_time)
				{
					y -= move_speed;
				}
				break;

			//���̂܂܎~�܂炸�ɉ��ɍs���p�^�[��
			case MOVE_LINE:
				if (in_time <= All_count)
				{
					y += move_speed;
				}
				break;

			//������Ƃ����Ɉړ����Ȃ�������Ă���
			case MOVE_LEFTDOWN:
				if (in_time <= All_count)
				{
					y += move_speed;
					if (count % 10 == 0)
					{
						x -= move_speed;
					}
				}
				break;

			//������Ƃ��E�Ɉړ����Ȃ�������Ă���
			case MOVE_RIGHTDOWN:
				if (in_time <= All_count)
				{
					y += move_speed;
					if (count % 10 == 0)
					{
						x += move_speed;
					}
				}
				break;

			default:
				break;

		}
		if (All_count >= stop_time)
		{
			if (OutCheck())
			{
				deadflag = true;
			}
		}

		++count;
	}
}

void Enemy::Shot( int All_count )
{

	//���˃^�C�~���O�ɂȂ�����A�t���O�𗧂Ă�
	if (shot_time == All_count)
	{
		sflag = true;
	}

	//�t���O�����Ă�Ƃ�����
	if (sflag)
	{
		s_shot = false;

		if (!deadflag)
		{

			//�G�ƃv���C���[�Ƃ̍��W�̍�����t���ڂ����߂�
			//����̂ݎ��s

			if (scount == 0)
				rad = atan2( p_y - y, p_x - x );

			//�G�̃V���b�g�p�^�[��(+)
			switch (s_pattern)
			{
				//�O���ɃV���b�g
				case SHOT_LINE:
					//5���[�v�Ɉ�񔭎ˁB�v5��
					if (scount % 5 == 0 && scount <= 20)
					//if (scount % 10 == 0 && scount <= 40)

					{
						for (int i = 0; i < ENEMY_SNUM; ++i)
						{
							//�t���O�������ĂȂ��e��T���āA���W�����Z�b�g
							if (shot[i].flag == false)
							{
								shot[i].flag = true;
								shot[i].x = x;
								shot[i].y = y;
								shot[i].rad = rad;
								break;
							}
						}

						//�V���b�g�T�E���h�t���O�𗧂Ă�
						s_shot = true;
					}
					break;

					//�v���C���[�Ɍ������Ē����V���b�g
				case SHOT_HOMING_LINE1:
					//6���[�v�Ɉ�񔭎ˁB54�܂łȂ̂�10�����ˁB
					if (scount % 6 == 0 && scount <= 54)
					//if (scount % 15 == 0 && scount <= 75)

					{
						for (int i = 0; i < ENEMY_SNUM; ++i)
						{
							//�t���O�������ĂȂ��e��T���āA���W�����Z�b�g
							if (shot[i].flag == false)
							{
								shot[i].flag = true;
								shot[i].x = x;
								shot[i].y = y;
								shot[i].rad = rad;
								break;
							}
						}
						//�V���b�g�T�E���h�t���O�𗧂Ă�
						s_shot = true;
					}
					break;

					//3�����V���b�g
				case SHOT_HOMING_LINE3:
					//10���[�v�Ɉ�񔭎ˁB1���[�v��3���Ȃ̂�5���[�v������ƂP�T������
					if (scount % 10 == 0 && scount <= 30)
					//if (scount % 15 == 0 && scount <= 45)

					{
						for (int i = 0; i < ENEMY_SNUM; ++i)
						{
							//�t���O�������ĂȂ��e��T���āA���W�����Z�b�g
							if (shot[i].flag == false)
							{
								shot[i].flag = true;
								shot[i].x = x;
								shot[i].y = y;

								//0�̎��͍����
								if (num == 0)
								{

									//�G�ƃv���C���[�Ƃ̋t���ڂ���10�x���������W�A������
									shot[i].rad = rad - (10 * 3.14 / 180);
									//1�̎��̓v���C���[�꒼��
								}
								else if (num == 1)
								{
									//�G�ƃv���C���[�Ƃ̋t���ڂ���
									shot[i].rad = rad;
									//2�̎��͉E���
								}
								else if (num == 2)
								{
									//�G�ƃv���C���[�Ƃ̋t���ڂ���10�x���������W�A������
									shot[i].rad = rad + (10 * M_PI / 180);

								}
								++num;

								//3�����˂�����,num��0�ɂ��ă��[�v�𔲂���B
								if (num == 3)
								{
									num = 0;
									break;
								}
							}
						}
						//�V���b�g�T�E���h�t���O�𗧂Ă�
						s_shot = true;
					}
					break;

					//���˃V���b�g
				case SHOT_HOMING_SHOOTING:
					//1���[�v����1������

					if (scount % 3 == 0 && scount <= 27) //42
					//if (scount % 10 == 0 && scount <= 90)

					{
						for (int i = 0; i < ENEMY_SNUM; ++i)
						{
							//�t���O�������ĂȂ��e��T���āA���W�����Z�b�g
							if (shot[i].flag == false)
							{
								shot[i].flag = true;
								shot[i].x = x;
								shot[i].y = y;
								//���񂾂�����������
								if (num == 0)
									srand( (unsigned int)time( NULL ) );

								shot[i].rad = atan2( p_y - y, p_x - x ) - (60 * M_PI / 180) + ((rand() % 120)*M_PI / 180);
								++num;
								break;
							}
						}
						//�V���b�g�T�E���h�t���O�𗧂Ă�
						s_shot = true;
					}
					break;
			}
		}


		//�t���O�������Ă�e�̐�
		int s = 0;

		//�t���O�����Ă�e�����A�e�̈ړ����s��
		for (int i = 0; i < ENEMY_SNUM; ++i)
		{
			if (shot[i].flag)
			{
				//�G�̃V���b�g�p�^�[���ɍ��킹���e�̓���(+)
				switch (shot[i].pattern)
				{
					//�P���ɉ��ɔ���
					case SHOT_LINE:
						shot[i].y += shot[i].speed;
						break;

					case SHOT_HOMING_LINE1:
						shot[i].x += shot[i].speed*cos( shot[i].rad );
						shot[i].y += shot[i].speed*sin( shot[i].rad );
						break;

					case SHOT_HOMING_LINE3:
						shot[i].x += shot[i].speed*cos( shot[i].rad );
						shot[i].y += shot[i].speed*sin( shot[i].rad );
						break;

					case SHOT_HOMING_SHOOTING:
						shot[i].x += shot[i].speed*cos( shot[i].rad );
						shot[i].y += shot[i].speed*sin( shot[i].rad );
						break;

				}

				//�e����ʂ��͂ݏo����t���O��߂��B
				if (ShotOutCheck( i ))
				{
					shot[i].flag = false;
					continue;
				}
				++s;
			}
		}
		//s���[���Ƃ������Ƃ͔��˒��̒e���Ȃ��B
		//����deadflag��TRUE�Ƃ������Ƃ͂��̓G�̃N���X�͏��ł����Ă��悢
		if (s == 0 && deadflag)
		{
			//�G�N���X���Ńt���O��TRUE�ɂ���
			endflag = true;
		}

		++scount;
	}
}

void Enemy::Draw()
{
	int temp;

//�e����ŏ��ɕ`��
//if (!deadflag) //�L���ɂ���ƓG��|�����Ƃ��e������
//{
	for (int i = 0; i < ENEMY_SNUM; ++i)
	{
		if (shot[i].flag)
		{
			if (stype == BALL_LINE || stype == BALL_SHOOTING)
			{
				DrawGraph( shot[i].x - shot[i].width / 2, shot[i].y - shot[i].height / 2, shot[i].gh, true );
			}
			else
			{
				DrawRotaGraph( shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * M_PI / 180), shot[i].gh, true );
			}
		}
	}
	//}

	if (!deadflag)
	{

		temp = count % 40 / 10;
		if (temp == 3)
			temp = 1;

		DrawGraph( x - width / 2, y - height / 2, gh[temp], TRUE );

		if (ebarrier_flag)
		{
			//PlayMovieToGraph( move_handle );
			//DrawExtendGraph( x, y, x + width, y + height, move_handle, FALSE );
			DrawGraph( x - width / 2 - 10, y - height / 2 - 10, ebarrier_gh, TRUE );
		}

	}

}

void Enemy::Update_All( int All_count )
{
	Move( All_count );
	Shot( All_count );
}

bool Enemy::Draw_All()
{
	Draw();

	return endflag;
}

bool Enemy::OutCheck()
{
	if (x < -50 || x > 520 || y < -30 || y > 530)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::ShotOutCheck( int i )
{
	if (shot[i].x < -20 || shot[i].x > 420 || shot[i].y < 20 || shot[i].y > 500)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::GetPosition( double *x, double *y )
{
	*x = this->x;
	*y = this->y;
}

bool Enemy::GetShotPosition( int index, double *x, double *y )
{
	if (shot[index].flag)
	{
		*x = shot[index].x;
		*y = shot[index].y;
		return true;
	}
	else
	{
		return false;
	}
}
void Enemy::SetShotFlag( int index, bool flag )
{
	shot[index].flag = flag;
}

int Enemy::GetShotType()
{
	return stype;
}

int Enemy::GetShotDamage( int index )
{
	return shot[index].power;
}

void Enemy::SetHp( int hp )
{
	this->hp += hp;

	if (this->hp <= 0) deadflag = true;
}

int Enemy::GetHp()
{
	return hp;
}

int Enemy::GetItemType()
{
	return item;
}

void Enemy::SetGrazeFlag( int index )
{
	shot[index].gflag = true;
}

bool Enemy::GetGrazeFlag( int index )
{
	return shot[index].gflag;
}

void Enemy::Add_BarrierHp( int hp )
{
	ebarrier_hp += hp;

	if (ebarrier_hp <= 0)
	{
		//DeleteGraph( move_handle );
		ebarrier_flag = false;
	}
}

int Enemy::GetBarrierHp()
{
	return ebarrier_hp;
}

bool Enemy::GetBarrierFlag()
{
	return ebarrier_flag;
}

void Enemy::SetDeadFlag()
{
	deadflag = true;
}

bool Enemy::GetDeadFlag()
{
	return deadflag;
}

bool Enemy::isPlaySound()
{
	return s_shot;
}

int Enemy::GetPlaySound()
{
	return s_sound;
}

bool Enemy::All( int All_count )
{
	Move( All_count );
	Shot( All_count );
	Draw();

	//++count;

	return endflag;
}