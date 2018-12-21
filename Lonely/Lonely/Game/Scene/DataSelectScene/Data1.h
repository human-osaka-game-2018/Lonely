/**
* @file Data1.h
* @brief Data1�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../GameLib/DirectX/DirectX.h"

/**
* @brief �f�[�^�֌W�̏������܂Ƃ߂��N���X
*/
class Data1 : public Object2DBase
{
public:

	Data1();
	~Data1();

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
	*/
	void Update();

	/**
	* @brief �`��֐�
	*/
	void Render();

private:

};
