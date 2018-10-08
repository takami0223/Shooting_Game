//#ifndef _SCENEMGR_H_
//#define _SCENEMGR_H_

#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"

class SceneMgr : public ISceneChanger, Task
{

private:
	BaseScene * mScene;      //シーン管理変数
	BaseScene *temp_mScene;
	eScene mNextScene;       //次のシーン管理変数
	bool temp_flag;

public:
	SceneMgr();
	void Initialize() override;//初期化
	void Finalize() override;//終了処理
	void Update() override;//更新
	void Draw() override;//描画

	// 引数 nextScene にシーンを変更する
	void ChangeScene( eScene NextScene ) override;

};

//#endif // !_SCENEMGR_H_