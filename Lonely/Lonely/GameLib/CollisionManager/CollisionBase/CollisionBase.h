/**
* @file CollisionBase.h
* @brief CollisionBaseクラスのヘッダファイル
* @author shion-sagawa
*/
#pragma once

#include "../../ObjectManager/Object.h"
#include "../EnumCollision/Enum_CollisionShape.h"

/**
* @brief 当たり判定の形の基底クラス
*/
class CollisionBase
{
public:

	CollisionBase();
	virtual ~CollisionBase();

	/**
	* @brief 衝突を起こしているときの挙動を行う関数
	*/
	void OnCollision(CollisionBase* collider,bool collisionStateIsRiding);


	int GetType() { return m_type; }
	void SetType(int type) { m_type = type; }

	int GetShape() { return m_shape; }

	Object* GetOwner() { return m_owner; }

	
protected:
	
	Object*       m_owner;    //!< オーナーのアドレス
	int           m_type;     //!< どの当たり判定グループに属するか
	int           m_shape;    //!< どんな形で当たり判定をとるか
};