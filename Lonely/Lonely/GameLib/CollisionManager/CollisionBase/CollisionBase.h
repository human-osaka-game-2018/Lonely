/**
* @file CollisionBase.h
* @brief CollisionBaseクラスのヘッダファイル
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
	* @brief 引数ありのコンストラクタ
	* @param オーナーのアドレス
	* @param どの当たり判定グループに属するか
	*/
	CollisionBase(Object3DBase* owner, int type);

	int GetType() { return m_type; }

private:
	
	Object3DBase* m_owner;    //!< オーナーのアドレス
	int           m_type;     //!< どの当たり判定グループに属するか

};