//#ifndef _BACK_H_
//#define _BACK_H_

#pragma once

class Back
{
private:
	double x, y; //�w�i�`�ʊJ�n���W
	int gh;      //�w�i�O���t�B�b�N�n���h���ϐ�

private:
	void Draw();
	void Move();

public:
	Back();
	void Update_All();
	void Draw_All();
	void All();
};

//#endif // !_BACK_H_


