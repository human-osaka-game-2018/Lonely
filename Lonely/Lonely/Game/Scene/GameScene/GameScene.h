/**
* @file GameScene.h
* @brief GameScene�N���X�̃w�b�_�t�@�C��
* @author ����
*/

#pragma once
#include"../../../GameLib/SceneManager/SceneBase/SceneBase.h"

/**
* @brief �Q�[���V�[���̃N���X
*/
class GameScene : public SceneBase
{
public:

	/**
	* @brief �R���X�g���N�^
	*/
	GameScene();

	/**
	* @brief�f�X�g���N�^
	*/
	~GameScene();

	/**
	* @brief ����֐�
	*/
	void Update();

	/**
	* @brief �`��֐�
	*/
	void Render();

private:
	
};

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

//void GameScene::Run() 
//{
//	
//}

void GameScene::Update()
{
	//�L�[Update
	//�I�u�W�F�N�g�̃R���g���[��
	//�J�����̃R���g���[��
}

void GameScene::Render()
{
	//�I�u�W�F�N�g�̃����_�[
}