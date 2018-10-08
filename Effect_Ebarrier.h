#pragma once

#include "define.h"

class Effect_Ebarrier
{
private:
	static int gh;
	bool flag;

public:
	double x, y;

private:
	void Move();
	void Draw();

public:
	Effect_Ebarrier();
	void SetFlag( double x, double y );
	//void SetFlag();
	bool GetFlag();
	void All();

};