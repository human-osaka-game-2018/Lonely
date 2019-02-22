/**
* @file DataSelectScene.h
* @brief DataSelectScene�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/SceneManager/SceneBase/SceneBase.h"
#include "SelectCursorInformation/SelectCursorInformation.h"

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

	SelectCursorInformation m_selectCursorInformation;

};
