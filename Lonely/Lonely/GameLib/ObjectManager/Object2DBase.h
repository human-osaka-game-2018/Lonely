/**
* @file Object2DBase.h
* @brief Object2DBase�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "Object.h"
#include "../2DHelper/2DHelper.h"
#include "../FBX/Texture.h"

/**
* @brief �QD�I�u�W�F�N�g�̊��ƂȂ�N���X
*/
class Object2DBase: public Object
{
public:

	Object2DBase();
	virtual ~Object2DBase();

	/**
	* @brief ���������s���֐�
	*/
	virtual bool Initialize();

	/**
	* @brief ������s���֐�
	*/
	virtual void Finalize();

	/**
	* @brief ����̍X�V���s���֐�
	*/
	virtual void Update();

	/**
	* @brief �`����s���֐�
	*/
	virtual void Render();

protected:

	Texture         m_texture;
	Simple2DVertex  m_vertices[4]; //!< ��`��4���_
	bool canRender = true;         //!<�@�`��ł��邩�ǂ���
};
