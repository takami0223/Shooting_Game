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

	//敵の種類
	this->type = type;

	//弾の種類
	this->stype = stype;

	//移動パターンとショットパターン
	this->m_pattern = m_pattern;
	this->s_pattern = s_pattern;

	//移動スピード
	this->move_speed = move_speed;

	//座標セット
	this->x = x;
	this->y = y;

	//出現、停止、発射、帰還時間セット
	this->in_time = in_time;
	this->stop_time = stop_time;
	this->shot_time = shot_time;
	this->out_time = out_time;

	//hpとアイテム代入
	this->hp = hp;
	this->item = item;

	this->ebarrier_hp = barrier_hp;

	if (this->ebarrier_hp > 0) this->ebarrier_flag = true;
	else this->ebarrier_flag = false;

	//this->ebarrier_flag = barrier_flag;

	ebarrier_gh = LoadGraph( "../images/barrier02.png" );

	//敵画像とサイズ取得
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

	//弾画像読み込み(+)
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

	//発射音読み込み(+)
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

	//弾の初期化
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
		//敵の動き方パターン(+)
		switch (m_pattern)
		{
			//途中で止まって、そのまま後ろに帰るパターン
			case MOVE_LINEDOWN:
				//出てきてから止まる時間までの間なら下に移動
				if (in_time < All_count && All_count < stop_time)
				{
					y += move_speed;
					//帰還時間を過ぎたら戻る。
				}
				else if (All_count > out_time)
				{
					y -= move_speed;
				}
				break;

			//そのまま止まらずに下に行くパターン
			case MOVE_LINE:
				if (in_time <= All_count)
				{
					y += move_speed;
				}
				break;

			//ちょっとずつ左に移動しながら消えていく
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

			//ちょっとずつ右に移動しながら消えていく
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

	//発射タイミングになったら、フラグを立てる
	if (shot_time == All_count)
	{
		sflag = true;
	}

	//フラグ立ってるときだけ
	if (sflag)
	{
		s_shot = false;

		if (!deadflag)
		{

			//敵とプレイヤーとの座標の差から逆正接を求める
			//初回のみ実行

			if (scount == 0)
				rad = atan2( p_y - y, p_x - x );

			//敵のショットパターン(+)
			switch (s_pattern)
			{
				//前方にショット
				case SHOT_LINE:
					//5ループに一回発射。計5発
					if (scount % 5 == 0 && scount <= 20)
					//if (scount % 10 == 0 && scount <= 40)

					{
						for (int i = 0; i < ENEMY_SNUM; ++i)
						{
							//フラグが立ってない弾を探して、座標等をセット
							if (shot[i].flag == false)
							{
								shot[i].flag = true;
								shot[i].x = x;
								shot[i].y = y;
								shot[i].rad = rad;
								break;
							}
						}

						//ショットサウンドフラグを立てる
						s_shot = true;
					}
					break;

					//プレイヤーに向かって直線ショット
				case SHOT_HOMING_LINE1:
					//6ループに一回発射。54までなので10発発射。
					if (scount % 6 == 0 && scount <= 54)
					//if (scount % 15 == 0 && scount <= 75)

					{
						for (int i = 0; i < ENEMY_SNUM; ++i)
						{
							//フラグが立ってない弾を探して、座標等をセット
							if (shot[i].flag == false)
							{
								shot[i].flag = true;
								shot[i].x = x;
								shot[i].y = y;
								shot[i].rad = rad;
								break;
							}
						}
						//ショットサウンドフラグを立てる
						s_shot = true;
					}
					break;

					//3直線ショット
				case SHOT_HOMING_LINE3:
					//10ループに一回発射。1ループに3発なので5ループさせると１５発発射
					if (scount % 10 == 0 && scount <= 30)
					//if (scount % 15 == 0 && scount <= 45)

					{
						for (int i = 0; i < ENEMY_SNUM; ++i)
						{
							//フラグが立ってない弾を探して、座標等をセット
							if (shot[i].flag == false)
							{
								shot[i].flag = true;
								shot[i].x = x;
								shot[i].y = y;

								//0の時は左より
								if (num == 0)
								{

									//敵とプレイヤーとの逆正接から10度引いたラジアンを代入
									shot[i].rad = rad - (10 * 3.14 / 180);
									//1の時はプレイヤー一直線
								}
								else if (num == 1)
								{
									//敵とプレイヤーとの逆正接を代入
									shot[i].rad = rad;
									//2の時は右より
								}
								else if (num == 2)
								{
									//敵とプレイヤーとの逆正接から10度足したラジアンを代入
									shot[i].rad = rad + (10 * M_PI / 180);

								}
								++num;

								//3発発射したら,numを0にしてループを抜ける。
								if (num == 3)
								{
									num = 0;
									break;
								}
							}
						}
						//ショットサウンドフラグを立てる
						s_shot = true;
					}
					break;

					//乱射ショット
				case SHOT_HOMING_SHOOTING:
					//1ループ毎に1発発射

					if (scount % 3 == 0 && scount <= 27) //42
					//if (scount % 10 == 0 && scount <= 90)

					{
						for (int i = 0; i < ENEMY_SNUM; ++i)
						{
							//フラグが立ってない弾を探して、座標等をセット
							if (shot[i].flag == false)
							{
								shot[i].flag = true;
								shot[i].x = x;
								shot[i].y = y;
								//初回だけ乱数初期化
								if (num == 0)
									srand( (unsigned int)time( NULL ) );

								shot[i].rad = atan2( p_y - y, p_x - x ) - (60 * M_PI / 180) + ((rand() % 120)*M_PI / 180);
								++num;
								break;
							}
						}
						//ショットサウンドフラグを立てる
						s_shot = true;
					}
					break;
			}
		}


		//フラグが立ってる弾の数
		int s = 0;

		//フラグ立ってる弾だけ、弾の移動を行う
		for (int i = 0; i < ENEMY_SNUM; ++i)
		{
			if (shot[i].flag)
			{
				//敵のショットパターンに合わせた弾の動き(+)
				switch (shot[i].pattern)
				{
					//単純に下に発射
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

				//弾が画面をはみ出たらフラグを戻す。
				if (ShotOutCheck( i ))
				{
					shot[i].flag = false;
					continue;
				}
				++s;
			}
		}
		//sがゼロということは発射中の弾がない。
		//かつdeadflagがTRUEということはこの敵のクラスは消滅させてもよい
		if (s == 0 && deadflag)
		{
			//敵クラス消滅フラグをTRUEにする
			endflag = true;
		}

		++scount;
	}
}

void Enemy::Draw()
{
	int temp;

//弾から最初に描画
//if (!deadflag) //有効にすると敵を倒したとき弾も消滅
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