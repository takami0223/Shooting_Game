//#ifndef _BACK_H_
//#define _BACK_H_

#pragma once

class Back
{
private:
	double x, y; //�w�i�`�ʊJ�n���W
	int gh[3];      //�w�i�O���t�B�b�N�n���h���ϐ�
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


