#include "Player.h"
//#include "Game.h"
#include "Keyboard.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>

int Player::chargeEffectHandle = 0;

Player::Player()
{
	/*�v���C���[�֘A�̏�����*/

	LoadDivGraph( "../images/shot_chara1.png", 12, 3, 4, 29, 40, playerGh );
	playerImgWidth = 29;
	playerImgHeight = 40;

	move = 1.0f;
	xcount = 0, ycount = 0;
	ix = 0, iy = 0, result = 0;

	x = PLAYER_INITX;
	y = PLAYER_INITY;


	stock = 5;//PLAYER_STOCK;
	life = 5;//PLAYER_LIFE;
	graze = 0;
	speed = 0;
	power = 0;

	powerLimit = POWER_DEFAULT_LIMIT;
	speedLimit = SPEED_DEFAULT_LIMIT;

	/*
	stock = PLAYER_STOCK;
	life = LIFE_LIMIT - 1;
	graze = GRAZE_LINIT - 16;
	speed = SPEED_LIMIT - 1;
	power = POWER_LIMIT - 1;
	*/
	bestPlayerSpeed = 6;
	bestRapidfire = 50;
	bestShotInterval = 3;

	initPlayerSpeed = playerSpeed = PLAYER_SPEED_NUM;
	initRapidfire = rapidfire = RAPIDFIRE_NUM;
	initShotinterval = shotInterval = SHOT_LIMIT_NUM;

	dcount = 0;
	ccount = 0;

	dcountInitFlag = false;
	damageFlag = false;
	damageZeroFlag = false;
	deadFlag = false;


	/*���֘A�̏�����*/
	s_charge = false;
	s_chargeStop = false;
	s_shot = false;


	/*�e�֘A�̏�����*/
	//�e������
	memset( shot, 0, sizeof( shot ) );

	//�e�摜�̓ǂݍ���
	int temp = LoadGraph( "../images/shot.png" );
	int w, h;
	GetGraphSize( temp, &w, &h );

	//�t���O�����ׂ�false
	//�O���t�B�b�N�n���h���Ɖ摜������
	for (int i = 0; i < PSHOT_NUM; i++)
	{
		shot[i].flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
		shot[i].rad = 0;
	}

	if (chargeEffectHandle == 0)
	{
		chargeEffectHandle = LoadGraph( "../effects/charge02.mp4" );
	}

	count = 0;

}

void Player::Move()
{
	/* �΂߈ړ��̈ړ��W��=0.71, �㉺���E�̈ړ��W��=1.0 */
	if (Keyboard_Get( KEY_INPUT_LEFT ) >= 1 || Keyboard_Get( KEY_INPUT_RIGHT ) >= 1)
	{
		if (Keyboard_Get( KEY_INPUT_UP ) >= 1 || Keyboard_Get( KEY_INPUT_DOWN ) >= 1)
		{
			move = 0.71f;
		}
		else
		{
			move = 1.0f;
		}
	}
	else if (Keyboard_Get( KEY_INPUT_UP ) >= 1 || Keyboard_Get( KEY_INPUT_DOWN ) >= 1)
	{
		move = 1.0f;
	}

	/* ���ݒn���W�̍X�V */
	if (Keyboard_Get( KEY_INPUT_LEFT ) >= 1)
	{
		x -= playerSpeed * move;
	}
	if (Keyboard_Get( KEY_INPUT_RIGHT ) >= 1)
	{
		x += playerSpeed * move;
	}
	if (Keyboard_Get( KEY_INPUT_UP ) >= 1)
	{
		y -= playerSpeed * move;
	}
	if (Keyboard_Get( KEY_INPUT_DOWN ) >= 1)
	{
		y += playerSpeed * move;
	}

	/* x�Ɋւ���ړ����� */
	if (x > 400 - MARGIN)
	{
		x = 400 - MARGIN;
	}
	else if (x < MARGIN)
	{
		x = MARGIN;
	}

	/* y�Ɋւ���ړ����� */
	if (y > 480 - playerImgHeight / 2 - MARGIN)
	{
		y = 480 - playerImgHeight / 2 - MARGIN;
	}
	else if (y < playerImgHeight / 2 + MARGIN)
	{
		y = playerImgHeight / 2 + MARGIN;
	}


	if (Keyboard_Get( KEY_INPUT_LEFT ) >= 1)
	{
		if (xcount > 0) xcount = 0;
		--xcount;
	}
	if (Keyboard_Get( KEY_INPUT_RIGHT ) >= 1)
	{
		if (xcount < 0) xcount = 0;
		++xcount;
	}
	if (Keyboard_Get( KEY_INPUT_UP ) >= 1)
	{
		if (ycount > 0) ycount = 0;
		--ycount;
	}
	if (Keyboard_Get( KEY_INPUT_DOWN ) >= 1)
	{
		if (ycount < 0) ycount = 0;
		++ycount;
	}

	ix = abs( xcount ) % 30 / 10;
	iy = abs( ycount ) % 30 / 10;

	if (xcount > 0)
	{
		ix += 3;
		result = ix;
	}
	else if (xcount < 0)
	{
		ix += 9;
		result = ix;
	}

	if (ycount > 0)
	{
		iy += 6;
		result = iy;
	}
	else if (ycount < 0)
	{
		iy += 0;
		result = iy;
	}

	if (move == 0.71f)
	{
		result = ix;
	}

	if (Keyboard_Get( KEY_INPUT_LEFT ) != 1 && Keyboard_Get( KEY_INPUT_RIGHT ) != 1)
	{
		xcount = 0;
	}
	if (Keyboard_Get( KEY_INPUT_UP ) != 1 && Keyboard_Get( KEY_INPUT_DOWN ) != 1)
	{
		ycount = 0;
	}

	++dcount;
	++count;
}

void Player::Shot()
{

	s_shot = false;
	int num = 0;

	if (!deadFlag)
	{
		//�L�[��������Ă��Ă��A6���[�v�Ɉ�񔭎�
		if (Keyboard_Get( KEY_INPUT_Z ) == 5 || (Keyboard_Get( KEY_INPUT_Z ) >= rapidfire && count % shotInterval == 0))
		{
			for (int i = 0; i < PSHOT_NUM; i++)
			{
				if (!shot[i].flag)
				{
					if (power < POWERUP_COUNT_1)
					{
						shot[i].flag = true;
						shot[i].x = x;
						shot[i].y = y;
						shot[i].rad = -M_PI / 2;
						shot[i].type = 0;
						break;
					}
					else if (power >= POWERUP_COUNT_1 && power < POWERUP_COUNT_2)
					{
						//0�̎����O������
						if (num == 0)
						{
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.57;
							shot[i].type = 0;
						}
						else if (num == 1)
						{
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.69;
							shot[i].type = 0;
						}
						else if (num == 2)
						{
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.45;
							shot[i].type = 0;
						}

						++num;

						if (num == 3)
						{
							break;
						}
					}
					else if (power >= POWERUP_COUNT_2 && power < POWERUP_COUNT_3)
					{
						//0�̎����O������
						if (num == 0)
						{
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.57;
							shot[i].type = 0;
						}
						else if (num == 1)
						{
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.69;
							shot[i].type = 0;
						}
						else if (num == 2)
						{
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.45;
							shot[i].type = 0;
						}
						else if (num > 2)
						{
							BallShotSet( i );
						}
						++num;
						if (num == 4)
						{
							break;
						}
					}
					else if (power >= POWERUP_COUNT_3)
					{
						//0�̎����O������
						if (num == 0)
						{
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.57;
							shot[i].type = 0;
						}
						else if (num == 1)
						{
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.69;
							shot[i].type = 0;
						}
						else if (num == 2)
						{
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.45;
							shot[i].type = 0;
						}
						else if (num > 2)
						{
							BallShotSet( i );
						}
						++num;
						if (num == 5)
						{
							break;
						}
					}
				}
			}
			s_shot = true;
		}
	}

	double trad;

	//�e���ړ������鏈��
	for (int i = 0; i < PSHOT_NUM; i++)
	{
		//���˂��Ă���e����
		if (shot[i].flag)
		{
			if (shot[i].type == 0)
			{
				shot[i].x += cos( shot[i].rad )*PSHOT_SPEED;
				shot[i].y += sin( shot[i].rad )*PSHOT_SPEED;
			}
			else if (shot[i].type == 1)
			{
				if (nearindex == -1)
				{
					trad = -M_PI / 2;
				}
				else
				{
					trad = atan2( e_y - shot[i].y, e_x - shot[i].x );
				}

				if (boss_flag)
				{
					trad = atan2( b_y - shot[i].y, b_x - shot[i].x );
				}
				shot[i].rad = trad;
				shot[i].x += cos( shot[i].rad )*PSHOT_SPEED;
				shot[i].y += sin( shot[i].rad )*PSHOT_SPEED;
			}

			//�e���͈͊O�ɂȂ�����
			if (shot[i].y < -10 || shot[i].x < -10 || shot[i].x > 410)
			{
				shot[i].flag = false;
			}
		}
	}


	if (Keyboard_Get( KEY_INPUT_Z ) == 0)
	{
		s_chargeNow = false;
		SeekMovieToGraph( chargeEffectHandle, 0 );
	}

	if (Keyboard_Get( KEY_INPUT_Z ) == 20)
	{
		s_charge = true;
		s_chargeNow = true;
	}
	else
	{
		s_charge = false;
	}

	if (Keyboard_Get( KEY_INPUT_Z ) == rapidfire)
	{
		s_chargeStop = true;
		s_chargeNow = false;
	}
	else
	{
		s_chargeStop = false;
	}
}

void Player::Draw()
{
	//�e�`��
	for (int i = 0; i < PSHOT_NUM; i++)
	{
		if (shot[i].flag)
		{
			DrawRotaGraph( shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * M_PI / 180), shot[i].gh, TRUE );
		}
	}

	//�c�@���c���Ă����
	if (stock > 0)
	{
		//�_���[�W���󂯂��v���C���[�`��
		if (damageFlag)
		{
			Keyboard_Reset();

			if (!dcountInitFlag)
			{
				dcount = 0;
				dcountInitFlag = true;
			}

			if (dcount > 0)
			{
				if (dcount % 2 == 0)
				{
					SetDrawBlendMode( DX_BLENDMODE_ALPHA, 0 );
					DrawGraph( x - playerImgWidth / 2, y - playerImgHeight / 2, playerGh[result], TRUE );
					SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
				}
				else
				{
					DrawGraph( x - playerImgWidth / 2, y - playerImgHeight / 2, playerGh[result], TRUE );
				}
			}
			//++dcount;
			if (dcount == 100)
			{
				damageFlag = false;
				dcountInitFlag = false;
				//dcount = 0;
			}
		}

		//���G���̃v���C���[�`��
		else if (damageZeroFlag)
		{
			if (!dcountInitFlag)
			{
				dcount = 0;
				dcountInitFlag = true;
			}

			if (dcount > 0)
			{
				if (dcount % 2 == 0)
				{
					SetDrawBlendMode( DX_BLENDMODE_ALPHA, 0 );
					DrawGraph( x - playerImgWidth / 2, y - playerImgHeight / 2, playerGh[result], TRUE );
					SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
				}
				else
				{
					DrawGraph( x - playerImgWidth / 2, y - playerImgHeight / 2, playerGh[result], TRUE );
				}
			}
			//++ccount;
			if (dcount == 100)
			{
				damageZeroFlag = false;
				dcountInitFlag = false;
				//ccount = 0;
			}
		}

		//���S���̃v���C���[�`��
		else if (deadFlag)
		{
			Keyboard_Reset();

			if (!dcountInitFlag)
			{
				dcount = 0;
				dcountInitFlag = true;
			}

			if (dcount > 40)
			{
				if (dcount % 2 == 0)
				{
					SetDrawBlendMode( DX_BLENDMODE_ALPHA, 140 );
					DrawGraph( PLAYER_INITX - playerImgWidth / 2, PLAYER_INITY - playerImgHeight / 2 - (dcount - 40) + 60, playerGh[1], TRUE );
					SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
				}
				else
				{
					DrawGraph( PLAYER_INITX - playerImgWidth / 2, PLAYER_INITY - playerImgHeight / 2 + 60 - (dcount - 40), playerGh[1], TRUE );
				}
			}
			//++dcount;
			if (dcount == 100)
			{
				deadFlag = false;
				//dcount = 0;

				//���W�������l�ɖ߂�
				x = PLAYER_INITX;
				y = PLAYER_INITY;

				//������̉摜�ɂ���
				result = 1;

				dcountInitFlag = false;

				damageZeroFlag = true;
			}
		}
		else
		{
			DrawGraph( x - playerImgWidth / 2, y - playerImgHeight / 2, playerGh[result], TRUE );

		}

		if (s_chargeNow)
		{
			PlayMovieToGraph( chargeEffectHandle );
			SetDrawBlendMode( DX_BLENDMODE_ADD, 255 );
			DrawExtendGraph( x - 40, y - 40, x + 40, y + 40, chargeEffectHandle, FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

		}
	}
}

void Player::Update_All()
{
	Move();
	Shot();
	BallUpdate();
}

void Player::Draw_All()
{
	Draw();
	BallDraw();
}

void Player::BallUpdate()
{
	if (power >= POWERUP_COUNT_2)
	{
		ball.Update_All( x, y );
	}
}

void Player::BallDraw()
{
	if (power >= POWERUP_COUNT_2 && !deadFlag)
	{
		ball.Draw_All();
	}
}

void Player::BallShotSet( int index )
{
	double ty;
	double trad;
	static int toggle = 1;
	//int tindex; //nearindex

	ty = ball.GetPosition();

	if (nearindex == -1)
	{
		trad = -M_PI / 2;
	}
	else
	{
		trad = atan2( e_y - ty + BALL_INITY, e_x - x + (toggle*BALL_INITX) );
	}

	shot[index].flag = true;
	shot[index].x = x + BALL_INITX * toggle;
	shot[index].y = ty + BALL_INITY;
	shot[index].rad = trad;
	shot[index].type = 1;

	if (toggle == 1)
	{
		toggle = -1;
	}
	else
	{
		toggle = 1;
	}
}

void Player::GetPosition( double *x, double *y )
{
	*x = this->x;
	*y = this->y;
}

bool Player::GetShotPosition( int index, double *x, double *y )
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

void Player::AddStatus( StatusData data, int num )
{
	switch (data)
	{
		case GRAZE:
			graze += num;

			if (graze > GRAZE_LINIT) graze = 0;

			break;

		case STOCK:
			stock += num;
			break;

		case HP:
			//if (this->life <= 0) this->life = 0; //�␳
			life += num;
			if (life > LIFE_LIMIT)
			{
				life = LIFE_LIMIT;
			}
			else if (life < 0)
			{
				life = 0;
			}
			break;

		case SPEED:
			speed += num;

			playerSpeed = PLAYER_SPEED_NUM + speed * 0.05;//0.1;
			if (playerSpeed > bestPlayerSpeed) playerSpeed = bestPlayerSpeed;

			if (speed > speedLimit)
			{
				speed = speedLimit;
			}
			else if (speed < 0)
			{
				speed = 0;
			}
			break;

		case SPEED_LIMIT:
			speedLimit += num;
			break;

		case POWER:
			power += num;


			rapidfire = RAPIDFIRE_NUM - power * 7;//10;//20;
			if (rapidfire < bestRapidfire) rapidfire = bestRapidfire;

			shotInterval = SHOT_LIMIT_NUM - power * 0.2;//0.3;
			if (shotInterval < bestShotInterval) shotInterval = bestShotInterval;
			/*
			if (power % 3 == 0 && power != 0)
			{
				shot_limit = SHOT_LIMIT_NUM - limit;
				if (shot_limit < min_shot_limit) shot_limit = min_shot_limit;
				limit++;
			}
			*/

			if (power > powerLimit)
			{
				power = powerLimit;
			}
			else if (power < 0)
			{
				power = 0;
			}
			break;

		case POWER_LIMIT:
			powerLimit += num;
			break;

		case RAPIDFIRE:
			break;


		default:
			break;
	}
}

int Player::GetStatus( StatusData data )
{
	switch (data)
	{
		case GRAZE:
			return graze;
			break;

		case STOCK:
			return stock;
			break;

		case HP:
			return life;
			break;

		case SPEED:
			return speed;
			break;

		case SPEED_LIMIT:
			return speedLimit;
			break;

		case POWER:
			return power;
			break;

		case POWER_LIMIT:
			return powerLimit;
			break;

		case RAPIDFIRE:
			return rapidfire;
			break;

		default:
			return 0;
			break;
	}
}

void Player::SetShotFlag( int index, bool flag )
{
	shot[index].flag = flag;
}

void Player::SetDamageFlag( int damage )
{
	if (damage != 0)
	{
	//���C�t�����炷
		if (!damageFlag)
			life -= damage;
		if (life <= 0)
		{
			deadFlag = true;
			life = 0;

			//���ŃG�t�F�N�g�̃t���O�𗧂Ă�
			effect_Pdead.SetFlag( x, y );
		}
		else
		{
			damageFlag = true;
		}
	}
	else if (damage == 0)
	{
		damageZeroFlag = true;
	}
}

bool Player::GetDamageFlag()
{
	return damageFlag;
}

bool Player::GetDamageZeroFlag()
{
	return damageZeroFlag;
}

bool Player::GetDeadFlag()
{
	return deadFlag;
}

bool Player::isPlayShotSound()
{
	return s_shot;
}

bool Player::isPlayChargeSound()
{
	return s_charge;
}

bool Player::isPlayChargeStopSound()
{
	return s_chargeStop;
}
