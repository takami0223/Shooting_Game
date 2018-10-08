//#ifndef _KEYBOARD_H_
//#define _KEYBOARD_H_

#pragma once

const static int GAME_Y = 240;
const static int CONFIG_Y = 270;
const static int TITLE_Y = 300;

typedef enum
{
	eMenu_Game,
	eMenu_Config,
	eMenu_Title,

	eMenu_Num,
} eMenu;

static int NowSelect = 0;//eMenu_Game;

// �L�[�̓��͏�Ԃ��X�V����
void Keyboard_Update();

void Keyboard_Reset();

// �����̃L�[�R�[�h�̃L�[�̓��͏�Ԃ�Ԃ�
int Keyboard_Get( int KeyCode );


//#endif // !_KEYBOARD_H_