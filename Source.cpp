#include <math.h>
#include "DxLib.h"

#define PI 3.1415926f

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	int Handle[3];     // 画像格納用ハンドル
	LoadDivGraph("../images/弾01.png", 3, 3, 1, 14, 16, Handle); // 3つに画像を分割してロード

	float x = 320, y = 240, angle = 0, speed = 1;

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{

		x += cos(angle) * speed;      // x座標を更新
		y += sin(angle) * speed;      // y座標を更新

		if (CheckHitKey(KEY_INPUT_Z) == 1)
		{//zが押されていたら変数の中身を変更
			x = 320;        //初期座標にセット
			y = 240;
			angle = GetRand(10000) / 10000.f * (PI * 2);        //0～PI*2の乱数を生成
			speed = 0.5f + GetRand(10000) / 10000.f * 2;      //0.5～2.5の乱数を生成
		}

		DrawRotaGraph(x, y, 1.0, angle + PI / 2, Handle[0], TRUE);//弾を描画
		DrawFormatString(0, 0, GetColor(255, 255, 255), "angle=%.2f, speed=%.2f\n", angle, speed);

	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}