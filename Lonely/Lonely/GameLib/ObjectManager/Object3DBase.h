/**
* @file Object3DBase.h
* @brief Object3DBase�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "Object.h"

/**
* @brief 3D�I�u�W�F�N�g�̊��ƂȂ�N���X
*/
class Object3DBase : public Object
{
public:

	Object3DBase();
	virtual ~Object3DBase();

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

	bool m_canRender = true;         //!<�@�`��ł��邩�ǂ���
};
