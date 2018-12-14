/**
* @file MenuGameEnd.cpp
* @brief MenuGameEnd�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/Texture.h"


/**
* @brief �^�C�g�����j���iGAME END�j�̏������܂Ƃ߂��N���X
*/
class MenuGameEnd : public Object2DBase
{
public:

	MenuGameEnd();
	~MenuGameEnd();


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

};