
#include "Boss.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>

Boss::Boss( int stage_num )
{
//座標初期値
	x = 200;
	y = -100;
	prev_x = 200;
	prev_y = -100;

	//画像読み込み
	if (stage_num == 1)
	{
		gh_face[0] = LoadGraph( "../images/boss02.png" );
		gh_face[1] = LoadGraph( "../images/boss02_damage.png" );
		hp = BOSS1_HP;
	}
	else if (stage_num == 2)
	{
		gh_face[0] = LoadGraph( "../images/boss03.png" );
		gh_face[1] = LoadGraph( "../images/boss03_damage.png" );
		hp = BOSS2_HP;
	}
	else if (stage_num == 3)
	{
		gh_face[0] = LoadGraph( "../images/boss04.png" );
		gh_face[1] = LoadGraph( "../images/boss04_damage.png" );
		hp = BOSS3_HP;
	}
	else
	{
		gh_face[0] = LoadGraph( "../images/boss02.png" );
		gh_face[1] = LoadGraph( "../images/boss02_damage.png" );
		hp = BOSS1_HP;
	}

	gh_shot[0] = LoadGraph( "../images/enemyshot1.png" );
	gh_shot[1] = LoadGraph( "../images/enemyshot2.png" );
	gh_shot[2] = LoadGraph( "../images/enemyshot3.png" );

	//弾初期化
	for (int i = 0; i < BOSS_SHOTNUM; ++i)
	{
		shot[i].type = 0;
		shot[i].flag = false;
		shot[i].gflag = false;
		shot[i].gh = 0;
		shot[i].pattern = 0;
		shot[i].rad = 0;
		shot[i].speed = 0;
		shot[i].power = 1;
		shot[i].x = 0;
		shot[i].y = 0;
	}

	raise = 2;
	raise2 = 2;
	angle = 0;
	move_pattern = 0;
	shot_pattern = 0;
	prev_move_pattern = 0;
	prev_shot_pattern = 0;

	movex = 0;
	movey = 180;

	waitcount = 0;
	wait = false;
	p3_state = 0;

	shotflag = false;
	damageflag = false;
	no_damageflag = false;
	//flag = true;
	flag = false;
	//hp = BOSS1_HP;
	prev_hp = 0;

	count = 0;
	scount = 0;
	temp_scount = 0;

	this->stage_num = stage_num;


	s_shot = false;
	//scflag = false;
}

void Boss::MoveInit( double bx, double by, int state )
{
	prev_x = x;
	prev_y = y;

	movex = bx - x;
	movey = by - y;

	angle = 0;

	p3_state = state;
}

void Boss::Move()
{

	switch (move_pattern)
	{
		case BOSS_MOVE_START:
			Appear();
			break;
		case BOSS_MOVE_PATTERN1:
			MovePattern1();
			break;
		case BOSS_MOVE_PATTERN2:
			MovePattern2();
			break;
		case BOSS_MOVE_PATTERN3:
			MovePattern3();
			break;
		case BOSS_MOVE_DEFAULT:
			MoveToDefault();
			break;
	}
}

void Boss::Shot()
{
	//何発発射したか
	int num = 0;
	//空いてる弾の添え字
	int index;

	//scountを戻すかどうかのフラグ
	bool scflag = false;
	static double trad;

	if (!damageflag)
	{

		if (scount == 0)
			trad = atan2( p_y - y, p_x - x );

		//サウンドフラグを戻す
		s_shot = false;

		//弾のセット
		switch (shot_pattern)
		{

			case BOSS_SHOT_LINE:
				if (scount % 5 == 0 && scount <= 15)
				//if (scount % 10 == 0 && scount <= 30)
				{

					while ((index = ShotSearch()) != -1)
					{

						shot[index].gh = gh_shot[1];
						shot[index].pattern = 0;//SHOT_HOMING_LINE1;
						shot[index].speed = 3 * stage_num;//6;
						shot[index].type = BALL_RAPIDFIRE;
						shot[index].power = 1;

						if (num == 0)
						{
							shot[index].rad = trad - (10 * M_PI / 180);
						}
						else if (num == 1)
						{
							shot[index].rad = trad - (5 * M_PI / 180);
						}
						else if (num == 2)
						{
							shot[index].rad = trad;
						}
						else if (num == 3)
						{
							shot[index].rad = trad + (5 * M_PI / 180);
						}
						else if (num == 4)
						{
							shot[index].rad = trad + (10 * M_PI / 180);
						}


						++num;

						s_shot = true;

						if (num == 5)
						{
							break;
						}
					}
				}

				break;
			case BOSS_SHOT_SHOTTING:
				//if (scount % 5 == 0)
				if (scount % 10 == 0)
				{
					if ((index = ShotSearch()) != -1)
					{
						shot[index].gh = gh_shot[2];
						shot[index].speed = 2 * stage_num;//4;
						shot[index].rad = atan2( p_y - y, p_x - x ) + (rand() % 41 - 20)*M_PI / 180;
						shot[index].pattern = 1;//SHOT_HOMING_SHOOTING;
						shot[index].type = BALL_SHOOTING;
						shot[index].power = 1;

						s_shot = true;

					}
				}

				break;

			case BOSS_SHOT_CIRCLE:
				if (scount % 30 == 0)
				{
					trad = atan2( p_y - y, p_x - x );
					while ((index = ShotSearch()) != -1)
					{

						shot[index].gh = gh_shot[0];
						shot[index].speed = 2 * stage_num;//5;
						shot[index].rad = trad + num * ((360 / 20)*M_PI / 180);
						shot[index].pattern = 2;//SHOT_LINE;
						shot[index].type = BALL_LINE;
						shot[index].power = 1;

						++num;

						if (num == 20)
						{
							break;
						}
						s_shot = true;
					}
				}
				break;

			case BOSS_SHOT_CIRCLE_LINE:
				if (scount % 15 == 0)
				{

					while ((index = ShotSearch()) != -1)
					{
						shot[index].gh = gh_shot[0];
						shot[index].speed = 3;
						shot[index].pattern = 3;//SHOT_LINE;
						shot[index].rad = ((360 / 20)*M_PI / 180)*num + ((scount / 15)*0.08);
						shot[index].type = BALL_LINE;
						shot[index].power = 1;

						++num;

						if (num == 20)
						{
							break;
						}
						s_shot = true;
					}
				}
				num = 0;
				if (scount % 5 == 0 && temp_scount <= scount)
				{

					while ((index = ShotSearch()) != -1)
					{
						shot[index].gh = gh_shot[1];
						shot[index].speed = 6;
						shot[index].pattern = 3;//SHOT_HOMING_LINE1;
						shot[index].type = BALL_RAPIDFIRE;
						shot[index].power = 1;
						if (num == 0)
						{
							shot[index].x = x - 50;
							shot[index].rad = atan2( p_y - y, p_x - (x - 50) );
						}
						else if (num == 1)
						{
							shot[index].x = x + 50;
							shot[index].rad = atan2( p_y - y, p_x - (x + 50) );
						}



						++num;


						if (num == 2)
						{
							//5発分打ち終わったら、60ループ(一秒間)停止
							if (temp_scount + 20 == scount)
							{
								temp_scount += 60;
							}
							break;
						}

						s_shot = true;
					}
				}
				break;

			default:
				break;
		}

		for (int i = 0; i < BOSS_SHOTNUM; ++i)
		{
			if (shot[i].flag)
			{
				switch (shot[i].pattern)
				{

					case 0:
						shot[i].x += shot[i].speed*cos( shot[i].rad );
						shot[i].y += shot[i].speed*sin( shot[i].rad );


						if (scflag == false && scount == 50)//40)
						{
							scflag = true;
						}

						break;

					case 1:
						shot[i].x += shot[i].speed*cos( shot[i].rad );
						shot[i].y += shot[i].speed*sin( shot[i].rad );

						break;

					case 2:
						shot[i].x += shot[i].speed*cos( shot[i].rad );
						shot[i].y += shot[i].speed*sin( shot[i].rad );
						break;

					case 3:
						shot[i].x += shot[i].speed*cos( shot[i].rad );
						shot[i].y += shot[i].speed*sin( shot[i].rad );
						break;

					default:
						break;
				}

				//弾がはみ出てたらフラグを戻す
				if (ShotOutCheck( i ))
				{
					shot[i].flag = false;
				}
			}
		}

		++scount;

		if (scflag)
		{
			scount = 0;
			//scflag = false;
		}
		/*
		if (scount == 40)
		{
			//scount = 0;
			//temp_scount = 0;
		}
		*/
	}
}

void Boss::Appear()
{
	double temp;

	angle += 2;

	temp = sin( angle*M_PI / 180 );

	x = 200;
	y = prev_y + temp * movey;

	//提位置まで移動したら移動パターンを1に変更
	if (angle == 90)
	{
		move_pattern = 1;
		angle = 0;
		shotflag = true;
	}
}

void Boss::MovePattern1()
{
	angle += raise;

	y = 80 + sin( angle*M_PI / 180 )*BOSS_SHAKE;

	if (angle == 90)
	{
		raise = -2;
	}
	else if (angle == -90)
	{
		raise = 2;
	}

	x = 200;
}

void Boss::MovePattern2()
{
	if (!wait)
	{

		x += raise2;

		if (x == 70)
		{
			raise2 = 2;
			wait = true;
		}
		else if (x == 330)
		{
			raise2 = -2;
			wait = true;
		}
	}

	if (wait)
	{
		++waitcount;
		if (waitcount == 20)
		{
			wait = false;
			waitcount = 0;
		}
	}
}

void Boss::MovePattern3()
{
	double temp;

	angle += 2;

	temp = sin( angle*M_PI / 180 );

	x = prev_x + temp * movex;
	y = prev_y + temp * movey;

	if (angle == 90)
	{

		if (p3_state == 0)
		{
			MoveInit( 70, 80, 1 );
		}
		else if (p3_state == 1)
		{
			MoveInit( 200, 160, 2 );
		}
		else
		{
			MoveInit( 330, 80, 0 );
		}
	}
}

void Boss::Draw()
{
	//if (!flag)
	//{
//弾から最初に描画
	for (int i = 0; i < BOSS_SHOTNUM; ++i)
	{
		if (shot[i].flag)
		{
			DrawRotaGraph( shot[i].x, shot[i].y, 1.0, shot[i].rad + 90 * M_PI / 180, shot[i].gh, TRUE );
		}
	}
//}

//弾があたったときはダメージ用の画像を描画、
	if (damageflag)
	{
		DrawRotaGraph( x, y, 1.0, 0, gh_face[1], TRUE );
	}
	else
	{
		//何も無いときは通常描画
		DrawRotaGraph( x, y, 1.0, 0, gh_face[0], TRUE );
	}


	damageflag = false;
}

int Boss::ShotSearch()
{
	bool check = false;
	int i = 0;

	for (i = 0; i < BOSS_SHOTNUM; ++i)
	{
		if (shot[i].flag == false)
		{
			check = true;
			break;
		}
	}

	if (check)
	{
		shot[i].flag = true;
		shot[i].x = x;
		shot[i].y = y;
	}
	else if (!check)
	{
		i = -1;
	}

	return i;
}

bool Boss::ShotOutCheck( int i )
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

void Boss::MoveToDefault()
{
	double temp;

	angle += 2;

	temp = sin( angle*M_PI / 180 );

	x = prev_x + temp * movex;
	y = prev_y + temp * movey;

	//指定した位置まで移動したら
	if (angle == 90)
	{

		//次の移動＆ショットパターンに変更
		SetMovePattern( prev_move_pattern + 1 );
		SetShotPattern( prev_shot_pattern + 1 );
		//無敵フラグを戻す
		no_damageflag = false;

		//移動パターンが３なら
		if (move_pattern == 3)
			MoveInit( 200, 160, 2 );
	}
}

void Boss::SetMovePattern( int pattern )
{
	prev_move_pattern = move_pattern;
	move_pattern = pattern;
}

void Boss::SetShotPattern( int pattern )
{
	prev_shot_pattern = shot_pattern;
	shot_pattern = pattern;
}


void Boss::GetPosition( double *x, double *y )
{
	*x = this->x;
	*y = this->y;
}

bool Boss::GetShotPosition( int index, double *x, double *y, int *type )
{
	if (shot[index].flag)
	{
		*x = shot[index].x;
		*y = shot[index].y;
		*type = shot[index].type;
		return true;
	}
	else
	{
		return false;
	}

}

void Boss::SetShotFlag( int index, bool flag )
{
	shot[index].flag = flag;
}

int Boss::GetShotDamage( int index )
{
	return shot[index].power;
}

bool Boss::GetGrazeFlag( int index )
{
	return shot[index].gflag;
}

void Boss::SetGrazeFlag( int index )
{
	shot[index].gflag = true;
}

void Boss::SetDamageSetting()
{
	prev_x = x;
	prev_y = y;

	movex = 200 - x;
	movey = 80 - y;

	angle = 0;

	no_damageflag = true;

	SetMovePattern( 4 );
	SetShotPattern( 4 );

}

bool Boss::GetDamageFlag()
{
	return damageflag;
}

bool Boss::GetNodamageFlag()
{
	return no_damageflag;
}

void Boss::SetFlag( bool flag )
{
	this->flag = flag;

	if (!flag)
	{
		prev_move_pattern = 0;
		prev_shot_pattern = 0;
	}
}

bool Boss::GetFlag()
{
	return flag;
}

void Boss::SetHp( int damage )
{
	prev_hp = hp;
	hp += damage;
	//damageflag = true;
}

int Boss::GetHp()
{
	return hp;
}

int Boss::GetPrevHp()
{
	return prev_hp;
}

void Boss::Update_All()
{
	Move();

	if (shotflag)
	{
		Shot();
	}
	++count;
}

void Boss::Draw_All()
{
	Draw();
}

void Boss::All()
{
	Move();
	Draw();
}