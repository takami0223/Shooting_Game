#include "Pause.h"
#include "define.h"
#include "Keyboard.h"
#include "DxLib.h"

Pause::Pause( ISceneChanger* changer ) : BaseScene( changer )
{
}

//初期化
void Pause::Initialize()
{
	SetDrawArea( 0, 0, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT );
	mImageHandle = LoadGraph( "../images/クラフィ表紙.jpg" );    //画像のロード
}

//更新
void Pause::Update()
{
	if (Keyboard_Get( KEY_INPUT_DOWN ) == 1)
	{//Gキーが押されていたら
		NowSelect = (NowSelect + 1) % eMenu_Num;
		//mSceneChanger->ChangeScene(eScene_Game);//シーンをゲーム画面に変更
	}
	if (Keyboard_Get( KEY_INPUT_UP ) == 1)
	{//Cキーが押されていたら
		NowSelect = (NowSelect - 1) % eMenu_Num;
		if (NowSelect < 0) NowSelect = eMenu_Num - 1;
		//mSceneChanger->ChangeScene(eScene_Config);//シーンを設定画面に変更
	}
	if (Keyboard_Get( KEY_INPUT_RETURN ) == 1)
	{
		switch (NowSelect)
		{
			case eMenu_Game:
				mSceneChanger->ChangeScene( eScene_Game );
				break;

			case eMenu_Config:
				mSceneChanger->ChangeScene( eScene_Config );
				break;

			case eMenu_Title:
				mSceneChanger->ChangeScene( eScene_Menu );
				break;

			default:
				break;
		}
	}

	/*
	if (Keyboard_Get( KEY_INPUT_ESCAPE ) == 1)
	{ //Escキーが押されていたら
		//delete this;
		mSceneChanger->ChangeScene( eScene_Game );//シーンをメニューに変更
	}
	*/

}

//描画
void Pause::Draw()
{
	//BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
					  /*
					  DrawString(0, 0, "メニュー画面です。", GetColor(255, 255, 255));
					  DrawString(0, 20, "Gキーを押すとゲーム画面に進みます。", GetColor(255, 255, 255));
					  DrawString(0, 40, "Cキーを押すと　設定画面に進みます。", GetColor(255, 255, 255));
					  */
	DrawString( 200, 150, "ポーズ画面です。", GetColor( 255, 255, 255 ) );
	DrawString( 200, 170, "上下キーを押し、エンターを押して下さい。", GetColor( 255, 255, 255 ) );
	DrawString( 280, GAME_Y, "始めから", GetColor( 255, 255, 255 ) );
	DrawString( 280, CONFIG_Y, "設定", GetColor( 255, 255, 255 ) );
	DrawString( 280, TITLE_Y, "タイトルに戻る", GetColor( 255, 255, 255 ) );

	int y = 0;

	switch (NowSelect)
	{//現在の選択状態に従って処理を分岐
		case eMenu_Game://ゲーム選択中なら
			y = GAME_Y;    //ゲームの座標を格納
			break;
		case eMenu_Config://設定選択中なら
			y = CONFIG_Y;    //設定の座標を格納
			break;

		case eMenu_Title:
			y = TITLE_Y;
			break;
	}
	DrawString( 250, y, "■", GetColor( 255, 255, 255 ) );
}