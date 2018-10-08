#include "Effect_Pbarrier.h"
#include "DxLib.h"

int Effect_Pbarrier::gh_1 = 0;
int Effect_Pbarrier::gh_2 = 0;
int Effect_Pbarrier::gauge_base = 0;
int Effect_Pbarrier::gauge_cover = 0;

int Effect_Pbarrier::move_handle = 0;
int Effect_Pbarrier::break_handle = 0;

Effect_Pbarrier::Effect_Pbarrier()
{
	x = y = 0;

	if (gh_1 == 0)
	{
		gh_1 = LoadGraph( "../images/barrier03.png" );
		gh_2 = LoadGraph( "../images/barrier01.png" );
		gauge_cover = LoadGraph( "../images/gauge_cover02.png" );
		gauge_base = LoadGraph( "../images/gauge_base01.png" );
	}

	gauge = 0;
	gauge_width = 88;

	h = 0;
	r = g = b = 0;

	barrier_hp = BARRIER_HP_1;
	barrier_flag = false;
	barrier_break_flag = false;
	full_barrier_flag = false;

	if (move_handle == 0)
	{
		move_handle = LoadGraph( "../effects/barrier_open.mp4" );
		break_handle = LoadGraph( "../effects/player-barrier-break02.mp4" );

	}
	barrier_break_time = 0;
	//PlayMovieToGraph( move_handle );

}

void Effect_Pbarrier::Move()
{
	if (full_barrier_flag)
	{
		gauge = gauge_width * barrier_hp / BARRIER_HP_2;
		h = barrier_hp * (512.0f / BARRIER_HP_2) - 100;

	}
	else
	{
		gauge = gauge_width * barrier_hp / BARRIER_HP_1;
		h = barrier_hp * (512.0f / BARRIER_HP_1) - 100;

	}
}

void Effect_Pbarrier::Draw()
{
	//h = barrier_hp * (512.0f / BARRIER_HP_1) - 100;
	r = min( max( (384 - h), 0 ), 0xff );
	g = min( max( (h + 64), 0 ), 0xff );
	b = max( (h - 384), 0 );


	if (barrier_flag)
	{
		//SeekMovieToGraph( move_handle, 0 );
		PlayMovieToGraph( move_handle );

		if (full_barrier_flag)
		{
			DrawGraph( x - 50, y - 50, gh_1, true );
		}
		else
		{
			//PlayMovieToGraph( move_handle );
			SetDrawBlendMode( DX_BLENDMODE_ADD, 255 );
			DrawExtendGraph( x - 50, y - 50, x + 50, y + 50, move_handle, FALSE );
			//DrawExtendGraph( x - 70, y - 40, x + 70, y + 40, move_handle, FALSE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
			DrawGraph( x - 50, y - 50, gh_2, true );
		}

		//‘¼ƒQ[ƒW‚ÆyÀ•W‚Ì·‚Í+10
		DrawGraph( x - 50, y + 40, gauge_base, true );
		DrawBox( x - 46, y + 45, x - 46 + gauge, y + 50, GetColor( r, g, b ), true );
		DrawGraph( x - 50, y + 40, gauge_cover, true );

	}

	if (barrier_break_flag)
	{
		PlayMovieToGraph( break_handle );
		SetDrawBlendMode( DX_BLENDMODE_ADD, 255 );
		DrawExtendGraph( x - 50, y - 50, x + 50, y + 50, break_handle, FALSE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

		barrier_break_time++;

		if (barrier_break_time >= 180)
		{
			SeekMovieToGraph( break_handle, 0 );
			barrier_break_flag = false;

		}
	}

}

void Effect_Pbarrier::Update_All()
{
	if (barrier_flag || barrier_break_flag)
	{
		Move();
	}
}

void Effect_Pbarrier::Draw_All()
{
	if (barrier_flag || barrier_break_flag)
	{
		Draw();
	}
}

void Effect_Pbarrier::All()
{
	Move();
	Draw();
}

void Effect_Pbarrier::SetBarrierFlag( int barrierhp )
{
	barrier_hp = barrierhp;

	if (barrierhp > 0)
	{
		barrier_flag = true;

		if (barrierhp == BARRIER_HP_2)
		{
			full_barrier_flag = true;
		}
		SeekMovieToGraph( move_handle, 0 );

	}
}

bool Effect_Pbarrier::GetBarrierFlag()
{
	return barrier_flag;
}

void Effect_Pbarrier::Add_BarrierHp( int hp )
{
	//if (hp < 0) hp = -1;
	//int temp_barrier_hp = barrier_hp;
	barrier_hp += hp;
	//if(temp_barrier_hp - barrier_hp == 1)

	/*
	if (hp == BARRIER_HP_2)
	{
		full_barrier_flag = true;
	}
	*/
	if (barrier_hp <= 0)
	{
		barrier_flag = false;
		full_barrier_flag = false;
		barrier_break_flag = true;
		barrier_hp = 0;
		barrier_break_time = 0;
		SeekMovieToGraph( break_handle, 0 );

		//DeleteGraph( move_handle );

		//s_barrier_break = true;
	}
}

int Effect_Pbarrier::GetBarrierHp()
{
	return barrier_hp;
}
