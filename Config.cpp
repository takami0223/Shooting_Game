#include "Config.h"
#include "define.h"
#include "Keyboard.h"
#include "DxLib.h"

Config::Config( ISceneChanger* changer ) : BaseScene( changer )
{
}

//初期化
void Config::Initialize()
{
	SetDrawArea( 0, 0, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT );
	mImageHandle = LoadGraph( "../images/thiko.jpg" );    //画像のロード
}

//更新
void Config::Update()
{
	if (Keyboard_Get( KEY_INPUT_ESCAPE ) == 1)
	{ //Escキーが押されていたら
		mSceneChanger->ChangeScene( eScene_Menu );//シーンをメニューに変更
	}
}

//描画
void Config::Draw()
{
	//BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString( 0, 0, "設定画面です。", GetColor( 255, 255, 255 ) );
	DrawString( 0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor( 255, 255, 255 ) );
}