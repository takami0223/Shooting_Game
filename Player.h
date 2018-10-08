//#ifndef _PLAYER_H_
//#define _PLAYER_H_

#pragma once

#include "define.h"
#include "Effect_Pdead.h"
#include "Ball.h"

enum StatusData
{
	GRAZE,
	STOCK,
	HP,
	SPEED,
	SPEED_LIMIT,
	POWER,
	POWER_LIMIT,
	RAPIDFIRE
};

struct Shot
{
	bool flag;         //弾が発射中かどうか
	double x;		   //球のx座標
	double y;          //球のy座標
	int gh;            //球のグラフィックハンドル変数
	int width, height; //画像幅
	double rad;		   //角度
	int type;		   //弾の種類(0なら通常、1なら追尾
};

class Player
{
private:

	Effect_Pdead effect_Pdead;
	Ball ball;

	Shot shot[PSHOT_NUM];

	int playerImgWidth, playerImgHeight;  //画像幅
	int playerGh[12];         //グラフィックハンドル格納用配列
	float move;         //移動係数
	int xcount, ycount; //横方向,縦方向のカウント数
	int ix, iy, result; //添字用変数

	static int chargeEffectHandle; //チャージエフェクトハンドル

	int graze;			//グレイズ数
	int stock;			//残機数
	int life;           //体力
	int speed;			//スピードアイテム取得数
	int power;			//パワーアイテム取得数
	int powerLimit;
	int speedLimit;

	//アイテム数に応じて変化するステータス
	double playerSpeed; //プレイヤーのスピード
	int rapidfire;		//連射扱いになるフレーム数
	int shotInterval;		//連射の際の弾の間隔フレーム数

	//ステータスの最高上限
	double bestPlayerSpeed;
	int bestRapidfire;
	int bestShotInterval;

	//ステータスの最低保証
	double initPlayerSpeed;
	int initRapidfire;
	int initShotinterval;

	int count;			//playerクラスの実行フレーム数
	int dcount;			//ダメージ中のカウント
	int ccount;			//チャージ音のカウント

	bool dcountInitFlag;	//dcountが初期化されたか
	bool damageFlag;    //ダメージを受けたかのフラグ
	bool damageZeroFlag;//無敵状態かのフラグ
	bool deadFlag;		//ライフが0になり、ゲームオーバーになったかのフラグ

	bool s_charge;		//チャージ音のフラグ
	bool s_chargeNow;  //チャージ中のフラグ
	bool s_chargeStop;	//チャージ終了音のフラグ
	bool s_shot;	    //弾を発射されたかのフラグ


public:
	double x, y;	//キャラクターのx座標,y座標
	double e_x, e_y;//敵の座標
	double b_x, b_y;//ボスの座標
	bool boss_flag;
	int nearindex;

private:
	void Move();
	void Shot();
	void Draw();

	void BallUpdate();
	void BallDraw();
	void BallShotSet( int index );

public:

	Player();

	//値の設定
	void AddStatus( StatusData data, int num );

	//値の取得
	int GetStatus( StatusData data );
	void GetPosition( double *x, double *y );
	bool GetShotPosition( int index, double *x, double *y );

	//フラグの設定
	void SetShotFlag( int index, bool flag );
	void SetDamageFlag( int damage );

	//フラグの取得
	bool GetDamageFlag();
	bool GetDamageZeroFlag();
	bool GetDeadFlag();
	bool isPlayShotSound();
	bool isPlayChargeSound();
	bool isPlayChargeStopSound();

	//All
	void Update_All();
	void Draw_All();
};

//#endif // !_PLAYER_H_