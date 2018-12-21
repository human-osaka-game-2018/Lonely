/**
* @file CollisionBase.h
* @brief CollisionBaseクラスのヘッダファイル
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