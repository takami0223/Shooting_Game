#include <math.h>
#include "DxLib.h"

#define PI 3.1415926f

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	int Handle[3];     // �摜�i�[�p�n���h��
	LoadDivGraph("../images/�e01.png", 3, 3, 1, 14, 16, Handle); // 3�ɉ摜�𕪊����ă��[�h

	float x = 320, y = 240, angle = 0, speed = 1;

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{

		x += cos(angle) * speed;      // x���W���X�V
		y += sin(angle) * speed;      // y���W���X�V

		if (CheckHitKey(KEY_INPUT_Z) == 1)
		{//z��������Ă�����ϐ��̒��g��ύX
			x = 320;        //�������W�ɃZ�b�g
			y = 240;
			angle = GetRand(10000) / 10000.f * (PI * 2);        //0�`PI*2�̗����𐶐�
			speed = 0.5f + GetRand(10000) / 10000.f * 2;      //0.5�`2.5�̗����𐶐�
		}

		DrawRotaGraph(x, y, 1.0, angle + PI / 2, Handle[0], TRUE);//�e��`��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "angle=%.2f, speed=%.2f\n", angle, speed);

	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}