#include "Game.h"
#include "define.h"
#include "Keyboard.h"
#include "DxLib.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <crtdbg.h>

//#pragma warning(disable: 4996)

#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

int Game::g_gameover = 0;
int Game::g_gameclear = 0;

Game::Game() : BaseScene()
{
}

Game::Game( ISceneChanger* changer ) : BaseScene( changer )
{
}

//������
void Game::Initialize()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//PlayMusic( "../sounds/Stage01.mp3", DX_PLAYTYPE_LOOP );
	//SetDrawArea( MARGIN, MARGIN, MARGIN + 380, MARGIN + 460 );
	srand( (unsigned int)time( NULL ) );

	if (g_gameover == 0)
	{
		g_gameover = LoadGraph( "../images/GameOver.png" );
		g_gameclear = LoadGraph( "../images/GameClear.png" );
	}

	count = 0;
	now_count = 0;
	stay_count = 0;

	player = new Player;
	back = new Back;
	score = new Score;
	effect_pbarrier = new Effect_Pbarrier;
	effect_pcharge = new Effect_Pcharge;

	graze = new Graze[GRAZE_NUM];
	effect_pdead = new Effect_Pdead[EFFECT_PDEADNUM];
	effect_edead = new Effect_Edead[EFFECT_EDEADNUM];
	item = new Item[ITEM_NUM];

	for (int i = 0; i < STAGE_NUM; i++)
	{
		boss[i] = new Boss( i + 1 );

		stage_finish_flag[i] = false;
		/*
		if (i == 0) boss_hp[i] = BOSS1_HP;
		if (i == 1) boss_hp[i] = BOSS2_HP;
		if (i == 2) boss_hp[i] = BOSS3_HP;
		*/
		boss_hp[i] = boss[i]->GetHp();
	}
	/*
	player.reset( new Player );
	back.reset( new Back );
	score.reset( new Score );
	effect_pbarrier.reset( new Effect_Pbarrier );
	effect_pcharge.reset( new Effect_Pcharge );
	graze.reset( new Graze[GRAZE_NUM] );
	effect_pdead.reset( new Effect_Pdead[EFFECT_PDEADNUM] );
	effect_edead.reset( new Effect_Edead[EFFECT_EDEADNUM] );
	item.reset( new Item[ITEM_NUM] );
	*/

	/*
	for (int i = 0; i < GRAZE_NUM; i++)
	{
		graze[i] = new Graze;
	}

	for (int i = 0; i < EFFECT_PDEADNUM; i++)
	{
		effect_pdead[i] = new Effect_Pdead;
	}

	for (int i = 0; i < EFFECT_EDEADNUM; i++)
	{
		effect_edead[i] = new Effect_Edead;
	}

	for (int i = 0; i < ITEM_NUM; i++)
	{
		item[i] = new Item;
	}
	*/

	//�G�f�[�^�̍쐬
	Init_EnemyData();


	/*
	for (int i = 0; i < temp_enemy_data.size(); i++)
	{
		enemy.push_back( temp_enemy_data[i] );
	}
	*/

	/*
start:
	FILE * fp;
	//EnemyData data[ENEMY_NUM];
	std::vector<EnemyData> data;
	EnemyData temp_data;
	char buf[100];
	int c = 0;
	int col = 1;
	int row = 0;

	memset( buf, 0, sizeof( buf ) );
	fopen_s( &fp, "../datas/enemydata.csv", "r" );

	if (fp != NULL)
	{
		//�w�b�_�ǂݔ�΂�
		while (fgetc( fp ) != '\n');

		while (1)
		{
			while (1)
			{

				c = fgetc( fp );

				//�����Ȃ烋�[�v�𔲂���B
				if (c == EOF) //|| row >= ENEMY_NUM)
					goto out;

				//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
				if (c != ',' && c != '\n')
					//strcat(buf, (const char*)&c);
					strcat_s( buf, 100, (const char*)&c );
				//�J���}�����s�Ȃ烋�[�v������B
				else
					break;
			}
			//�����ɗ����Ƃ������Ƃ́A1�Z�����̕����񂪏o���オ�����Ƃ�������
			switch (col)
			{
				//1��ڂ͓G��ނ�\���Batoi�֐��Ő��l�Ƃ��đ���B
				case 1: temp_data.type = atoi( buf ); break;
				case 2: temp_data.stype = atoi( buf ); break;
				case 3: temp_data.m_pattern = atoi( buf ); break;
				case 4: temp_data.s_pattern = atoi( buf ); break;
				case 5: temp_data.in_time = atoi( buf ); break;
				case 6: temp_data.stop_time = atoi( buf ); break;
				case 7: temp_data.shot_time = atoi( buf ); break;
				case 8: temp_data.out_time = atoi( buf ); break;
				case 9: temp_data.x = atoi( buf ); break;
				case 10: temp_data.y = atoi( buf ); break;
				case 11: temp_data.speed = atoi( buf ); break;
				case 12: temp_data.hp = atoi( buf ); break;
				case 13: temp_data.item = atoi( buf ); break;
				case 14: temp_data.sound = atoi( buf ); break;
			}
			//�o�b�t�@��������
			memset( buf, 0, sizeof( buf ) );
			//�񐔂𑫂�
			++col;

			//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
			if (c == '\n')
			{
				col = 1;
				++row;
				data.push_back( temp_data );
			}
		}
	out:

		//�G�N���X����
		for (int i = 0; i < data.size(); ++i)
		{
			enemy.push_back( new Enemy( data[i].type, data[i].stype, data[i].m_pattern, data[i].s_pattern, data[i].in_time, data[i].stop_time, data[i].shot_time,
										data[i].out_time, data[i].x, data[i].y, data[i].speed, data[i].hp, data[i].item, data[i].sound ) );
		}

		if (fp != NULL) fclose( fp );
	}
	else
	{
		goto start;
	}
	*/
				/*
				case 1: data[row].type = atoi( buf ); break;
				case 2: data[row].stype = atoi( buf ); break;
				case 3: data[row].m_pattern = atoi( buf ); break;
				case 4: data[row].s_pattern = atoi( buf ); break;
				case 5: data[row].in_time = atoi( buf ); break;
				case 6: data[row].stop_time = atoi( buf ); break;
				case 7: data[row].shot_time = atoi( buf ); break;
				case 8: data[row].out_time = atoi( buf ); break;
				case 9: data[row].x = atoi( buf ); break;
				case 10: data[row].y = atoi( buf ); break;
				case 11: data[row].speed = atoi( buf ); break;
				case 12: data[row].hp = atoi( buf ); break;
				case 13: data[row].item = atoi( buf ); break;
				case 14: data[row].sound = atoi( buf ); break;
				*/

	//BGM�t�@�C���ǂݍ���
	s_bgm[0] = LoadSoundMem( "../sounds/Stage01_BGM.mp3" );
	s_bgm[1] = LoadSoundMem( "../sounds/Stage02_BGM.mp3" );
	s_bgm[2] = LoadSoundMem( "../sounds/Stage03_BGM.mp3" );

	//���ʉ��t�@�C���ǂݍ���
	s_pbarrier = LoadSoundMem( "../sounds/player-barrier01.mp3" );
	s_pbarrier_damage = LoadSoundMem( "../sounds/player-barrier-damage01.wav" );
	s_pbarrier_break = LoadSoundMem( "../sounds/player-barrier-break01.mp3" );
	s_ebarrier_damage = LoadSoundMem( "../sounds/player-barrier-damage01.wav" );
	s_ebarrier_break = LoadSoundMem( "../sounds/player-barrier-break01.mp3" );
	s_pcharge = LoadSoundMem( "../sounds/charge.mp3" );
	s_pcharge_max = LoadSoundMem( "../sounds/charge-max01.mp3" );
	//s_eshot = LoadSoundMem("../sounds/beam-gun01.mp3");
	s_pshot = LoadSoundMem( "../sounds/beam-gun03.mp3" );
	s_edamage = LoadSoundMem( "../sounds/enemy-damage01.mp3" );
	s_pdamage = LoadSoundMem( "../sounds/player-damage01.mp3" );
	s_edead = LoadSoundMem( "../sounds/enemy-dead01.mp3" );
	s_pdead = LoadSoundMem( "../sounds/player-dead01.mp3" );
	s_bdead = LoadSoundMem( "../sounds/boss-dead01.mp3" );
	s_graze = LoadSoundMem( "../sounds/graze02.mp3" );
	s_item0 = LoadSoundMem( "../sounds/item00.mp3" );
	s_item1 = LoadSoundMem( "../sounds/item01.mp3" );
	s_item2 = LoadSoundMem( "../sounds/item02.mp3" );
	s_item3 = LoadSoundMem( "../sounds/item03.mp3" );
	s_boss_change = LoadSoundMem( "../sounds/bosschange01.mp3" );
	s_clear = LoadSoundMem( "../sounds/gameclear01.mp3" );
	//eshot_flag = false;
	//pshot_flag = false;
	//edead_flag = false;
	//pdead_flag = false;

	isPause = false;
	game_finish_flag = false;
	game_clear_flag = false;
	now_stage = 0;
	sound_stoptime = 0;

}

//�X�V
void Game::Update()
{
	if (Keyboard_Get( KEY_INPUT_ESCAPE ) == 1)
	{
		isPause = !isPause;
		sound_stoptime = GetCurrentPositionSoundMem( s_bgm[now_stage] );
		//bgm_flag = !bgm_flag;
		if (isPause)
		{
			StopSoundMem( s_bgm[now_stage] );

			//bgm_flag = !bgm_flag;
			//mSceneChanger->ChangeScene( eScene_Pause );//�V�[�������j���[�ɕύX
		}
		else
		{
			PlaySoundMem( s_bgm[now_stage], DX_PLAYTYPE_BACK );
			SetCurrentPositionSoundMem( sound_stoptime, s_bgm[now_stage] );
		}


	}

	if (Keyboard_Get( KEY_INPUT_M ) == 1)
	{
		StopSoundMem( s_bgm[now_stage] );
		mSceneChanger->ChangeScene( eScene_Pause );
	}

	if (!isPause)
	{

		Init_SoundFlag();
		//EnemyCollisionAll();

		//�w�i
		back->Update_All();

		//�G
		if (!boss[now_stage]->GetFlag())
		{
			EnemyCollisionAll();

			for (int i = 0; i < enemy[now_stage].size(); i++)
			{
				if (enemy[now_stage][i] != NULL)
				{
					enemy[now_stage][i]->p_x = player->x;
					enemy[now_stage][i]->p_y = player->y;
					enemy[now_stage][i]->Update_All( count );

					//�G�V���b�g�T�E���h�t���O�`�F�b�N
					if (enemy[now_stage][i]->isPlaySound())
					{
						eshot_flag = true;
						s_eshot = enemy[now_stage][i]->GetPlaySound();
					}
				}
			}
		}

		//�v���C���[
		player->Update_All();

		//�v���[���[�̃`���[�W�ʒu
		//if (!player->GetDeadFlag())
		//{
		/*
		effect_pcharge->x = player->x;
		effect_pcharge->y = player->y;
		effect_pcharge->max_charge = player->Get_Status( RAPIDFIRE );
		effect_pcharge->Update_All();
		*/
	//}

	//�v���C���[�̃z�[�~���O�ʒu
		EnemyTracking();


		//�v���[���[�o���A�ʒu
		if (player->GetStatus( GRAZE ) % BARRIER_OPEN_NUM == 0 && player->GetStatus( GRAZE ) != 0)
		{
			if (!effect_pbarrier->GetBarrierFlag())
			{
				pbarrier_flag = true;
				player->SetDamageFlag( 0 );
				//effect_pbarrier->SetBarrierFlag( true );
				//if (effect_pbarrier->GetBarrierHp() <= 0)
				if (player->GetStatus( GRAZE ) > GRAZE_LINIT - BARRIER_OPEN_NUM)
				{
					//effect_pbarrier->Add_BarrierHp( BARRIER_HP_2 );
					effect_pbarrier->SetBarrierFlag( BARRIER_HP_2 );

				}
				else
				{
					//effect_pbarrier->Add_BarrierHp( BARRIER_HP_1 );
					effect_pbarrier->SetBarrierFlag( BARRIER_HP_1 );
				}
			}
		}
		effect_pbarrier->x = player->x;
		effect_pbarrier->y = player->y;
		effect_pbarrier->Update_All();

		//�v���C���[���ŃG�t�F�N�g�ʒu
		for (int i = 0; i < EFFECT_PDEADNUM; ++i)
		{
			effect_pdead[i].Update_All();
		}


		//�G���ŃG�t�F�N�g
		for (int i = 0; i < EFFECT_EDEADNUM; ++i)
		{
			effect_edead[i].Update_All();
		}

		//�O���C�Y
		for (int i = 0; i < GRAZE_NUM; ++i)
		{
			graze[i].Update_All();
		}

		//�A�C�e��
		for (int i = 0; i < ITEM_NUM; ++i)
		{
			item[i].Update_All();
		}

		//�X�e�[�W���N���A������
		for (int i = 0; i < enemy[now_stage].size(); i++)
		{
			if (enemy[now_stage][i] != NULL)
			{
				if (!enemy[now_stage][i]->GetDeadFlag())
				{
					stage_finish_flag[now_stage] = false;
					break;
				}
				else
				{
					stage_finish_flag[now_stage] = true;
				}
			}
		}

		if (stage_finish_flag[now_stage])
		{
			stay_count++;
			if (stay_count >= 200)
			{
				boss[now_stage]->SetFlag( true );
				if (boss[now_stage]->GetFlag())
				{
					boss[now_stage]->p_x = player->x;
					boss[now_stage]->p_y = player->y;
					BossCollisionAll();
					boss[now_stage]->Update_All();
				}
			}
		}
		else
		{
			stay_count = 0;
		}


		//�v���[���[�̃V���b�g��
		if (player->isPlayShotSound())
		{
			pshot_flag = true;
		}

		//�v���[���[�̃`���[�W��
		if (player->isPlayChargeSound())
		{
			pcharge_flag = true;
		}

		//�v���[���[�̃`���[�W������
		if (player->isPlayChargeStopSound())
		{
			pcharge_stop_flag = true;
		}

		if (!game_finish_flag)// || !game_clear_flag)
		{
			int time = 0;
			time = GetSoundTotalTime( s_bgm[now_stage] );
			int sound_time = 0;
			sound_time = time / 1000 * 60 + 30;
			if (count % sound_time == 0)
			{
				bgm_flag = true;
			}
		}
		else
		{

			now_count++;
		}

		if (game_clear_flag)
		{
			StopSoundMem( s_bgm[now_stage] );
			now_count++;
		}

		//�Q�[���N���X�̑��t���[����
		++count;

	}
}

//�`��E��
void Game::Draw()
{
	SetDrawArea( MARGIN, MARGIN, MARGIN + 380, MARGIN + 460 );


	//BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�(�w�i�ύX)
	//DrawString( 0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor( 255, 255, 255 ) );


	//�w�i�`��
	back->Draw_All();

	//�G�`��
	for (int i = 0; i < enemy[now_stage].size(); i++)
	{
		if (enemy[now_stage][i] != NULL)
		{
			if (enemy[now_stage][i]->Draw_All())
			{
				//delete enemy[now_stage][i];
				enemy[now_stage][i] = NULL;
			}
		}
	}


	//�v���[���[�̃`���[�W�`��
	if (!player->GetDeadFlag())
	{
		effect_pcharge->x = player->x;
		effect_pcharge->y = player->y;
		effect_pcharge->max_charge = player->GetStatus( RAPIDFIRE );
		effect_pcharge->All(); //Move()�𕪗�����Ƃ����
	}
	//�v���C���[�`��
	player->Draw_All();

	//�v���C���[�o���A�`��
	effect_pbarrier->Draw_All();

	//�v���C���[���ŃG�t�F�N�g�`��
	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		effect_pdead[i].Draw_All();
	}


	//�G���ŃG�t�F�N�g�`��
	for (int i = 0; i < EFFECT_EDEADNUM; ++i)
	{
		effect_edead[i].Draw_All();
	}

	//�O���C�Y�`��
	for (int i = 0; i < GRAZE_NUM; ++i)
	{
		graze[i].Draw_All();
	}

	//�A�C�e���`��
	for (int i = 0; i < ITEM_NUM; ++i)
	{
		item[i].Draw_All();
	}

	//�{�X�`��
	if (stage_finish_flag[now_stage])
	{
		boss[now_stage]->Draw_All();
	}

	//�Q�[���I�[�o�[��ʕ`��
	if (player->GetStatus( STOCK ) <= 0)
	{
		DrawGraph( 50, 190, g_gameover, TRUE );
		game_finish_flag = true;

		if (now_count == 300)
		{
			StopSoundMem( s_bgm[now_stage] );
			mSceneChanger->ChangeScene( eScene_Menu );
			//Init_SoundFlag();
		}
		//now_count++;

	}

	if (game_clear_flag)
	{
		DrawGraph( 50, 190, g_gameclear, TRUE );
		if (now_count == 300)
		{
			StopSoundMem( s_bgm[now_stage] );
			mSceneChanger->ChangeScene( eScene_Menu );
			//Init_SoundFlag();
		}
	}


	//�X�R�A�`��
	SetDrawArea( 0, 0, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT );
	score->All();

	//�T�E���h�I��
	SoundAll();
}

void Game::Finalize()
{
	//delete temp;
	//temp = nullptr;

	//vector<Enemy*>().swap( temp_enemy_data );
	//delete temp;
	//temp = nullptr;


	vector<Enemy*>().swap( temp );

	delete player;
	player = nullptr;
	delete back;
	back = nullptr;
	delete score;
	score = nullptr;
	delete effect_pbarrier;
	effect_pbarrier = nullptr;
	//delete effect_ebarrier;
	delete effect_pcharge;
	effect_pcharge = nullptr;

	for (int i = 0; i < STAGE_NUM; i++)
	{
		delete boss[i];
	}


	/*
	for (int i = 0; i < enemy.size(); i++)
	{
		for (int j = 0; j < enemy[i].size(); j++)
		{
			if (enemy[i][j] != NULL) delete enemy[i][i];
		}
	}*/

	vector<vector<Enemy*>>().swap( enemy );

	/*
	for (int i = 0; i < GRAZE_NUM; i++)
	{
		delete graze[i];
	}

	for (int i = 0; i < EFFECT_PDEADNUM; i++)
	{
		delete effect_pdead[i];
	}

	for (int i = 0; i < EFFECT_EDEADNUM; i++)
	{
		delete effect_edead[i];
	}

	for (int i = 0; i < ITEM_NUM; i++)
	{
		delete item[i];
	}
	*/


	delete[] graze;
	graze = nullptr;
	delete[] effect_pdead;
	effect_pdead = nullptr;
	delete[] effect_edead;
	effect_edead = nullptr;
	delete[] item;
	item = nullptr;

}

void Game::GetPlayerPosition( double *x, double *y )
{

	double temp_x, temp_y;

	player->GetPosition( &temp_x, &temp_y );

	*x = temp_x;
	*y = temp_y;
}

bool Game::GetEnemyPosition( int index, double *x, double *y )
{
	double temp_x, temp_y;

	if (enemy[now_stage][index] == NULL || enemy[now_stage][index]->GetDeadFlag()) return false;

	//�w�肵���Y���̓G�̍��W���擾
	enemy[now_stage][index]->GetPosition( &temp_x, &temp_y );

	*x = temp_x;
	*y = temp_y;

	return true;
}

void Game::PlayerDeadEffect( double x, double y )
{
	for (int z = 0; z < EFFECT_PDEADNUM; ++z)
	{
		if (!effect_pdead[z].GetFlag())
		{
			effect_pdead[z].SetFlag( x, y );
			break;
		}
	}
}

void Game::EnemyDeadEffect( double x, double y )
{
	//�G�t�F�N�g�Z�b�g
	for (int z = 0; z < EFFECT_EDEADNUM; ++z)
	{
		if (!effect_edead[z].GetFlag())
		{
			effect_edead[z].SetFlag( x, y );
			break;
		}
	}
}

void Game::Init_EnemyData()
{
	vector<Enemy*> temp_enemy_data;
	//vector<unique_ptr<Enemy>> temp_enemy_data;

	for (int stageNum = 0; stageNum < STAGE_NUM; stageNum++)
	{
		vector<EnemyData> data;

		for (int waveNum = 0; waveNum < WAVE_NUM; waveNum++)
		{
			bool ballShootingFlag = false;
			int wave_enemy;

			//�E�F�[�u�̐i�݋�ɂ����1�E�F�[�u�̓G�̐������߂�
			if (waveNum < WAVE_NUM / 5)
			{
				//wave_enemy = rand() % 2 + 2; //2 �` 3
				wave_enemy = 3 + stageNum; //2 �` 4
			}
			else if (waveNum < (WAVE_NUM / 5) * 2)
			{
				//wave_enemy = rand() % 3 + 2; //2 �` 4
				wave_enemy = rand() % 3 + 3 + stageNum; //4 �` 6
			}
			else if (waveNum < (WAVE_NUM / 5) * 3)
			{
				//wave_enemy = rand() % 3 + 3; //3 �` 5
				wave_enemy = rand() % 2 + 4 + stageNum; //5 �` 6
			}
			else if (waveNum < (WAVE_NUM / 5) * 4)
			{
				//wave_enemy = rand() % 4 + 4; //4 �` 7
				wave_enemy = rand() % 3 + 4 + stageNum; //5 �` 7
			}
			else
			{
				//wave_enemy = 10;
				wave_enemy = rand() % 2 + 6 + stageNum; //7 �` 8
			}

			//1�E�F�[�u�ɏo������G1��1�̂�ݒ�
			for (int z = 0; z < wave_enemy; z++)
			{
				EnemyData temp_data;

				int wave_between = 220; //���̃E�F�[�u�ɐi�ނ܂ł̃t���[����

				temp_data.type = rand() % (stageNum + 1);

				//�E�F�[�u�̐i�݋�ɉ������u�G�̃^�C�v�v�u�o���A�̗L���v�u�o���A��HP�v�u�A�C�e���̃h���b�v���v
				if (waveNum < WAVE_NUM / 4)
				{
					/*
					temp_data.type = ENEMY_0; //0 �` 1
					temp_data.barrier_hp = 0;

					int item = rand() % 10;
					if (item < 1) temp_data.item = ITEM_SCOREUP;
					else if (item < 6) temp_data.item = ITEM_POWERUP;
					else if (item < 9) temp_data.item = ITEM_SPEEDUP;
					else if (item < 10) temp_data.item = ITEM_LIFEUP;
					*/
					temp_data.barrier_hp = 0;

				}
				else if (waveNum < WAVE_NUM / 2)
				{
					/*
					temp_data.type = rand() % 2; //0 �` 1
					temp_data.barrier_hp = 0;

					int item = rand() % 10;
					if (item < 2) temp_data.item = ITEM_SCOREUP;
					else if (item < 6) temp_data.item = ITEM_POWERUP;
					else if (item < 8) temp_data.item = ITEM_SPEEDUP;
					else if (item < 10) temp_data.item = ITEM_LIFEUP;
					*/
					temp_data.barrier_hp = 0;


				}
				else if (waveNum < (WAVE_NUM / 4) * 3)
				{
					/*
					temp_data.type = rand() % 3; //0 �` 2
					int check = rand() % 5;
					if (check == 0) temp_data.barrier_hp = rand() % 3 + 1; //1 �` 3
					else temp_data.barrier_hp = 0;

					int item = rand() % 10;
					if (item < 3) temp_data.item = ITEM_SCOREUP;
					else if (item < 5) temp_data.item = ITEM_POWERUP;
					else if (item < 7) temp_data.item = ITEM_SPEEDUP;
					else if (item < 10) temp_data.item = ITEM_LIFEUP;
					*/

					int check = rand() % (stageNum + 1);
					if (check == 1) temp_data.barrier_hp = rand() % 3 + 1; //1 �` 3
					else temp_data.barrier_hp = 0;

				}
				else
				{
					/*
					temp_data.type = rand() % 2 + 1; //1 �` 2
					int check = rand() % 3;
					if (check == 0) temp_data.barrier_hp = rand() % 2 + 4; //4 �` 5
					else temp_data.barrier_hp = 0;

					int item = rand() % 10;
					if (item < 4) temp_data.item = ITEM_SCOREUP;
					else if (item < 5) temp_data.item = ITEM_POWERUP;
					else if (item < 6) temp_data.item = ITEM_SPEEDUP;
					else if (item < 10) temp_data.item = ITEM_LIFEUP;
					*/
					int check = rand() % (stageNum + 1);
					if (check == 2) temp_data.barrier_hp = rand() % 2 + 4; //4 �` 5
					else temp_data.barrier_hp = 0;
				}

				//�G�̎�ނɂ���ČŒ肳���u�ړ��X�s�[�h�v�u�e�̃X�s�[�h�v�uHP�v�u�e�̍U���́v��ύX
				switch (temp_data.type)
				{
					/*varsion0.8*/
					/*
					case ENEMY_0:
						temp_data.move_speed = 2;
						temp_data.speed = 3;
						temp_data.hp = 1 * (stageNum + 1);
						temp_data.power = 1 * (stageNum + 1);
						break;

					case ENEMY_1:
						temp_data.move_speed = rand() % 2 + 2; //2 �` 3
						temp_data.speed = rand() % 2 + 3; //3 �` 4
						temp_data.hp = 5 * (stageNum + 1);
						temp_data.power = 2 * (stageNum + 1);
						break;

					case ENEMY_2:
						temp_data.move_speed = rand() % 2 + 3; //3 �` 4
						temp_data.speed = rand() % 3 + 4; //4 �` 6
						temp_data.hp = 15 * (stageNum + 1);
						temp_data.power = 3 * (stageNum + 1);
						break;

					default:
						break;
					*/
					case ENEMY_0:
						temp_data.move_speed = 2;
						temp_data.shot_speed = 3;
						temp_data.hp = 1;
						temp_data.power = 1;
						break;

					case ENEMY_1:
						temp_data.move_speed = 3;
						temp_data.shot_speed = 4;
						temp_data.hp = 3;
						temp_data.power = 2;
						break;

					case ENEMY_2:
						temp_data.move_speed = 4;
						temp_data.shot_speed = 5;
						temp_data.hp = 5;
						temp_data.power = 3;
						break;

					default:
						break;

				}

				//1wave�ɗ��˃^�C�v�̓G�͈�̂܂�(�����͈ړ�����)�ɐ���
				do
				{
					temp_data.stype = rand() % BALL_TYPE_NUM;
				} while (ballShootingFlag == true && temp_data.stype == BALL_SHOOTING);

				//�e�̎�ނɂ���ČŒ肳���u���˃p�^�[���v�u�T�E���h�v�u�ړ��p�^�[���v������
				switch (temp_data.stype)
				{
					case BALL_LINE:
						temp_data.s_pattern = 0;
						temp_data.sound = 0;
						temp_data.m_pattern = rand() % BOSS_MOVE_TYPE_NUM;
						break;

					case BALL_RAPIDFIRE:
						temp_data.s_pattern = rand() % 2 + 1; //1 �` 2
						if (temp_data.s_pattern == SHOT_HOMING_LINE1) temp_data.sound = SOUND_HOMING_LINE1;
						if (temp_data.s_pattern == SHOT_HOMING_LINE3) temp_data.sound = SOUND_HOMING_LINE3;
						temp_data.m_pattern = rand() % BOSS_MOVE_TYPE_NUM;
						break;

					case BALL_SHOOTING:
						temp_data.s_pattern = SHOT_HOMING_SHOOTING;
						temp_data.sound = SOUND_HOMING_SHOOTING;
						temp_data.m_pattern = MOVE_LINEDOWN;
						ballShootingFlag = true;
						break;

					default:
						break;
				}

				//temp_data.m_pattern = rand() % M_PATTEAN_NUM;
				temp_data.in_time = wave_between * waveNum + 60;
				temp_data.stop_time = temp_data.in_time + 60;
				temp_data.shot_time = temp_data.stop_time + 1;
				temp_data.out_time = temp_data.shot_time + 80;

				/*
				switch (wave_enemy)
				{
				case 1:
				temp_data.x = rand() % 280 + 60;
				break;

				case 2:
				temp_data.x = rand() % 280 + 60;
				break;

				case 3:
				temp_data.x = rand() % 280 + 60;
				break;

				case 4:
				temp_data.x = rand() % 280 + 60;
				break;

				case 5:
				temp_data.x = rand() % 280 + 60;
				break;

				default:
				break;
				}
				*/

				temp_data.x = rand() % 280 + 60;
				temp_data.y = -40;

				/*
				0:�X�R�A�v���X
				1:�p���[�A�b�v
				2:�X�s�[�h�A�b�v
				3:HP��
				*/

				int itemRand = rand() % 10;
				if (stageNum == 0)
				{
					if (itemRand < 2) temp_data.item = ITEM_SCOREUP;
					else if (itemRand < 5) temp_data.item = ITEM_POWERUP;
					else if (itemRand < 7) temp_data.item = ITEM_SPEEDUP;
					else if (itemRand < 10) temp_data.item = ITEM_LIFEUP;
				}
				if (stageNum == 1)
				{
					if (itemRand < 3) temp_data.item = ITEM_SCOREUP;
					else if (itemRand < 5) temp_data.item = ITEM_POWERUP;
					else if (itemRand < 7) temp_data.item = ITEM_SPEEDUP;
					else if (itemRand < 10) temp_data.item = ITEM_LIFEUP;
				}
				if (stageNum == 2)
				{
					if (itemRand < 5) temp_data.item = ITEM_SCOREUP;
					else if (itemRand < 6) temp_data.item = ITEM_POWERUP;
					else if (itemRand < 7) temp_data.item = ITEM_SPEEDUP;
					else if (itemRand < 10) temp_data.item = ITEM_LIFEUP;
				}
				else
				{
					temp_data.item = rand() % ITEM_TYPE_NUM;
				}

				//temp_data.item = 1;
				/*
				int random = rand() % 2;
				if (random == 0) temp_data.barrier_flag = true;
				else temp_data.barrier_flag = false;
				*/

				data.push_back( temp_data );
			}
		}

		//�G�N���X����
		//Enemy temp_enemy_data;
		//Enemy *temp;
		for (int i = 0; i < data.size(); i++)
		{
			/*
			temp.push_back( move( make_unique<Enemy>( new Enemy( data[i].type, data[i].stype, data[i].m_pattern, data[i].s_pattern, data[i].in_time, data[i].stop_time, data[i].shot_time,
																 data[i].out_time, data[i].x, data[i].y, data[i].move_speed, data[i].speed, data[i].hp, data[i].power, data[i].barrier_hp, data[i].item, data[i].sound ) ) ) );
			temp_enemy_data.push_back( temp[i] );
			*/
			/*
			temp_enemy_data.push_back( move( make_unique<Enemy>( new Enemy( data[i].type, data[i].stype, data[i].m_pattern, data[i].s_pattern, data[i].in_time, data[i].stop_time, data[i].shot_time,
																			data[i].out_time, data[i].x, data[i].y, data[i].move_speed, data[i].speed, data[i].hp, data[i].power, data[i].barrier_hp, data[i].item, data[i].sound ) ) ) );
			*/
			/*
			Enemy *temp;
			temp = new Enemy( data[i].type, data[i].stype, data[i].m_pattern, data[i].s_pattern, data[i].in_time, data[i].stop_time, data[i].shot_time,
							  data[i].out_time, data[i].x, data[i].y, data[i].move_speed, data[i].speed, data[i].hp, data[i].power, data[i].barrier_hp, data[i].item, data[i].sound );
			temp_enemy_data.push_back( temp );
			*/
			//delete temp;

			temp_enemy_data.push_back( new Enemy( data[i].type, data[i].stype, data[i].m_pattern, data[i].s_pattern, data[i].in_time, data[i].stop_time, data[i].shot_time,
												  data[i].out_time, data[i].x, data[i].y, data[i].move_speed, data[i].shot_speed, data[i].hp, data[i].power, data[i].barrier_hp, data[i].item, data[i].sound ) );

					   //delete temp[i];
					   //*temp++;
					   //temp[i] = nullptr;
					   //enemy.push_back( temp_enemy_data );
		}
		data.clear();
		enemy.push_back( temp_enemy_data );
		//vector<Enemy*>().swap( temp_enemy_data );
		/*
		for (int i = 0; i < temp_enemy_data.size(); i++)
		{
			delete temp_enemy_data[i];
		}
		*/
	}
	//vector<Enemy*>().swap( temp_enemy_data );
	//delete temp;
	//temp = nullptr;
}

void Game::EnemyTracking()
{
	int nearindex = -1;
	double nearresult = 0;
	double ex, ey, tx, ty;
	for (int i = 0; i < enemy[now_stage].size(); i++)
	{
		if (enemy[now_stage][i] != NULL && !enemy[now_stage][i]->GetDeadFlag())
		{
			tx = enemy[now_stage][i]->x - player->x;
			ty = enemy[now_stage][i]->y - player->y;
			if (nearindex == -1)
			{
				nearindex = i;
				nearresult = tx * tx + ty * ty;
				continue;
			}
			if (nearresult > tx * tx + ty * ty)
			{
				nearindex = i;
				nearresult = tx * tx + ty * ty;
			}

		}
	}
	player->nearindex = nearindex;

	if (nearindex >= 0)
	{
		player->e_x = enemy[now_stage][nearindex]->x;
		player->e_y = enemy[now_stage][nearindex]->y;
	}
	player->boss_flag = boss[now_stage]->GetFlag();
	player->b_x = boss[now_stage]->x;
	player->b_y = boss[now_stage]->y;
}
/// <summary>
/// �~�`��p�̓����蔻��֐�
/// </summary>
/// <param name="c1">�~�`�P�̔��a</param>
/// <param name="c2">�~�`�Q�̔��a</param>
/// <param name="cx1">�~�`�P�� x���W</param>
/// <param name="cx2">�~�`�Q�� x���W</param>
/// <param name="cy1">�~�`�P�� y���W</param>
/// <param name="cy2">�~�`�Q�� y���W</param>
/// <returns></returns>
bool Game::CircleCollision( double c1, double c2, double cx1, double cx2, double cy1, double cy2 )
{
	double hlength = c1 + c2; //2�̉~�̔��a�̍��v
	double xlength = cx1 - cx2; //2�̉~��x���ł̋���
	double ylength = cy1 - cy2; //2�̉~��y���ł̋���

	if (hlength * hlength >= xlength * xlength + ylength * ylength)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::EnemyCollisionAll()
{
	double px, py, psx, psy, ex, ey;

	bool tempflag = false;
	bool gtempflag = false;

	//����L�����̒e�ƓG�Ƃ̓����蔻��
	for (int i = 0; i < PSHOT_NUM; ++i)
	{
		if (player->GetShotPosition( i, &psx, &psy ))
		{
			for (int s = 0; s < enemy[now_stage].size(); ++s)
			{
				//�G�N���X�̃|�C���^��NULL����Ȃ��A����deadflag��false(����łȂ����A�҂��ĂȂ�)
				if (enemy[now_stage][s] != NULL && !enemy[now_stage][s]->GetDeadFlag())
				{
					enemy[now_stage][s]->GetPosition( &ex, &ey );
					//�����蔻��
					if (CircleCollision( PSHOT_COLLISION, ENEMY1_COLLISION, psx, ex, psy, ey ))
					{
						//�������Ă���΁Adeadflag�𗧂Ă�
						//enemy[s]->SetDeadFlag();

						if (!enemy[now_stage][s]->GetBarrierFlag())
						{
							//�������Ă���΁A�G��HP�����炷�iHP��0�ɂȂ��deadflag�����j
							enemy[now_stage][s]->SetHp( -1 );
							//���������e�̃t���O��߂�
							player->SetShotFlag( i, false );

							//�G�����񂾎�
							if (enemy[now_stage][s]->GetDeadFlag())
							{
								//�G���ŉ��t���O�Z�b�g
								edead_flag = true;
								//�G���ŃG�t�F�N�g�Z�b�g
								EnemyDeadEffect( ex, ey );
								//���_��������
								score->SetScore( CURRENT_SCORE, 100 );

								//�A�C�e���o��
								for (int i = 0; i < ITEM_TYPE_NUM; i++)
								{
									if (!item[i].GetFlag())
									{
										if ((rand() % 10) >= 5)
										{
											//item[i]->SetFlag( ex, ey, enemy[s]->GetItemType() );
											switch (enemy[now_stage][s]->GetItemType())
											{
												//�X�R�A����
												case ITEM_SCOREUP:
													item[i].SetFlag( ex, ey, ITEM_SCOREUP );
													break;

												//�p���[�A�b�v
												case ITEM_POWERUP:
													item[i].SetFlag( ex, ey, ITEM_POWERUP );
													break;

												//�X�s�[�h�A�b�v
												case ITEM_SPEEDUP:
													item[i].SetFlag( ex, ey, ITEM_SPEEDUP );
													break;

												//HP��
												case ITEM_LIFEUP:
													item[i].SetFlag( ex, ey, ITEM_LIFEUP );
													break;

												default:
													break;
											}
										}
										break;
									}
								}
							}
							else
							{
								edamage_flag = true;
							}
						}
						else
						{
							enemy[now_stage][s]->Add_BarrierHp( -1 );
							player->SetShotFlag( i, false );
							if (enemy[now_stage][s]->GetBarrierHp() <= 0)
							{
								ebarrier_break_flag = true;
							}
							else
							{
								ebarrier_damage_flag = true;
							}
						}
					}
				}
			}
		}
	}

	//�G�Ƒ���L�����Ƃ̓����蔻��
	//�v���C���[���u�����Ă��āv�u�_���[�W���󂯂Ă��炸�v�u�o���A���Ƀ_���[�W���󂯂Ă��Ȃ��v
	if (!player->GetDeadFlag() && !player->GetDamageFlag() && !player->GetDamageZeroFlag())
	{
		player->GetPosition( &px, &py );
		for (int i = 0; i < enemy[now_stage].size(); i++)
		{
			if (enemy[now_stage][i] != NULL && !enemy[now_stage][i]->GetDeadFlag())
			{
				enemy[now_stage][i]->GetPosition( &ex, &ey );
				if (CircleCollision( PLAYER_COLLISION, ENEMY1_COLLISION, px, ex, py, ey ))
				{
					tempflag = true;
				}

				if (tempflag)
				{
					//�o���A���W�J����Ă��Ȃ����
					if (!effect_pbarrier->GetBarrierFlag())
					{
						//����L������damageflag�𗧂Ă�
						player->SetDamageFlag( 1 );
						//�e������
						//enemy[now_stage][i]->SetShotFlag( s, false );

						if (player->GetStatus( HP ) <= 0)
						{
							//�v���C���[���ŉ��t���O�𗧂Ă�
							pdead_flag = true;

							//�v���C���[���ŃG�t�F�N�g
							PlayerDeadEffect( px, py );

							//�X�e�[�^�X����
							player->AddStatus( STOCK, -1 );
							player->AddStatus( SPEED, -3 );
							player->AddStatus( POWER, -3 );
							player->AddStatus( HP, PLAYER_LIFE );
						}
						else
						{
							pdamage_flag = true;
						}
					}
					else// if (effect_pbarrier->GetBarrierFlag())
					{
						player->SetDamageFlag( 0 );
						effect_pbarrier->Add_BarrierHp( -1/*-enemy[i]->GetShotDamage( s )*/ );
						//enemy[now_stage][i]->SetShotFlag( s, false );

						if (effect_pbarrier->GetBarrierHp() <= 0)
						{
							player->AddStatus( GRAZE, 1 );
							//effect_pbarrier->SetBarrierFlag( false );
							pbarrier_break_flag = true;
						}
						pbarrier_damage_flag = true;
					}
					//�ꎞ�t���O��߂�
					tempflag = false;
					break;
				}
			}
		}
	}

	//�G�̒e�Ƒ���L�����Ƃ̓����蔻��
	//�v���C���[���u�����Ă��āv�u�_���[�W���󂯂Ă��炸�v�u�o���A���Ƀ_���[�W���󂯂Ă��Ȃ��v
	if (!player->GetDeadFlag() && !player->GetDamageFlag() && !player->GetDamageZeroFlag())
	{
		player->GetPosition( &px, &py );
		for (int i = 0; i < enemy[now_stage].size(); ++i)
		{
			if (enemy[now_stage][i] != NULL)
			{
				for (int s = 0; s < ENEMY_SNUM; ++s)
				{

					//�e�t���O�������Ă����true��Ԃ�
					if (enemy[now_stage][i]->GetShotPosition( s, &ex, &ey ))
					{
						//�e�ɂ���ē����蔻�肪�Ⴄ�̂�switch���ŕ���
						switch (enemy[now_stage][i]->GetShotType())
						{

							case BALL_LINE:
								//�O���C�Y����
								if (CircleCollision( GRAZE_COLLISION, ESHOT0_COLLISION, px, ex, py, ey ))
								{
									if (GRAZE_COLLISION - PLAYER_COLLISION < graze_count)
									{
										gtempflag = true;
										graze_count = 0;
									}
									graze_count++;

								}
								//�ʏ�̓����蔻��
								if (CircleCollision( PLAYER_COLLISION, ESHOT0_COLLISION, px, ex, py, ey ))
								{
									tempflag = true;
									//gtempflag = false;
								}
								break;

							case BALL_RAPIDFIRE:
								if (CircleCollision( GRAZE_COLLISION, ESHOT1_COLLISION, px, ex, py, ey ))
								{
									if (GRAZE_COLLISION - PLAYER_COLLISION < graze_count)
									{
										gtempflag = true;
										graze_count = 0;
									}
									graze_count++;
								}
								if (CircleCollision( PLAYER_COLLISION, ESHOT1_COLLISION, px, ex, py, ey ))
								{
									tempflag = true;
									//gtempflag = false;
								}
								break;

							case BALL_SHOOTING:
								if (CircleCollision( GRAZE_COLLISION, ESHOT2_COLLISION, px, ex, py, ey ))
								{
									if (GRAZE_COLLISION - PLAYER_COLLISION < graze_count)
									{
										gtempflag = true;
										graze_count = 0;
									}
									graze_count++;
								}
								if (CircleCollision( PLAYER_COLLISION, ESHOT2_COLLISION, px, ex, py, ey ))
								{
									tempflag = true;
									//gtempflag = false;

								}
								break;
						}


						//�O���C�Y�����蔻��t���O��true�Ȃ�
						if (gtempflag)
						{
							if (!effect_pbarrier->GetBarrierFlag())
							{
								if (!enemy[now_stage][i]->GetGrazeFlag( s ))
								{
									enemy[now_stage][i]->SetGrazeFlag( s );
									//�O���C�Y�̃C���X�^���X����
									for (int z = 0; z < GRAZE_NUM; ++z)
									{
										if (!graze[z].GetFlag())
										{
											graze[z].SetFlag( px, py );
											break;
										}
									}
									//�O���C�Y�̓��_��������
									//score->SetScore( GRAZE_SCORE, 1 );
									score->SetScore( CURRENT_SCORE, 20 );
									player->AddStatus( GRAZE, 1 );

									//�O���C�Y���Z�b�g
									graze_flag = true;
								}

							}
							gtempflag = false;
						}

						if (tempflag)
						{
							//�o���A���W�J����Ă��Ȃ����
							if (!effect_pbarrier->GetBarrierFlag())
							{
								//����L������damageflag�𗧂Ă�
								player->SetDamageFlag( enemy[now_stage][i]->GetShotDamage( s ) );
								//�e������
								enemy[now_stage][i]->SetShotFlag( s, false );

								if (player->GetStatus( HP ) <= 0)
								{
									//�v���C���[���ŉ��t���O�𗧂Ă�
									pdead_flag = true;

									//�v���C���[���ŃG�t�F�N�g
									PlayerDeadEffect( px, py );

									//�X�e�[�^�X����
									player->AddStatus( STOCK, -1 );
									player->AddStatus( SPEED, -3 );
									player->AddStatus( POWER, -3 );
									player->AddStatus( HP, PLAYER_LIFE );
								}
								else
								{
									pdamage_flag = true;
								}
							}
							else// if (effect_pbarrier->GetBarrierFlag())
							{
								player->SetDamageFlag( 0 );
								effect_pbarrier->Add_BarrierHp( -1/*-enemy[i]->GetShotDamage( s )*/ );
								enemy[now_stage][i]->SetShotFlag( s, false );

								if (effect_pbarrier->GetBarrierHp() <= 0)
								{
									player->AddStatus( GRAZE, 1 );
									//effect_pbarrier->SetBarrierFlag( false );
									pbarrier_break_flag = true;
								}
								pbarrier_damage_flag = true;
							}
							//�ꎞ�t���O��߂�
							tempflag = false;
							break;
						}
						//break;
					}
					//break;
				}
				//break;
			}
		}

	}

	//�A�C�e���Ƒ���L�����Ƃ̓����蔻��
	//�v���C���[���u�����Ă��āv�u�_���[�W���󂯂Ă��炸�v�u�o���A���Ƀ_���[�W���󂯂Ă��Ȃ��v
	if (!player->GetDeadFlag() && !player->GetDamageFlag() || player->GetDamageZeroFlag())
	{

		double ix, iy;
		player->GetPosition( &px, &py );

		for (int i = 0; i < ITEM_NUM; ++i)
		{
			if (item[i].GetFlag())
			{
				item[i].GetPosition( &ix, &iy );
				if (CircleCollision( PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy ))
				{
					switch (item[i].GetType())
					{
						case ITEM_SCOREUP:
							score->SetScore( CURRENT_SCORE, 300 );
							item0_flag = true;
							break;

						case ITEM_POWERUP:
							player->AddStatus( POWER, 1 );
							item1_flag = true;
							break;

						case ITEM_SPEEDUP:
							player->AddStatus( SPEED, 1 );
							item2_flag = true;
							break;

						case ITEM_LIFEUP:
							player->AddStatus( HP, 1 );
							item3_flag = true;
							break;

						default:
							break;
					}
					item[i].Delete();
				}
			}
		}
	}

	score->SetScore( GRAZE_SCORE, player->GetStatus( GRAZE ) );
	score->SetScore( SPEED_SCORE, player->GetStatus( SPEED ) );
	score->SetScore( POWER_SCORE, player->GetStatus( POWER ) );
	score->SetScore( STOCK_SCORE, player->GetStatus( STOCK ) );
	score->SetScore( LIFE_SCORE, player->GetStatus( HP ) );

}

void Game::BossCollisionAll()
{
	double px, py, psx, psy, bx, by, ix, iy;

	//�o���A�C�e����
	int itemnum = 0;

	//�O���C�Y�ƃq�b�g�������̃t���O
	bool hflag = false, gflag = false;

	//�{�X�̒e�̎��
	int type;

	//�v���C���[�ƃ{�X�̓����蔻��
	if (!player->GetDeadFlag() && !player->GetDamageFlag() && !player->GetDamageZeroFlag())
	{
		player->GetPosition( &px, &py );
		boss[now_stage]->GetPosition( &bx, &by );

		if (CircleCollision( PLAYER_COLLISION, BOSS_COLLISION, px, bx, py, by ))
		{
			hflag = true;
		}

		if (hflag)
		{
			//�o���A���W�J����Ă��Ȃ����
			if (!effect_pbarrier->GetBarrierFlag())
			{
				//����L������damageflag�𗧂Ă�
				player->SetDamageFlag( 1 );
				//�e������
				//boss[now_stage]->SetShotFlag( i, false );

				if (player->GetStatus( HP ) <= 0)
				{
					//�v���C���[���ŉ��t���O�𗧂Ă�
					pdead_flag = true;

					//�v���C���[���ŃG�t�F�N�g
					PlayerDeadEffect( px, py );

					//�X�e�[�^�X����
					player->AddStatus( STOCK, -1 );
					player->AddStatus( SPEED, -3 );
					player->AddStatus( POWER, -3 );
					player->AddStatus( HP, PLAYER_LIFE );
				}
				else
				{
					pdamage_flag = true;
				}
			}
			else// if (effect_pbarrier->GetBarrierFlag())
			{
				player->SetDamageFlag( 0 );
				effect_pbarrier->Add_BarrierHp( -1/*-enemy[i]->GetShotDamage( s )*/ );
				//boss[now_stage]->SetShotFlag( i, false );

				if (effect_pbarrier->GetBarrierHp() <= 0)
				{
					player->AddStatus( GRAZE, 1 );
					//effect_pbarrier->SetBarrierFlag( false );
					pbarrier_break_flag = true;
				}
				pbarrier_damage_flag = true;
			}
			//�ꎞ�t���O��߂�
			hflag = false;
		}
	}

	//�v���C���[�̃V���b�g�ƃ{�X�̓����蔻��
	if (!boss[now_stage]->GetNodamageFlag())
	{
		for (int i = 0; i < PSHOT_NUM; ++i)
		{
			if (player->GetShotPosition( i, &psx, &psy ))
			{
				boss[now_stage]->GetPosition( &bx, &by );
				if (CircleCollision( PSHOT_COLLISION, BOSS_COLLISION, psx, bx, psy, by ))
				{
					boss[now_stage]->SetHp( -1 );
					player->SetShotFlag( i, false );
					score->SetScore( CURRENT_SCORE, 10 );
					edamage_flag = true;


					if (boss_hp[now_stage] * 2 / 3 >= boss[now_stage]->GetHp() && boss[now_stage]->GetPrevHp() > boss_hp[now_stage] * 2 / 3)
					{
						//�_���[�W�G�t�F�N�g���o��
						EnemyDeadEffect( bx, by );
						//�_���[�W����炷
						boss_change_flag = true;
						//����ɓ��_��������
						score->SetScore( CURRENT_SCORE, 1000 );
						//�A�C�e�����o���B
						for (int z = 0; z < ITEM_NUM; ++z)
						{
							if (!item[z].GetFlag())
							{
								//�A�C�e���̏������W���΂炯������B
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z].SetFlag( ix, iy, rand() % (ITEM_TYPE_NUM - 1) + 1 );
								++itemnum;
								//5�o�����烋�[�v�𔲂���
								if (itemnum == 5)
								{
									break;
								}
							}
						}
						boss[now_stage]->SetDamageSetting();
					}
					else if (boss_hp[now_stage] / 3 >= boss[now_stage]->GetHp() && boss[now_stage]->GetPrevHp() > boss_hp[now_stage] / 3)
					{
						//�_���[�W�G�t�F�N�g���o��
						EnemyDeadEffect( bx, by );
						//�_���[�W����炷
						boss_change_flag = true;
						//����ɓ��_��������
						score->SetScore( CURRENT_SCORE, 1000 );
						//�A�C�e�����o���B
						for (int z = 0; z < ITEM_NUM; ++z)
						{
							if (!item[z].GetFlag())
							{
								//�A�C�e���̏������W���΂炯������B
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z].SetFlag( ix, iy, rand() % (ITEM_TYPE_NUM - 1) + 1 );
								++itemnum;
								//5�o�����烋�[�v�𔲂���
								if (itemnum == 7)
								{
									break;
								}
							}
						}
						boss[now_stage]->SetDamageSetting();
					}
					else if (boss[now_stage]->GetHp() <= 0)
					{
						boss[now_stage]->SetFlag( false );
						stage_finish_flag[now_stage] = boss[now_stage]->GetFlag();
						EnemyDeadEffect( bx, by );
						bdead_flag = true;
						score->SetScore( CURRENT_SCORE, 10000 );

						for (int z = 0; z < ITEM_NUM; z++)
						{
							if (!item[z].GetFlag())
							{
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z].SetFlag( ix, iy, rand() % (ITEM_TYPE_NUM - 1) + 1 );
								++itemnum;
								if (itemnum == 12) break;
							}
						}

						//�{�X������C�ꎞ��~
						count = -60;

						if (now_stage == STAGE_NUM - 1)
						{
							//�N���A�t�@���t�@�[��
							clear_flag = true;
							//�N���A���S��\��
							game_clear_flag = true;
							StopSoundMem( s_bgm[now_stage] );
							break;
						}
						else if (now_stage < STAGE_NUM - 1)
						{
							StopSoundMem( s_bgm[now_stage] );
							//����X�e�[�^�X�A�b�v
							player->AddStatus( POWER_LIMIT, 5 );
							player->AddStatus( SPEED_LIMIT, 5 );

							now_stage++;
							back->SetNowStage( now_stage );
						}
					}

				}
			}
		}
	}

	//�{�X�̃V���b�g�ƃv���C���[�Ƃ̓����蔻��
	if (!player->GetDeadFlag() && !player->GetDamageFlag() && !player->GetDamageZeroFlag())
	{
		player->GetPosition( &px, &py );
		for (int i = 0; i < BOSS_SHOTNUM; ++i)
		{
			if (boss[now_stage]->GetShotPosition( i, &bx, &by, &type ))
			{
				switch (type)
				{
					case 0:
						if (CircleCollision( GRAZE_COLLISION, ESHOT0_COLLISION, px, bx, py, by ))
						{
							gflag = true;
						}
						if (CircleCollision( PLAYER_COLLISION, ESHOT0_COLLISION, px, bx, py, by ))
						{
							hflag = true;
						}
						break;

					case 1:
						if (CircleCollision( GRAZE_COLLISION, ESHOT1_COLLISION, px, bx, py, by ))
						{
							gflag = true;
						}
						if (CircleCollision( PLAYER_COLLISION, ESHOT1_COLLISION, px, bx, py, by ))
						{
							hflag = true;
						}
						break;

					case 2:
						if (CircleCollision( GRAZE_COLLISION, ESHOT2_COLLISION, px, bx, py, by ))
						{
							gflag = true;
						}
						if (CircleCollision( PLAYER_COLLISION, ESHOT2_COLLISION, px, bx, py, by ))
						{
							hflag = true;
						}
						break;
				}
				//�O���C�Y�t���O�������Ă���
				if (gflag)
				{
					if (!effect_pbarrier->GetBarrierFlag())
					{
						//�Y���̒e�����ɃO���C�Y���Ă��邩�`�F�b�N
						//if (!boss[now_count]->GetGrazeFlag( i ))
						if (!boss[now_stage]->GetGrazeFlag( i ))
						{
							//boss[now_count]->SetGrazeFlag( i );
							boss[now_stage]->SetGrazeFlag( i );
							//�܂��g���ĂȂ��O���C�Y�G�t�F�N�g��T��
							for (int z = 0; z < GRAZE_NUM; ++z)
							{
								if (!graze[z].GetFlag())
								{
									graze[z].SetFlag( px, py );
									break;

								}
							}
							//�X�R�A�����Z
							//score->SetScore( GRAZE_SCORE, 1 );
							player->AddStatus( GRAZE, 1 );
							score->SetScore( CURRENT_SCORE, 20 );
							graze_flag = true;


						}
					}
					//���̒e�̃O���C�Y���`�F�b�N���邽�߃t���O��߂��B
					gflag = false;
				}
				if (hflag)
				{
					//�o���A���W�J����Ă��Ȃ����
					if (!effect_pbarrier->GetBarrierFlag())
					{
						//����L������damageflag�𗧂Ă�
						player->SetDamageFlag( boss[now_stage]->GetShotDamage( i ) );
						//�e������
						boss[now_stage]->SetShotFlag( i, false );

						if (player->GetStatus( HP ) <= 0)
						{
							//�v���C���[���ŉ��t���O�𗧂Ă�
							pdead_flag = true;

							//�v���C���[���ŃG�t�F�N�g
							PlayerDeadEffect( px, py );

							//�X�e�[�^�X����
							player->AddStatus( STOCK, -1 );
							player->AddStatus( SPEED, -3 );
							player->AddStatus( POWER, -3 );
							player->AddStatus( HP, PLAYER_LIFE );
						}
						else
						{
							pdamage_flag = true;
						}
					}
					else// if (effect_pbarrier->GetBarrierFlag())
					{
						player->SetDamageFlag( 0 );
						effect_pbarrier->Add_BarrierHp( -1/*-enemy[i]->GetShotDamage( s )*/ );
						boss[now_stage]->SetShotFlag( i, false );

						if (effect_pbarrier->GetBarrierHp() <= 0)
						{
							player->AddStatus( GRAZE, 1 );
							//effect_pbarrier->SetBarrierFlag( false );
							pbarrier_break_flag = true;
						}
						pbarrier_damage_flag = true;
					}
					//�ꎞ�t���O��߂�
					hflag = false;
					break;
				}
			}
		}
	}

	//�A�C�e���ƃv���C���[�̓����蔻��
	if (!player->GetDeadFlag() && !player->GetDamageFlag() || player->GetDamageZeroFlag())
	{

		double ix, iy;
		player->GetPosition( &px, &py );
		//�A�C�e���ƃv���C���[�Ƃ̓����蔻��
		for (int i = 0; i < ITEM_NUM; ++i)
		{
			if (item[i].GetFlag())
			{
				item[i].GetPosition( &ix, &iy );
				if (CircleCollision( PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy ))
				{
					switch (item[i].GetType())
					{
						case ITEM_SCOREUP:
							score->SetScore( CURRENT_SCORE, 300 );
							item0_flag = true;
							break;

						case ITEM_POWERUP:
							player->AddStatus( POWER, 1 );
							item1_flag = true;
							break;

						case ITEM_SPEEDUP:
							player->AddStatus( SPEED, 1 );
							item2_flag = true;
							break;

						case ITEM_LIFEUP:
							player->AddStatus( HP, 1 );
							item3_flag = true;
							break;

						default:
							break;
					}
					item[i].Delete();
				}
			}
		}
	}

	//���C�t�͖���擾
	score->SetScore( GRAZE_SCORE, player->GetStatus( GRAZE ) );
	score->SetScore( SPEED_SCORE, player->GetStatus( SPEED ) );
	score->SetScore( SPEED_LIMIT_SCORE, player->GetStatus( SPEED_LIMIT ) );
	score->SetScore( POWER_SCORE, player->GetStatus( POWER ) );
	score->SetScore( POWER_LIMIT_SCORE, player->GetStatus( POWER_LIMIT ) );
	score->SetScore( STOCK_SCORE, player->GetStatus( STOCK ) );
	score->SetScore( LIFE_SCORE, player->GetStatus( HP ) );
}

void Game::Init_SoundFlag()
{
	bgm_flag
		= pbarrier_flag
		= pbarrier_damage_flag
		= pbarrier_break_flag
		= ebarrier_damage_flag
		= ebarrier_break_flag
		= pcharge_flag
		= pcharge_stop_flag
		= eshot_flag
		= pshot_flag
		= edamage_flag
		= pdamage_flag
		= edead_flag
		= pdead_flag
		= bdead_flag
		= graze_flag
		= item0_flag
		= item1_flag
		= item2_flag
		= item3_flag
		= boss_change_flag
		= clear_flag
		= false;

}

void Game::SoundAll()
{
	if (bgm_flag) PlaySoundMem( s_bgm[now_stage], DX_PLAYTYPE_BACK );
	if (pbarrier_flag) PlaySoundMem( s_pbarrier, DX_PLAYTYPE_BACK );
	if (pbarrier_damage_flag) PlaySoundMem( s_pbarrier_damage, DX_PLAYTYPE_BACK );
	if (pbarrier_break_flag) PlaySoundMem( s_pbarrier_break, DX_PLAYTYPE_BACK );
	if (ebarrier_damage_flag) PlaySoundMem( s_ebarrier_damage, DX_PLAYTYPE_BACK );
	if (ebarrier_break_flag) PlaySoundMem( s_ebarrier_break, DX_PLAYTYPE_BACK );
	if (pcharge_flag) PlaySoundMem( s_pcharge, DX_PLAYTYPE_BACK );
	if (pcharge_stop_flag) StopSoundMem( s_pcharge );
	if (pcharge_stop_flag) PlaySoundMem( s_pcharge_max, DX_PLAYTYPE_BACK );
	if (eshot_flag) PlaySoundMem( s_eshot, DX_PLAYTYPE_BACK );
	if (pshot_flag) PlaySoundMem( s_pshot, DX_PLAYTYPE_BACK );
	if (edamage_flag) PlaySoundMem( s_edamage, DX_PLAYTYPE_BACK );
	if (pdamage_flag) PlaySoundMem( s_pdamage, DX_PLAYTYPE_BACK );
	if (edead_flag) PlaySoundMem( s_edead, DX_PLAYTYPE_BACK );
	if (pdead_flag) PlaySoundMem( s_pdead, DX_PLAYTYPE_BACK );
	if (bdead_flag) PlaySoundMem( s_bdead, DX_PLAYTYPE_BACK );
	if (graze_flag) PlaySoundMem( s_graze, DX_PLAYTYPE_BACK );
	if (item0_flag) PlaySoundMem( s_item0, DX_PLAYTYPE_BACK );
	if (item1_flag) PlaySoundMem( s_item1, DX_PLAYTYPE_BACK );
	if (item2_flag) PlaySoundMem( s_item2, DX_PLAYTYPE_BACK );
	if (item3_flag) PlaySoundMem( s_item3, DX_PLAYTYPE_BACK );
	if (boss_change_flag) PlaySoundMem( s_boss_change, DX_PLAYTYPE_BACK );
	if (clear_flag) PlaySoundMem( s_clear, DX_PLAYTYPE_BACK );

}