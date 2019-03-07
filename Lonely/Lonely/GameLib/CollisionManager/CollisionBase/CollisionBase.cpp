/**
* @file CollisionBase.h
* @brief CollisionBase�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#include "CollisionBase.h"

CollisionBase::CollisionBase()
{
}

CollisionBase::~CollisionBase()
{
}

CollisionBase::CollisionBase(Object3DBase* owner, int type)
{
	m_owner = owner;
	m_type = type;
}