//#ifndef _SCENEMGR_H_
//#define _SCENEMGR_H_

#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"

class SceneMgr : public ISceneChanger, Task
{

private:
	BaseScene * mScene;      //�V�[���Ǘ��ϐ�
	BaseScene *temp_mScene;
	eScene mNextScene;       //���̃V�[���Ǘ��ϐ�
	bool temp_flag;

public:
	SceneMgr();
	void Initialize() override;//������
	void Finalize() override;//�I������
	void Update() override;//�X�V
	void Draw() override;//�`��

	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene( eScene NextScene ) override;

};

//#endif // !_SCENEMGR_H_