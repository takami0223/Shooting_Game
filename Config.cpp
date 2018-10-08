#include "Config.h"
#include "define.h"
#include "Keyboard.h"
#include "DxLib.h"

Config::Config( ISceneChanger* changer ) : BaseScene( changer )
{
}

//������
void Config::Initialize()
{
	SetDrawArea( 0, 0, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT );
	mImageHandle = LoadGraph( "../images/thiko.jpg" );    //�摜�̃��[�h
}

//�X�V
void Config::Update()
{
	if (Keyboard_Get( KEY_INPUT_ESCAPE ) == 1)
	{ //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene( eScene_Menu );//�V�[�������j���[�ɕύX
	}
}

//�`��
void Config::Draw()
{
	//BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString( 0, 0, "�ݒ��ʂł��B", GetColor( 255, 255, 255 ) );
	DrawString( 0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor( 255, 255, 255 ) );
}