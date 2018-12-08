/**
* @file MenuPressEnter.h
* @brief MenuPressEnter�N���X�̃w�b�_�t�@�C��
* @author ����@�k��
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/Texture.h"


/**
* @brief �^�C�g�����j���iPRESS�@ENTER�j�̏������܂Ƃ߂��N���X
*/
class MenuPressEnter : public Object2DBase
{
public:

	MenuPressEnter();
	~MenuPressEnter();


	/**
	* @brief ����������֐�
	* @return ����������肭�ł��Ă��Ȃ���FALSE 
	*/
	bool Initialize();

	/**
	* @brief �������֐�
	*/
	void Finalize();

	/**
	* @brief ����֐�
	* @param �^�C�g�����j���[�̉��Ԃ̃X�e�b�v��
	*/
	void Update(int step);

	/**
	* @brief �`��֐�
	*/
	void Render();

private:

	int            frameCount = 0;     //!< �t���[���𐔂��邽�߂̕ϐ�
};
