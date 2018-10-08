#include "Menu.h"
#include "define.h"
#include "Keyboard.h"
#include "DxLib.h"

Menu::Menu( ISceneChanger* changer ) : BaseScene( changer )
{
}

//初期化
void Menu::Initialize()
{
	SetDrawArea( 0, 0, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT );
	//mImageHandle = LoadGraph( "../images/クラフィ表紙.jpg" );    //画像のロード
	mImageHandle = LoadGraph( "../images/title01.jpg" );    //画像のロード
}

//更新
void Menu::Update()
{
	if (Keyboard_Get( KEY_INPUT_DOWN ) == 1)
	{//Gキーが押されていたら
		NowSelect = (NowSelect + 1) % (eMenu_Num - 1);
		//mSceneChanger->ChangeScene(eScene_Game);//シーンをゲーム画面に変更
	}
	if (Keyboard_Get( KEY_INPUT_UP ) == 1)
	{//Cキーが押されていたら
		NowSelect = (NowSelect + 1) % (eMenu_Num - 1);
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

			default:
				break;
		}
	}
}

//描画
void Menu::Draw()
{
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	/*
	DrawString(0, 0, "メニュー画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Gキーを押すとゲーム画面に進みます。", GetColor(255, 255, 255));
	DrawString(0, 40, "Cキーを押すと　設定画面に進みます。", GetColor(255, 255, 255));
	*/
	DrawString( 200, 150, "メニュー画面です。", GetColor( 255, 255, 255 ) );
	DrawString( 200, 170, "上下キーを押し、エンターを押して下さい。", GetColor( 255, 255, 255 ) );
	DrawString( 280, GAME_Y, "ゲーム", GetColor( 255, 255, 255 ) );
	DrawString( 280, CONFIG_Y, "設定", GetColor( 255, 255, 255 ) );
	int y = 0;
	switch (NowSelect)
	{//現在の選択状態に従って処理を分岐
		case eMenu_Game://ゲーム選択中なら
			y = GAME_Y;    //ゲームの座標を格納
			break;
		case eMenu_Config://設定選択中なら
			y = CONFIG_Y;    //設定の座標を格納
			break;
	}
	DrawString( 250, y, "■", GetColor( 255, 255, 255 ) );
}