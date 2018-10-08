#include "Pause.h"
#include "define.h"
#include "Keyboard.h"
#include "DxLib.h"

Pause::Pause( ISceneChanger* changer ) : BaseScene( changer )
{
}

//������
void Pause::Initialize()
{
	SetDrawArea( 0, 0, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT );
	mImageHandle = LoadGraph( "../images/�N���t�B�\��.jpg" );    //�摜�̃��[�h
}

//�X�V
void Pause::Update()
{
	if (Keyboard_Get( KEY_INPUT_DOWN ) == 1)
	{//G�L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eMenu_Num;
		//mSceneChanger->ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
	}
	if (Keyboard_Get( KEY_INPUT_UP ) == 1)
	{//C�L�[��������Ă�����
		NowSelect = (NowSelect - 1) % eMenu_Num;
		if (NowSelect < 0) NowSelect = eMenu_Num - 1;
		//mSceneChanger->ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
	}
	if (Keyboard_Get( KEY_INPUT_RETURN ) == 1)
	{
		switch (NowSelect)
		{
			case eMenu_Game:
				mSceneChanger->ChangeScene( eScene_Game );
				break;

			case eMenu_Config:
				mSceneChanger->ChangeScene( eScene_Config );
				break;

			case eMenu_Title:
				mSceneChanger->ChangeScene( eScene_Menu );
				break;

			default:
				break;
		}
	}

	/*
	if (Keyboard_Get( KEY_INPUT_ESCAPE ) == 1)
	{ //Esc�L�[��������Ă�����
		//delete this;
		mSceneChanger->ChangeScene( eScene_Game );//�V�[�������j���[�ɕύX
	}
	*/

}

//�`��
void Pause::Draw()
{
	//BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
					  /*
					  DrawString(0, 0, "���j���[��ʂł��B", GetColor(255, 255, 255));
					  DrawString(0, 20, "G�L�[�������ƃQ�[����ʂɐi�݂܂��B", GetColor(255, 255, 255));
					  DrawString(0, 40, "C�L�[�������Ɓ@�ݒ��ʂɐi�݂܂��B", GetColor(255, 255, 255));
					  */
	DrawString( 200, 150, "�|�[�Y��ʂł��B", GetColor( 255, 255, 255 ) );
	DrawString( 200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor( 255, 255, 255 ) );
	DrawString( 280, GAME_Y, "�n�߂���", GetColor( 255, 255, 255 ) );
	DrawString( 280, CONFIG_Y, "�ݒ�", GetColor( 255, 255, 255 ) );
	DrawString( 280, TITLE_Y, "�^�C�g���ɖ߂�", GetColor( 255, 255, 255 ) );

	int y = 0;

	switch (NowSelect)
	{//���݂̑I����Ԃɏ]���ď����𕪊�
		case eMenu_Game://�Q�[���I�𒆂Ȃ�
			y = GAME_Y;    //�Q�[���̍��W���i�[
			break;
		case eMenu_Config://�ݒ�I�𒆂Ȃ�
			y = CONFIG_Y;    //�ݒ�̍��W���i�[
			break;

		case eMenu_Title:
			y = TITLE_Y;
			break;
	}
	DrawString( 250, y, "��", GetColor( 255, 255, 255 ) );
}