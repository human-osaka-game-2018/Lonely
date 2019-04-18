/**
* @file TriggerBase.h
* @brief TriggerBaseクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object3DBase.h"

#include <d3dx9math.h>

#include "CollisionManager/CollisionManager.h"
#include "CollisionManager/CollisionBase/CollisionBase.h"
#include "../SharedInformation/SharedInformation.h"

/**
* @brief トリガーの基底クラス
*/
class TriggerBase : public Object3DBase
{
public:

	TriggerBase();
	virtual ~TriggerBase();

	/**
	* @brief 初期化関数
	*/
	bool Initialize();

	/**
	* @brief 解放関数
	*/
	void Finalize();

	/**
	* @brief このトリガーがプレイヤーに当たっているときの関数
	*/
	void CollidesWithPlayer();


	int GetTriggerType() { return m_triggerType; }

protected:

	SharedInformation* m_pSharedInformation;    //!< 情報共有クラスのポインタ
	CollisionManager*  m_pCollisionManager;     //!< 当たり判定管理クラスのポインタ
	CollisionBase*     m_pCollision;            //!< 当たり判定の実体
					   						    
	D3DXVECTOR3        m_prevPosition;          //!< プレイヤーの位置（フレームで移動する前の）
	int                m_triggerType;            //!< どのトリガーなのか
	bool               m_collides;              //!< 当たっているかどうか

};
