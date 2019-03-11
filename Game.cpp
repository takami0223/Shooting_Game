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

//初期化
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

	//敵データの作成
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
		//ヘッダ読み飛ばし
		while (fgetc( fp ) != '\n');

		while (1)
		{
			while (1)
			{

				c = fgetc( fp );

				//末尾ならループを抜ける。
				if (c == EOF) //|| row >= ENEMY_NUM)
					goto out;

				//カンマか改行でなければ、文字としてつなげる
				if (c != ',' && c != '\n')
					//strcat(buf, (const char*)&c);
					strcat_s( buf, 100, (const char*)&c );
				//カンマか改行ならループ抜ける。
				else
					break;
			}
			//ここに来たということは、1セル分の文字列が出来上がったということ
			switch (col)
			{
				//1列目は敵種類を表す。atoi関数で数値として代入。
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
			//バッファを初期化
			memset( buf, 0, sizeof( buf ) );
			//列数を足す
			++col;

			//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
			if (c == '\n')
			{
				col = 1;
				++row;
				data.push_back( temp_data );
			}
		}
	out:

		//敵クラス生成
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

	//BGMファイル読み込み
	s_bgm[0] = LoadSoundMem( "../sounds/Stage01_BGM.mp3" );
	s_bgm[1] = LoadSoundMem( "../sounds/Stage02_BGM.mp3" );
	s_bgm[2] = LoadSoundMem( "../sounds/Stage03_BGM.mp3" );

	//効果音ファイル読み込み
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

//更新
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
			//mSceneChanger->ChangeScene( eScene_Pause );//シーンをメニューに変更
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

		//背景
		back->Update_All();

		//敵
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

					//敵ショットサウンドフラグチェック
					if (enemy[now_stage][i]->isPlaySound())
					{
						eshot_flag = true;
						s_eshot = enemy[now_stage][i]->GetPlaySound();
					}
				}
			}
		}

		//プレイヤー
		player->Update_All();

		//プレーヤーのチャージ位置
		//if (!player->GetDeadFlag())
		//{
		/*
		effect_pcharge->x = player->x;
		effect_pcharge->y = player->y;
		effect_pcharge->max_charge = player->Get_Status( RAPIDFIRE );
		effect_pcharge->Update_All();
		*/
	//}

	//プレイヤーのホーミング位置
		EnemyTracking();


		//プレーヤーバリア位置
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

		//プレイヤー消滅エフェクト位置
		for (int i = 0; i < EFFECT_PDEADNUM; ++i)
		{
			effect_pdead[i].Update_All();
		}


		//敵消滅エフェクト
		for (int i = 0; i < EFFECT_EDEADNUM; ++i)
		{
			effect_edead[i].Update_All();
		}

		//グレイズ
		for (int i = 0; i < GRAZE_NUM; ++i)
		{
			graze[i].Update_All();
		}

		//アイテム
		for (int i = 0; i < ITEM_NUM; ++i)
		{
			item[i].Update_All();
		}

		//ステージをクリアしたか
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


		//プレーヤーのショット音
		if (player->isPlayShotSound())
		{
			pshot_flag = true;
		}

		//プレーヤーのチャージ音
		if (player->isPlayChargeSound())
		{
			pcharge_flag = true;
		}

		//プレーヤーのチャージ完了音
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

		//ゲームクラスの総フレーム数
		++count;

	}
}

//描画・音
void Game::Draw()
{
	SetDrawArea( MARGIN, MARGIN, MARGIN + 380, MARGIN + 460 );


	//BaseScene::Draw();//親クラスの描画メソッドを呼ぶ(背景変更)
	//DrawString( 0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor( 255, 255, 255 ) );


	//背景描画
	back->Draw_All();

	//敵描画
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


	//プレーヤーのチャージ描画
	if (!player->GetDeadFlag())
	{
		effect_pcharge->x = player->x;
		effect_pcharge->y = player->y;
		effect_pcharge->max_charge = player->GetStatus( RAPIDFIRE );
		effect_pcharge->All(); //Move()を分離するとちらつく
	}
	//プレイヤー描画
	player->Draw_All();

	//プレイヤーバリア描画
	effect_pbarrier->Draw_All();

	//プレイヤー消滅エフェクト描画
	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		effect_pdead[i].Draw_All();
	}


	//敵消滅エフェクト描画
	for (int i = 0; i < EFFECT_EDEADNUM; ++i)
	{
		effect_edead[i].Draw_All();
	}

	//グレイズ描画
	for (int i = 0; i < GRAZE_NUM; ++i)
	{
		graze[i].Draw_All();
	}

	//アイテム描画
	for (int i = 0; i < ITEM_NUM; ++i)
	{
		item[i].Draw_All();
	}

	//ボス描画
	if (stage_finish_flag[now_stage])
	{
		boss[now_stage]->Draw_All();
	}

	//ゲームオーバー画面描画
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


	//スコア描画
	SetDrawArea( 0, 0, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT );
	score->All();

	//サウンドオン
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

	//指定した添字の敵の座標を取得
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
	//エフェクトセット
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

			//ウェーブの進み具合によって1ウェーブの敵の数を決める
			if (waveNum < WAVE_NUM / 5)
			{
				//wave_enemy = rand() % 2 + 2; //2 ～ 3
				wave_enemy = 3 + stageNum; //2 ～ 4
			}
			else if (waveNum < (WAVE_NUM / 5) * 2)
			{
				//wave_enemy = rand() % 3 + 2; //2 ～ 4
				wave_enemy = rand() % 3 + 3 + stageNum; //4 ～ 6
			}
			else if (waveNum < (WAVE_NUM / 5) * 3)
			{
				//wave_enemy = rand() % 3 + 3; //3 ～ 5
				wave_enemy = rand() % 2 + 4 + stageNum; //5 ～ 6
			}
			else if (waveNum < (WAVE_NUM / 5) * 4)
			{
				//wave_enemy = rand() % 4 + 4; //4 ～ 7
				wave_enemy = rand() % 3 + 4 + stageNum; //5 ～ 7
			}
			else
			{
				//wave_enemy = 10;
				wave_enemy = rand() % 2 + 6 + stageNum; //7 ～ 8
			}

			//1ウェーブに出現する敵1体1体を設定
			for (int z = 0; z < wave_enemy; z++)
			{
				EnemyData temp_data;

				int wave_between = 220; //次のウェーブに進むまでのフレーム数

				temp_data.type = rand() % (stageNum + 1);

				//ウェーブの進み具合に応じた「敵のタイプ」「バリアの有無」「バリアのHP」「アイテムのドロップ率」
				if (waveNum < WAVE_NUM / 4)
				{
					/*
					temp_data.type = ENEMY_0; //0 ～ 1
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
					temp_data.type = rand() % 2; //0 ～ 1
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
					temp_data.type = rand() % 3; //0 ～ 2
					int check = rand() % 5;
					if (check == 0) temp_data.barrier_hp = rand() % 3 + 1; //1 ～ 3
					else temp_data.barrier_hp = 0;

					int item = rand() % 10;
					if (item < 3) temp_data.item = ITEM_SCOREUP;
					else if (item < 5) temp_data.item = ITEM_POWERUP;
					else if (item < 7) temp_data.item = ITEM_SPEEDUP;
					else if (item < 10) temp_data.item = ITEM_LIFEUP;
					*/

					int check = rand() % (stageNum + 1);
					if (check == 1) temp_data.barrier_hp = rand() % 3 + 1; //1 ～ 3
					else temp_data.barrier_hp = 0;

				}
				else
				{
					/*
					temp_data.type = rand() % 2 + 1; //1 ～ 2
					int check = rand() % 3;
					if (check == 0) temp_data.barrier_hp = rand() % 2 + 4; //4 ～ 5
					else temp_data.barrier_hp = 0;

					int item = rand() % 10;
					if (item < 4) temp_data.item = ITEM_SCOREUP;
					else if (item < 5) temp_data.item = ITEM_POWERUP;
					else if (item < 6) temp_data.item = ITEM_SPEEDUP;
					else if (item < 10) temp_data.item = ITEM_LIFEUP;
					*/
					int check = rand() % (stageNum + 1);
					if (check == 2) temp_data.barrier_hp = rand() % 2 + 4; //4 ～ 5
					else temp_data.barrier_hp = 0;
				}

				//敵の種類によって固定される「移動スピード」「弾のスピード」「HP」「弾の攻撃力」を変更
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
						temp_data.move_speed = rand() % 2 + 2; //2 ～ 3
						temp_data.speed = rand() % 2 + 3; //3 ～ 4
						temp_data.hp = 5 * (stageNum + 1);
						temp_data.power = 2 * (stageNum + 1);
						break;

					case ENEMY_2:
						temp_data.move_speed = rand() % 2 + 3; //3 ～ 4
						temp_data.speed = rand() % 3 + 4; //4 ～ 6
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

				//1waveに乱射タイプの敵は一体まで(そいつは移動制限)に制限
				do
				{
					temp_data.stype = rand() % BALL_TYPE_NUM;
				} while (ballShootingFlag == true && temp_data.stype == BALL_SHOOTING);

				//弾の種類によって固定される「発射パターン」「サウンド」「移動パターン」を決定
				switch (temp_data.stype)
				{
					case BALL_LINE:
						temp_data.s_pattern = 0;
						temp_data.sound = 0;
						temp_data.m_pattern = rand() % BOSS_MOVE_TYPE_NUM;
						break;

					case BALL_RAPIDFIRE:
						temp_data.s_pattern = rand() % 2 + 1; //1 ～ 2
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
				0:スコアプラス
				1:パワーアップ
				2:スピードアップ
				3:HP回復
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

		//敵クラス生成
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
/// 円形専用の当たり判定関数
/// </summary>
/// <param name="c1">円形１の半径</param>
/// <param name="c2">円形２の半径</param>
/// <param name="cx1">円形１の x座標</param>
/// <param name="cx2">円形２の x座標</param>
/// <param name="cy1">円形１の y座標</param>
/// <param name="cy2">円形２の y座標</param>
/// <returns></returns>
bool Game::CircleCollision( double c1, double c2, double cx1, double cx2, double cy1, double cy2 )
{
	double hlength = c1 + c2; //2つの円の半径の合計
	double xlength = cx1 - cx2; //2つの円のx軸での距離
	double ylength = cy1 - cy2; //2つの円のy軸での距離

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

	//操作キャラの弾と敵との当たり判定
	for (int i = 0; i < PSHOT_NUM; ++i)
	{
		if (player->GetShotPosition( i, &psx, &psy ))
		{
			for (int s = 0; s < enemy[now_stage].size(); ++s)
			{
				//敵クラスのポインタがNULLじゃない、かつdeadflagがfalse(死んでない＆帰還してない)
				if (enemy[now_stage][s] != NULL && !enemy[now_stage][s]->GetDeadFlag())
				{
					enemy[now_stage][s]->GetPosition( &ex, &ey );
					//当たり判定
					if (CircleCollision( PSHOT_COLLISION, ENEMY1_COLLISION, psx, ex, psy, ey ))
					{
						//当たっていれば、deadflagを立てる
						//enemy[s]->SetDeadFlag();

						if (!enemy[now_stage][s]->GetBarrierFlag())
						{
							//当たっていれば、敵のHPを減らす（HPが0になればdeadflagが立つ）
							enemy[now_stage][s]->SetHp( -1 );
							//当たった弾のフラグを戻す
							player->SetShotFlag( i, false );

							//敵が死んだ時
							if (enemy[now_stage][s]->GetDeadFlag())
							{
								//敵消滅音フラグセット
								edead_flag = true;
								//敵消滅エフェクトセット
								EnemyDeadEffect( ex, ey );
								//得点を加える
								score->SetScore( CURRENT_SCORE, 100 );

								//アイテム出現
								for (int i = 0; i < ITEM_TYPE_NUM; i++)
								{
									if (!item[i].GetFlag())
									{
										if ((rand() % 10) >= 5)
										{
											//item[i]->SetFlag( ex, ey, enemy[s]->GetItemType() );
											switch (enemy[now_stage][s]->GetItemType())
											{
												//スコア増加
												case ITEM_SCOREUP:
													item[i].SetFlag( ex, ey, ITEM_SCOREUP );
													break;

												//パワーアップ
												case ITEM_POWERUP:
													item[i].SetFlag( ex, ey, ITEM_POWERUP );
													break;

												//スピードアップ
												case ITEM_SPEEDUP:
													item[i].SetFlag( ex, ey, ITEM_SPEEDUP );
													break;

												//HP回復
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

	//敵と操作キャラとの当たり判定
	//プレイヤーが「生きていて」「ダメージを受けておらず」「バリア中にダメージを受けていない」
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
					//バリアが展開されていなければ
					if (!effect_pbarrier->GetBarrierFlag())
					{
						//操作キャラのdamageflagを立てる
						player->SetDamageFlag( 1 );
						//弾を消す
						//enemy[now_stage][i]->SetShotFlag( s, false );

						if (player->GetStatus( HP ) <= 0)
						{
							//プレイヤー消滅音フラグを立てる
							pdead_flag = true;

							//プレイヤー消滅エフェクト
							PlayerDeadEffect( px, py );

							//ステータス減少
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
					//一時フラグを戻す
					tempflag = false;
					break;
				}
			}
		}
	}

	//敵の弾と操作キャラとの当たり判定
	//プレイヤーが「生きていて」「ダメージを受けておらず」「バリア中にダメージを受けていない」
	if (!player->GetDeadFlag() && !player->GetDamageFlag() && !player->GetDamageZeroFlag())
	{
		player->GetPosition( &px, &py );
		for (int i = 0; i < enemy[now_stage].size(); ++i)
		{
			if (enemy[now_stage][i] != NULL)
			{
				for (int s = 0; s < ENEMY_SNUM; ++s)
				{

					//弾フラグが立っていればtrueを返す
					if (enemy[now_stage][i]->GetShotPosition( s, &ex, &ey ))
					{
						//弾によって当たり判定が違うのでswitch文で分岐
						switch (enemy[now_stage][i]->GetShotType())
						{

							case BALL_LINE:
								//グレイズ判定
								if (CircleCollision( GRAZE_COLLISION, ESHOT0_COLLISION, px, ex, py, ey ))
								{
									if (GRAZE_COLLISION - PLAYER_COLLISION < graze_count)
									{
										gtempflag = true;
										graze_count = 0;
									}
									graze_count++;

								}
								//通常の当たり判定
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


						//グレイズ当たり判定フラグがtrueなら
						if (gtempflag)
						{
							if (!effect_pbarrier->GetBarrierFlag())
							{
								if (!enemy[now_stage][i]->GetGrazeFlag( s ))
								{
									enemy[now_stage][i]->SetGrazeFlag( s );
									//グレイズのインスタンス検索
									for (int z = 0; z < GRAZE_NUM; ++z)
									{
										if (!graze[z].GetFlag())
										{
											graze[z].SetFlag( px, py );
											break;
										}
									}
									//グレイズの得点を加える
									//score->SetScore( GRAZE_SCORE, 1 );
									score->SetScore( CURRENT_SCORE, 20 );
									player->AddStatus( GRAZE, 1 );

									//グレイズ音セット
									graze_flag = true;
								}

							}
							gtempflag = false;
						}

						if (tempflag)
						{
							//バリアが展開されていなければ
							if (!effect_pbarrier->GetBarrierFlag())
							{
								//操作キャラのdamageflagを立てる
								player->SetDamageFlag( enemy[now_stage][i]->GetShotDamage( s ) );
								//弾を消す
								enemy[now_stage][i]->SetShotFlag( s, false );

								if (player->GetStatus( HP ) <= 0)
								{
									//プレイヤー消滅音フラグを立てる
									pdead_flag = true;

									//プレイヤー消滅エフェクト
									PlayerDeadEffect( px, py );

									//ステータス減少
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
							//一時フラグを戻す
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

	//アイテムと操作キャラとの当たり判定
	//プレイヤーが「生きていて」「ダメージを受けておらず」「バリア中にダメージを受けていない」
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

	//出すアイテム数
	int itemnum = 0;

	//グレイズとヒットしたかのフラグ
	bool hflag = false, gflag = false;

	//ボスの弾の種類
	int type;

	//プレイヤーとボスの当たり判定
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
			//バリアが展開されていなければ
			if (!effect_pbarrier->GetBarrierFlag())
			{
				//操作キャラのdamageflagを立てる
				player->SetDamageFlag( 1 );
				//弾を消す
				//boss[now_stage]->SetShotFlag( i, false );

				if (player->GetStatus( HP ) <= 0)
				{
					//プレイヤー消滅音フラグを立てる
					pdead_flag = true;

					//プレイヤー消滅エフェクト
					PlayerDeadEffect( px, py );

					//ステータス減少
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
			//一時フラグを戻す
			hflag = false;
		}
	}

	//プレイヤーのショットとボスの当たり判定
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
						//ダメージエフェクトを出す
						EnemyDeadEffect( bx, by );
						//ダメージ音を鳴らす
						boss_change_flag = true;
						//さらに得点を加える
						score->SetScore( CURRENT_SCORE, 1000 );
						//アイテムを出す。
						for (int z = 0; z < ITEM_NUM; ++z)
						{
							if (!item[z].GetFlag())
							{
								//アイテムの初期座標をばらけさせる。
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z].SetFlag( ix, iy, rand() % (ITEM_TYPE_NUM - 1) + 1 );
								++itemnum;
								//5個出したらループを抜ける
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
						//ダメージエフェクトを出す
						EnemyDeadEffect( bx, by );
						//ダメージ音を鳴らす
						boss_change_flag = true;
						//さらに得点を加える
						score->SetScore( CURRENT_SCORE, 1000 );
						//アイテムを出す。
						for (int z = 0; z < ITEM_NUM; ++z)
						{
							if (!item[z].GetFlag())
							{
								//アイテムの初期座標をばらけさせる。
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z].SetFlag( ix, iy, rand() % (ITEM_TYPE_NUM - 1) + 1 );
								++itemnum;
								//5個出したらループを抜ける
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

						//ボス討伐後，一時停止
						count = -60;

						if (now_stage == STAGE_NUM - 1)
						{
							//クリアファンファーレ
							clear_flag = true;
							//クリアロゴを表示
							game_clear_flag = true;
							StopSoundMem( s_bgm[now_stage] );
							break;
						}
						else if (now_stage < STAGE_NUM - 1)
						{
							StopSoundMem( s_bgm[now_stage] );
							//特殊ステータスアップ
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

	//ボスのショットとプレイヤーとの当たり判定
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
				//グレイズフラグが立ってたら
				if (gflag)
				{
					if (!effect_pbarrier->GetBarrierFlag())
					{
						//該当の弾が既にグレイズしているかチェック
						//if (!boss[now_count]->GetGrazeFlag( i ))
						if (!boss[now_stage]->GetGrazeFlag( i ))
						{
							//boss[now_count]->SetGrazeFlag( i );
							boss[now_stage]->SetGrazeFlag( i );
							//まだ使われてないグレイズエフェクトを探す
							for (int z = 0; z < GRAZE_NUM; ++z)
							{
								if (!graze[z].GetFlag())
								{
									graze[z].SetFlag( px, py );
									break;

								}
							}
							//スコアを加算
							//score->SetScore( GRAZE_SCORE, 1 );
							player->AddStatus( GRAZE, 1 );
							score->SetScore( CURRENT_SCORE, 20 );
							graze_flag = true;


						}
					}
					//次の弾のグレイズをチェックするためフラグを戻す。
					gflag = false;
				}
				if (hflag)
				{
					//バリアが展開されていなければ
					if (!effect_pbarrier->GetBarrierFlag())
					{
						//操作キャラのdamageflagを立てる
						player->SetDamageFlag( boss[now_stage]->GetShotDamage( i ) );
						//弾を消す
						boss[now_stage]->SetShotFlag( i, false );

						if (player->GetStatus( HP ) <= 0)
						{
							//プレイヤー消滅音フラグを立てる
							pdead_flag = true;

							//プレイヤー消滅エフェクト
							PlayerDeadEffect( px, py );

							//ステータス減少
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
					//一時フラグを戻す
					hflag = false;
					break;
				}
			}
		}
	}

	//アイテムとプレイヤーの当たり判定
	if (!player->GetDeadFlag() && !player->GetDamageFlag() || player->GetDamageZeroFlag())
	{

		double ix, iy;
		player->GetPosition( &px, &py );
		//アイテムとプレイヤーとの当たり判定
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

	//ライフは毎回取得
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