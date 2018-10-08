#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"
#include "Pause.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() :
	mNextScene( eScene_None ) //���̃V�[���Ǘ��ϐ�
{
	mScene = (BaseScene*) new Menu( this );
}

//������
void SceneMgr::Initialize()
{
	temp_flag = false;
	mScene->Initialize();
}

//�I������
void SceneMgr::Finalize()
{
	mScene->Finalize();
}

//�X�V
void SceneMgr::Update()
{
	//���̃V�[�����Z�b�g����Ă�����
	if (mNextScene != eScene_None)
	{
		//if (mNextScene == eScene_Pause)
		//{
			//temp_mScene = mScene;
			//temp_flag = true;
		//}
		////else
		//{
		mScene->Finalize();//���݂̃V�[���̏I�����������s
		delete mScene;
	//}


		switch (mNextScene)
		{       //�V�[���ɂ���ď����𕪊�
			case eScene_Menu:        //���̉�ʂ����j���[�Ȃ�
				mScene = (BaseScene*) new Menu( this );   //���j���[��ʂ̃C���X�^���X�𐶐�����
				break;//�ȉ���

			case eScene_Game:
				//if (temp_flag)
				//{
					//mScene = temp_mScene;
					//temp_flag = false;
				//}
				//else
				//{
				mScene = (BaseScene*) new Game( this );
			//}
				break;

			case eScene_Config:
				mScene = (BaseScene*) new Config( this );
				break;

			case eScene_Pause:
				mScene = (BaseScene*) new Pause( this );
				break;

		}
		mNextScene = eScene_None;    //���̃V�[�������N���A
		mScene->Initialize();    //�V�[����������
	}

	mScene->Update(); //�V�[���̍X�V
}

//�`��
void SceneMgr::Draw()
{
	mScene->Draw(); //�V�[���̕`��
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr::ChangeScene( eScene NextScene )
{
	mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}