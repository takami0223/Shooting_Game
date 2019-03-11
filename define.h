//#ifndef _DEFINE_H_
//#define _DEFINE_H_

#pragma once

enum ENEMY_TYPE
{
	ENEMY_0 = 0,
	ENEMY_1 = 1,
	ENEMY_2 = 2,

	ENEMY_TYPE_NUM
};

enum BALL_TYPE
{
	BALL_LINE = 0,
	BALL_RAPIDFIRE = 1,
	BALL_SHOOTING = 2,

	BALL_TYPE_NUM
};

enum MOVE_TYPE
{
	MOVE_LINEDOWN = 0,
	MOVE_LINE = 1,
	MOVE_LEFTDOWN = 2,
	MOVE_RIGHTDOWN = 3,

	MOVE_TYPE_NUM
};

enum SHOT_TYPE
{
	SHOT_LINE = 0,
	SHOT_HOMING_LINE1 = 1,
	SHOT_HOMING_LINE3 = 2,
	SHOT_HOMING_SHOOTING = 3,

	SHOT_TYPE_NUM
};

enum ITEM_TYPE
{
	ITEM_SCOREUP = 0,
	ITEM_POWERUP = 1,
	ITEM_SPEEDUP = 2,
	ITEM_LIFEUP = 3,

	ITEM_TYPE_NUM
};

enum SOUND_TYPE
{
	SOUND_LINE = 0,
	SOUND_HOMING_LINE1 = 1,
	SOUND_HOMING_LINE3 = 2,
	SOUND_HOMING_SHOOTING = 3,

	SOUND_TYPE_NUM
};

struct E_Shot
{
	bool flag;			//弾が発射中かどうか
	double x;			//x座標
	double y;			//y座標
	double rad;			//角度
	int gh;				//グラフィックハンドル
	int sh;				//サウンドハンドル
	int type;
	int width, height;	//画像の幅と高さ
	int pattern;		//ショットパターン
	int speed;			//弾スピード
	int power;			//弾の攻撃力
	bool gflag;			//グレイズ判定用フラグ
};

//全般
#define MAX_WINDOW_WIDTH 640
#define MAX_WINDOW_HEIGHT 480
#define MARGIN 10
#define STAGE_NUM 3

//当たり判定用半径定義
#define PLAYER_COLLISION 4
#define ENEMY1_COLLISION 14
#define BOSS_COLLISION 60

#define PSHOT_COLLISION 5

#define GRAZE_COLLISION 20

#define ESHOT0_COLLISION 12
#define ESHOT1_COLLISION 5
#define ESHOT2_COLLISION 10

#define ITEM_COLLISION 16

//extern "C" int All_count;

//Player
#define PLAYER_INITX 180
#define PLAYER_INITY 400

#define PLAYER_STOCK 5
#define PLAYER_LIFE 5
#define PLAYER_SPEED 3//4

#define PLAYER_SPEED_NUM 3
#define RAPIDFIRE_NUM 150
#define SHOT_LIMIT_NUM 20

#define LIFE_LIMIT 30
#define SPEED_DEFAULT_LIMIT 30

#define POWERUP_COUNT_1 10 //3方向
#define POWERUP_COUNT_2 20 //追尾弱
#define POWERUP_COUNT_3 30 //追尾今日
#define POWER_DEFAULT_LIMIT 30//20

#define PSHOT_NUM 150
#define PSHOT_SPEED 10
#define SHOT_LIMIT 6

//Effect_Pbarrier
#define BARRIER_HP_1 5
#define BARRIER_HP_2 10 //Fullの際
#define BARRIER_OPEN_NUM 15

//Effect_Ebarrier
//#define EBARRIER_NUM 20

//Effect_Pdead
#define EFFECT_PDEADNUM 20

//Enemy
#define WAVE_NUM 30//60
//#define TYPE_NUM 3
//#define STYPE_NUM 3
//#define M_PATTEAN_NUM 4
//int ENEMY_NUM = 20;
#define ENEMY_NUM 50
#define ENEMY_SNUM 50

//Boss
#define BOSS_SHOTNUM 150
#define BOSS_SHAKE 20
#define BOSS1_HP 500
#define BOSS2_HP 700//1000
#define BOSS3_HP 1000//1500


//Effect_Edead
#define EFFECT_EDEADNUM 20

//Graze
#define GRAZE_LINIT BARRIER_OPEN_NUM * 5
#define GRAZE_NUM 1000

//Score
#define SCORE_X 390 //スコアの文字描写の基準となるｘ座標

//Item
//#define ITEM_TYPE_NUM 4 //アイテムの種類
#define ITEM_NUM 30 //アイテムの総数

//Ball
#define BALL_INITX 50
#define BALL_INITY 30
#define BALL_SHAKE 15
//Back
#define SCROLL_SPEED 2

//#endif // !_DEFINE_H_