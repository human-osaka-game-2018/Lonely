/**
* @file TitleBackGround.h
* @brief TitleBackGround�N���X�̃w�b�_�t�@�C��
* @author ����@�k��
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object.h"
#include "../../../GameLib/DirectX/DirectX.h"
#include "../../../GameLib/2DHelper/2DHelper.h"
#include "../../../GameLib/FBX/VertexBuffer.h"


/**
* @brief �^�C�g���̔w�i�֌W�̏������܂Ƃ߂��N���X
*/
class TitleBackGround : public Object
{
public:
	
	TitleBackGround();
	~TitleBackGround();

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

	Texture       m_texture;
	VertexBuffer  m_vertexBuffer;
};
