//#ifndef _BACK_H_
//#define _BACK_H_

#pragma once

class Back
{
private:
	double x, y; //背景描写開始座標
	int gh[3];      //背景グラフィックハンドル変数
	int now_stage;

private:
	void Draw();
	void Move();

public:
	Back();
	void SetNowStage( int now_stage );
	void Update_All();
	void Draw_All();
	void All();
};

//#endif // !_BACK_H_


