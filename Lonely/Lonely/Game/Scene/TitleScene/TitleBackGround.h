/**
* @file TitleBackGround.h
* @brief TitleBackGround�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../GameLib/DirectX/DirectX.h"
#include "../../../GameLib/2DHelper/2DHelper.h"
#include "../../../GameLib/FBX/Texture.h"


/**
* @brief �^�C�g���̔w�i�֌W�̏������܂Ƃ߂��N���X
*/
class TitleBackGround : public Object2DBase
{
public:
	
	TitleBackGround();
	~TitleBackGround();

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
