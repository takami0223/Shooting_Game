//#ifndef _CONFIG_H_
//#define _CONFIG_H_

#pragma once

#include "BaseScene.h"

//�ݒ��ʃN���X
class Config : public BaseScene
{

public:
	Config(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h
	//void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

};

//#endif // !_CONFIG_H_


