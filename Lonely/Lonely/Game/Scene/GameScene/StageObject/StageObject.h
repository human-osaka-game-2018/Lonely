/**
* @file StageObject.h
* @brief StageObjectクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

#include "../../../../GameLib/ObjectManager/Object3DBase.h"
#include "../../../../GameLib/CollisionManager/CollisionManager.h"
#include "../../../../GameLib/CollisionManager/CollisionBase/CollisionBox.h"
#include "../../../../GameLib/FBX/FBX.h"
#include "../SharedInformation/SharedInformation.h"

/**
* @brief トリガーの基底クラス
*/
class StageObject : public Object3DBase
{
public:

	StageObject();
	virtual ~StageObject();

	/**
	* @brief 初期化関数
	*/
	bool Initialize();

	/**
	* @brief 解放関数
	*/
	void Finalize();

protected:

	CollisionManager*  m_pCollisionManager;    //!< 当たり判定管理クラスのポインタ
	CollisionBox*      m_pCollision;           //!< 当たり判定の実体
	SharedInformation* m_pSharedInformation;

	D3DXVECTOR3        m_prevPosition;         //!< プレイヤーの位置（フレームで移動する前の）
	bool               m_collides;             //!< 当たっているかどうか
	int                m_stageObjectType;      //!< どのタイプのステージオブジェクトか

	FbxModel           m_fbxModel;
	Model              m_shpere;
	float              m_radius;
	float              m_rotation;

};
