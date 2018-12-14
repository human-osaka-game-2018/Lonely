/**
* @file TitleLogo.h
* @brief TitleLogo�N���X�̃w�b�_�t�@�C��
* @author ����@�k��
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../GameLib/DirectX/DirectX.h"
#include "../../../GameLib/2DHelper/2DHelper.h"
#include "../../../GameLib/FBX/VertexBuffer.h"
#include "../../../GameLib/FBX/Texture.h"

/**
* @brief �^�C�g�����S�̏������܂Ƃ߂��N���X
*/
class TitleLogo : public Object2DBase
{
public:

	TitleLogo();
	~TitleLogo();


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

	float logoWidth = 30.f;            //!< �^�C�g�����S�̒��S�_����̉���
	float logoHeight = 20.f;           //!< �^�C�g�����S�̒��S�_����̏c��
};
