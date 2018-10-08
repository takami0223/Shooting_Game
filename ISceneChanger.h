//#ifndef _ISCENECHANGER_H_
//#define _ISCENECHANGER_H_

#pragma once

typedef enum
{
	eScene_Menu,    //���j���[���
	eScene_Game,    //�Q�[�����
	eScene_Config,  //�ݒ���
	eScene_Pause,   //�{�[�Y���

	eScene_None,    //����
} eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger
{
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene( eScene NextScene ) = 0;//�w��V�[���ɕύX����
};

//#endif // !_ISCENECHANGER_H_