//#ifndef _GAME_H_
//#define _GAME_H_

#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "Player.h"
#include "Back.h"
#include "Enemy.h"
#include "Graze.h"
#include "Effect_Pcharge.h"
#include "Effect_Pbarrier.h"
#include "Effect_Pdead.h"
#include "Effect_Edead.h"
#include "Score.h"
#include "Item.h"
#include "Boss.h"

#include <vector>
#include <memory>
using namespace std;

struct EnemyData
{
	int type;	   //�G���
	int stype;     //�e���
	int m_pattern; //�ړ��p�^�[��
	int s_pattern; //���˃p�^�[��
	int in_time;   //�o������
	int stop_time; //��~����
	int shot_time; //�e���ˎ���
	int out_time;  //�A�Ҏ���
	int x;		   //x���W
	int y;		   //y���W
	int move_speed;//�ړ����x
	int speed;	   //�e�X�s�[�h
	int hp;		   //HP
	int power;	   //�e�̍U����
	int barrier_hp;//�o���A��HP
	int item;	   //�A�C�e��
	int sound;	   //���ˉ�
};

//�Q�[����ʃN���X
class Game : public BaseScene
{
private:
	//Game *game;
	//Enemy * temp;


	Player * player;
	Back *back;

	//Enemy *enemy[ENEMY_NUM];
	vector<Enemy*> temp;
	vector<vector<Enemy*>> enemy;
	Graze *graze;//[GRAZE_NUM];
	Effect_Pcharge *effect_pcharge;
	Effect_Pbarrier *effect_pbarrier;
	Effect_Pdead *effect_pdead;//[EFFECT_PDEADNUM];
	Effect_Edead *effect_edead;//[EFFECT_EDEADNUM];
	Score *score;
	Item *item;//[ITEM_NUM];
	Boss *boss[STAGE_NUM];

	/*
	unique_ptr<Player> player;
	unique_ptr<Back> back;
	vector<unique_ptr<Enemy>> temp;
	vector<vector<unique_ptr<Enemy>>> enemy;
	unique_ptr<Graze[]> graze;
	unique_ptr<Effect_Pcharge> effect_pcharge;
	unique_ptr<Effect_Pbarrier> effect_pbarrier;
	unique_ptr<Effect_Pdead[]> effect_pdead;
	unique_ptr<Effect_Edead[]> effect_edead;
	unique_ptr<Score> score;
	unique_ptr<Item[]> item;
	*/
	//BGM�n���h��
	int s_bgm[STAGE_NUM];

	//BGM��炷���̃t���O
	bool bgm_flag;

	//���ʉ��n���h��
	int s_pbarrier;
	int s_pbarrier_damage;
	int s_pbarrier_break;
	int s_ebarrier_damage;
	int s_ebarrier_break;
	int s_pcharge;
	int s_pcharge_max;
	int s_eshot;
	int s_pshot;
	int s_edamage;
	int s_pdamage;
	int s_edead;
	int s_pdead;
	int s_bdead;
	int s_graze;
	int s_item0;
	int s_item1;
	int s_item2;
	int s_item3;
	int s_boss_change;
	int s_clear;

	//���ʉ���炷���̃t���O
	bool pbarrier_flag;
	bool pbarrier_damage_flag;
	bool pbarrier_break_flag;
	bool ebarrier_damage_flag;
	bool ebarrier_break_flag;
	bool pcharge_flag;
	bool pcharge_stop_flag; //s_pcharge_max�̃t���O�ƕ��p
	bool eshot_flag;
	bool pshot_flag;
	bool edamage_flag;
	bool pdamage_flag;
	bool edead_flag;
	bool pdead_flag;
	bool bdead_flag;
	bool graze_flag;
	bool item0_flag;
	bool item1_flag;
	bool item2_flag;
	bool item3_flag;
	bool boss_change_flag;
	bool clear_flag;

	int count;
	int now_count;
	int stay_count;
	int graze_count;

	int now_stage;
	int sound_stoptime;

	int boss_hp[STAGE_NUM];
	bool isPause;
	bool stage_finish_flag[STAGE_NUM];
	bool game_finish_flag;
	bool game_clear_flag;

	static int g_gameover;
	static int g_gameclear;

private:
	void Init_SoundFlag();
	void SoundAll();

	bool CircleCollision( double c1, double c2, double cx1, double cx2, double cy1, double cy2 );
	void EnemyCollisionAll();
	void BossCollisionAll();

	void Init_EnemyData();
	void EnemyTracking();

public:
	Game();
	Game( ISceneChanger* changer );
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B


	void PlayerDeadEffect( double x, double y );
	void EnemyDeadEffect( double x, double y );

	void GetPlayerPosition( double *x, double *y );
	bool GetEnemyPosition( int index, double *x, double *y );

};

//#endif // !_GAME_H_