/**
* @file CollisionBase.h
* @brief CollisionBase�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/
#pragma once

#include "../../ObjectManager/Object.h"
#include "../EnumCollision/Enum_CollisionShape.h"

/**
* @brief �����蔻��̌`�̊��N���X
*/
class CollisionBase
{
public:

	CollisionBase();
	virtual ~CollisionBase();

	/**
	* @brief �Փ˂��N�����Ă���Ƃ��̋������s���֐�
	*/
	void OnCollision(CollisionBase* collider,bool collisionStateIsRiding);


	int GetType() { return m_type; }
	void SetType(int type) { m_type = type; }

	int GetShape() { return m_shape; }

	Object* GetOwner() { return m_owner; }

	
protected:
	
	Object*       m_owner;    //!< �I�[�i�[�̃A�h���X
	int           m_type;     //!< �ǂ̓����蔻��O���[�v�ɑ����邩
	int           m_shape;    //!< �ǂ�Ȍ`�œ����蔻����Ƃ邩
};