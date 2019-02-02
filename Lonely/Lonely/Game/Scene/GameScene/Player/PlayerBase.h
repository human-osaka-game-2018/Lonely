/**
* @file PlayerBase.h
* @brief PlayerBaseクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

#include "../../../../GameLib/ObjectManager/Object3DBase.h"
#include "../../../../GameLib/CollisionManager/CollisionManager.h"
#include "../../../../GameLib/CollisionManager/CollisionBase/CollisionBase.h"

/**
* @brief トリガーの基底クラス
*/
class PlayerBase : public Object3DBase
{
public:

	PlayerBase();
	virtual ~PlayerBase();

	/**
	* @brief 初期化関数
	*/
	bool Initialize();

	/**
	* @brief 解放関数
	*/
	void Finalize();

	int GetPlayerType() { return m_playerType; }

protected:

	CollisionManager * m_pCollisionManager;   //!< 当たり判定管理クラスのポインタ
	CollisionBase*    m_pCollision;           //!< 当たり判定の実体

	D3DXVECTOR3       m_prevPosition;         //!< プレイヤーの位置（フレームで移動する前の）
	int               m_playerType;           //!< プレイヤーとして操作しているキャラは何なのか
};
