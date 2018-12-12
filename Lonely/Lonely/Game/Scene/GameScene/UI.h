/**
* @file UI.h
* @brief UI�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../GameLib/2DHelper/2DHelper.h"

/**
* @brief UI�̏������܂Ƃ߂��N���X
*/
class UI : public Object2DBase
{
public:

	UI();
	~UI();


	/**
	* @brief ����������֐�
	* @param
	*/
	bool Initialize();

	/**
	* @brief �������֐�
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

	float logoWidth = 100.f;            //!< �^�C�g�����S�̒��S�_����̉���
	float logoHeight = 100.f;           //!< �^�C�g�����S�̒��S�_����̏c��
};
