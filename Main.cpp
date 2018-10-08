#include "DxLib.h"
#include "Keyboard.h"
#include "SceneMgr.h"
#include "Pause.h"

//#include <crtdbg.h>

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	ChangeWindowMode( TRUE ), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	SceneMgr sceneMgr;

	bool isPause = false;
	sceneMgr.Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

		Keyboard_Update();

		if (Keyboard_Get( KEY_INPUT_ESCAPE ) == 1)
		{
			isPause = !isPause;
		}

		//if (!isPause)
		//{
		sceneMgr.Update();  //�X�V

	//}
		sceneMgr.Draw();    //�`��

	}

	sceneMgr.Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}