/**
* @file CollisionManager.h
* @brief CollisionManagerクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <vector>
#include <d3dx9math.h>

#include "CollisionBase/CollisionBase.h"
#include "EnumCollision/Enum_CollisionType.h"

/**
* @brief オブジェクトを管理するクラス
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
	void RegisterCollision(CollisionBase* pCollision);

	/**
	* @brief オブジェクトを解放する関数
	*/
	void ReleaseCollision();

	/**
	* @brief 当たり判定を行うチェックする関数
	* @param 判定されるクラスのポインタ
	* @param 判定されるクラスのポインタ
	* @return 当たっていたらTRUEを返す
	*/
	bool DetectsCollision(CollisionBase* colliderA, CollisionBase* colliderB);

	/**
	* @brief 球と球の当たり判定を行う関数
	* @param 判定されるクラスのポインタ
	* @param 判定されるクラスのポインタ
	* @return 当たっていたらTRUEを返す
	*/
	bool SphereCollidesWithSphere(CollisionBase* colliderA, CollisionBase* colliderB);

	/**
	* @brief 直方体と直方体の当たり判定を行う関数
	* @param 判定されるクラスのポインタ
	* @param 判定されるクラスのポインタ
	* @return 当たっていたらTRUEを返す
	*/
	bool BoxCollidesWithBoxXZ(CollisionBase* box1, CollisionBase* box2);

	/**
	* @brief 直方体と直方体の当たり判定を行う関数
	* @param 判定されるクラスのポインタ
	* @param 判定されるクラスのポインタ
	* @return 当たっていたらTRUEを返す
	*/
	bool BoxCollidesWithBoxXYZ(CollisionBase* box1, CollisionBase* box2);


private:

	/**
	* @brief どれと当たり判定を行うか（使う際に変えてもらう必要がある）
	*/
	int collisionTargetType[5] =
	{
		1 << PLAYER_WITH_OBJECT | 1 << ENEMY        | 1 << STAGE_OBJECT | 1 << TRIGGER,     // PLAYERタイプが判定を行うグループ
		1 << ENEMY              | 1 << STAGE_OBJECT | 1 << TRIGGER,                         // PLAYER_WITH_OBJECTタイプが判定を行うグループ
		1 << ENEMY              | 1 << STAGE_OBJECT,                                        // ENEMYタイプが判定を行うグループ
		1 << STAGE_OBJECT                                                                   // OBJECTタイプが判定を行うグループ
		                                                            	                    // TRIGGERタイプが判定を行うグループ
	};

	/**
	* @brief 分離軸に投影された軸成分から投影線分の長さを出す
	* @param 
	* @param 
	* @param 
	* @param 
	* @return 投影した線分の長さを返す
	*/
	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);
	
	bool m_isRiding;

	std::vector<CollisionBase*> m_pCollisionVec[COLLISION_TYPE_MAX];    //!< 当たり判定オブジェクトを持つベクター配列

};
