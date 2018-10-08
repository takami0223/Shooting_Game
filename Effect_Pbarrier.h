#pragma once

#include "define.h"

class Effect_Pbarrier
{
private:
	static int gh_1; //�o���A�̃O���t�B�b�N�n���h��
	static int gh_2;
	static int gauge_cover, gauge_base; //�o���A�Q�[�W�̃O���t�B�b�N�n���h��
	static int move_handle;
	static int break_handle;

	int gauge;
	int gauge_width;

	double h;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	int barrier_hp;    //�o���A�̑ϋv�l
	bool barrier_flag; //�o���A���\���Ă��邩
	bool barrier_break_flag; //�o���A�����ꂽ��
	bool full_barrier_flag; //�ō��̃o���A���\���Ă��邩

	bool barrier_break_time;


private:
	void Move();
	void Draw();

public:
	double x, y;

	Effect_Pbarrier();

	void SetBarrierFlag( int barrierhp );
	bool GetBarrierFlag();

	void Add_BarrierHp( int hp );
	int GetBarrierHp();

	void Update_All();
	void Draw_All();
	void All();
};