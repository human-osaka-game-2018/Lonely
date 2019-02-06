/**
* @file CollisionBox.cpp
* @brief CollisionBoxクラスのソースファイル
* @author shion-sagawa
*/
#include "CollisionBox.h"
#include "../EnumCollision/Enum_CollisionType.h"
#include "../../ObjectManager/Object3DBase.h"

CollisionBox::CollisionBox(Object* owner, int type)
{
	m_owner = owner;
	m_type = type;
	m_shape = BOX;

	m_normaDirect[0] = { 1.0f, 0.f , 0.f  };
	m_normaDirect[1] = { 0.f , 1.0f, 0.f  };
	m_normaDirect[2] = { 0.f , 0.f , 1.0f };

	m_length[0] = 0.5f;
	m_length[1] = 0.5f;
	m_length[2] = 0.5f;
}

CollisionBox::CollisionBox(Object* owner, int type, D3DXVECTOR3* length)
{
	m_owner = owner;
	m_type = type;
	m_shape = BOX;

	m_normaDirect[0] = { 1.0f, 0.f , 0.f };
	m_normaDirect[1] = { 0.f , 1.0f, 0.f };
	m_normaDirect[2] = { 0.f , 0.f , 1.0f };

	m_length[0] = length->x;
	m_length[1] = length->y;
	m_length[2] = length->z;
}

CollisionBox::~CollisionBox()
{
}

D3DXVECTOR3 CollisionBox::GetDirect(int elem)
{
	return m_normaDirect[elem];
}

FLOAT CollisionBox::GetLength(int elem)
{
	return m_length[elem];
}

D3DXVECTOR3 CollisionBox::GetPosition()
{
	Object3DBase* pObject3D = dynamic_cast<Object3DBase*>(m_owner);

	
	/*if (this->m_type == PLAYER)
	{
		this->m_owner 
	}
	else if (this->m_type == ENEMY)
	{

	}
	else if (this->m_type == STAGE_OBJECT)
	{

	}
	else if (this->m_type == TRIGGER)
	{

	}*/

	return pObject3D->GetPosition();;
}

D3DXVECTOR3 CollisionBox::GetFollowingPositionExceptY()
{
	Object3DBase* pObject3D = dynamic_cast<Object3DBase*>(m_owner);

	return pObject3D->GetFollowingPositionExceptY();

}
