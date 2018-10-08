//#ifndef _CONFIG_H_
//#define _CONFIG_H_

#pragma once

#include "BaseScene.h"

//設定画面クラス
class Config : public BaseScene
{

public:
	Config(ISceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド
	//void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。

};

//#endif // !_CONFIG_H_


