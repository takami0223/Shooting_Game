#pragma once

#include "define.h"

class Ball
{
private:
	int gh;

	bool toggle; //上下にふわふわ浮かせるため
	int raise;
	double angle;

public:
	double x, y;

private:
	void Move( double px, double py );
	void Draw();

public:
	Ball();

	void Update_All( double px, double py );
	void Draw_All();
	void All( double px, double py );
	double GetPosition();
};