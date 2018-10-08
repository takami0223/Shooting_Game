//#ifndef _ISCENECHANGER_H_
//#define _ISCENECHANGER_H_

#pragma once

typedef enum
{
	eScene_Menu,    //メニュー画面
	eScene_Game,    //ゲーム画面
	eScene_Config,  //設定画面
	eScene_Pause,   //ボーズ画面

	eScene_None,    //無し
} eScene;

//シーンを変更するためのインターフェイスクラス
class ISceneChanger
{
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene( eScene NextScene ) = 0;//指定シーンに変更する
};

//#endif // !_ISCENECHANGER_H_