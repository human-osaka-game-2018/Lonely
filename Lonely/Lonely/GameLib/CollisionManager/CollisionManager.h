/**
* @file CollisionManager.h
* @brief CollisionManagerクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <vector>

#include "CollisionBase/CollisionBase.h"

/**
* @brief 当たり判定のグループ分け（使う際に変えてもらう必要がある）
*/
enum CollisionType
{
	PLAYER,
	ENEMY,
	MOVE_OBJ,
	DONT_MOVE_OBJ,
	COLLISION_TYPE_MAX,
};

/**
* オブジェクトを管理するクラス
*/
class CollisionManager
{
public:

	CollisionManager();
	~CollisionManager();

	/**
	* @brief インスタンスを生成する関数
	*/
	void Initialize();

	/**
	* @brief インスタンスを破棄する関数
	*/
	void Finalize();

	/**
	* @brief 操作関数
	*/
	void Update();

	/**
	* @brief オブジェクトを登録する関数
	* @param 登録したい派生クラスのポインタ
	*/
	void RegisterCollision(CollisionBase*);

	/**
	* @brief オブジェクトを解放する関数
	*/
	void ReleaseCollision();

private:

	std::vector<CollisionBase*> m_pCollisionVec[COLLISION_TYPE_MAX];    //!< 当たり判定オブジェクトを持つベクター配列

	/**
	* @brief どれと当たり判定を行うか（使う際に変えてもらう必要がある）
	*/
	int collisionTargetType[] =
	{
		1 << PLAYER | 1 << ENEMY | 1 << MOVE_OBJ | 1 << DONT_MOVE_OBJ,	// Player
		1 << ENEMY | 1 << MOVE_OBJ | 1 << DONT_MOVE_OBJ,	            // Enemy
		1 << MOVE_OBJ | 1 << DONT_MOVE_OBJ,                             // MoveObj
		1 << DONT_MOVE_OBJ,                                             // DontMoveObj
	};

};
