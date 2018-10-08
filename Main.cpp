#include "DxLib.h"
#include "Keyboard.h"
#include "SceneMgr.h"
#include "Pause.h"

//#include <crtdbg.h>

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	ChangeWindowMode( TRUE ), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	SceneMgr sceneMgr;

	bool isPause = false;
	sceneMgr.Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{//画面更新 & メッセージ処理 & 画面消去

		Keyboard_Update();

		if (Keyboard_Get( KEY_INPUT_ESCAPE ) == 1)
		{
			isPause = !isPause;
		}

		//if (!isPause)
		//{
		sceneMgr.Update();  //更新

	//}
		sceneMgr.Draw();    //描画

	}

	sceneMgr.Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}