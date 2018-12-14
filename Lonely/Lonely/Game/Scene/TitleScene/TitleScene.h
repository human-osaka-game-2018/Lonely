/**
* @file TitleScene.h
* @brief TitleScene�N���X�̃w�b�_�t�@�C��
* @author ����@�k��
*/

#pragma once
#include "../../../GameLib/SceneManager/SceneBase/SceneBase.h"
#include "TitleScene.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "TitleMenu1.h"
#include "TitleMenu2.h"
#include "Cursor.h"

/**
* @brief �^�C�g���V�[���̃N���X
*/
class TitleScene : public SceneBase
{
public:

	TitleScene();
	~TitleScene();

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