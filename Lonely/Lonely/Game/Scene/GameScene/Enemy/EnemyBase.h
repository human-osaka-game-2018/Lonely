/**
* @file EnemyBase.h
* @brief EnemyBaseクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object3DBase.h"

#include <d3dx9math.h>

#include "CollisionManager/CollisionManager.h"
#include "CollisionManager/CollisionBase/CollisionBase.h"

/**
* @brief トリガーの基底クラス
*/
class EnemyBase : public Object3DBase
{
public:

	EnemyBase();
	virtual ~EnemyBase();

	/**
	* @brief 初期化関数
	*/
	bool Initialize();

	/**
	* @brief 解放関数
	*/
	void Finalize();

	int GetTriggerType() { return m_triggerType; }

protected:

	CollisionManager* m_pCollisionManager;    //!< 当たり判定管理クラスのポインタ
	CollisionBase*    m_pCollision;           //!< 当たり判定の実体

	D3DXVECTOR3       m_prevPosition;         //!< フレームで移動する前の位置
	int               m_triggerType;           //!< どのトリガーなのか
	bool              m_collides;             //!< 当たっているかどうか

};
