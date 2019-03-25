/**
* @file CollisionBase.h
* @brief CollisionBase�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../ObjectManager/Object3DBase.h"

/**
* @brief
*/
class CollisionBase
{
public:

	CollisionBase() = delete;
	~CollisionBase();

	/**
	* @brief ��������̃R���X�g���N�^
	* @param �I�[�i�[�̃A�h���X
	* @param �ǂ̓����蔻��O���[�v�ɑ����邩
	*/
	CollisionBase(Object3DBase* owner, int type);

	int GetType() { return m_type; }

private:
	
	Object3DBase* m_owner;    //!< �I�[�i�[�̃A�h���X
	int           m_type;     //!< �ǂ̓����蔻��O���[�v�ɑ����邩

};