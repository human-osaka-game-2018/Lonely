/**
* @file DataSelectScene.h
* @brief DataSelectScene�N���X�̃w�b�_�t�@�C��
* @author ����
*/

#pragma once

#include "../../../GameLib/SceneManager/SceneBase/SceneBase.h"

/**
* @brief �f�[�^�Z���N�g�V�[���̃N���X
*/
class DataSelectScene : public SceneBase
{
public:

	DataSelectScene();
	~DataSelectScene();
	
	/**
	* @brief ����������֐�
	*/
	bool Initialize();

	/**
	* @brief �������֐�
	*/
	void Finalize();

	/**
	* @brief ������X�V����֐�
	*/
	void Update();

	/**
	* @brief �`��֐�
	*/
	void Render();

private:

};

DataSelectScene::DataSelectScene()
{
}

DataSelectScene::~DataSelectScene()
{
}

bool DataSelectScene::Initialize()
{
}

void DataSelectScene::Finalize()
{
}

void DataSelectScene::Update()
{

}

void DataSelectScene::Render()
{

}