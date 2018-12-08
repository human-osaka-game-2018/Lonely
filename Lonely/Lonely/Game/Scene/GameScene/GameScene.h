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

	GameScene();
	~GameScene();

	/**
	* @brief �������֐� 
	*/
	bool Initialize();

	/**
	* @brief ����֐�
	*/
	void Finalize();

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
