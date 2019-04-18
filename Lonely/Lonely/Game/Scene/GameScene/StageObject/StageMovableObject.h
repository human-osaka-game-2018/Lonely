/**
* @file StageMovableObject.h
* @brief StageMovableObjectクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "StageObject.h"

#include <d3dx9math.h>

#include "Scene/GameScene/Trigger/TriggerMovable.h"
#include "CollisionManager/CollisionManager.h"
#include "CollisionManager/CollisionBase/CollisionBase.h"
#include "Scene/GameScene/Player/Sumahoneko.h"

/**
* @brief トリガーの基底クラス
*/
class StageMovableObject : public StageObject
{
public:

	StageMovableObject();
	~StageMovableObject();

	StageMovableObject(D3DXVECTOR3* position, D3DXVECTOR3* myBoxLength, D3DXVECTOR3* triggerBoxLength, Sumahoneko* pSumahoneko);

	/**
	* @brief 初期化関数
	*/
	bool Initialize();

	/**
	* @brief 解放関数
	*/
	void Finalize();

	/**
	* @brief 更新関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();

	/**
	* @brief フレームで処理した移動量を、衝突していたので戻す関数
	*/
	void RevertPosition();

	Sumahoneko* GetPlayer() { return m_pSumahoneko; };

private:

	SimpleTexVertex m_vertices[4] =
	{
		//   x,      y,   z,      color,  tu,  tv
		-2.f,  2.f, 0.f, static_cast<DWORD>(0xffffffff), 0.f, 0.f,
		2.f,  2.f, 0.f, static_cast<DWORD>(0xffffffff), 1.f, 0.f,
		2.f, -2.f, 0.f, static_cast<DWORD>(0xffffffff), 1.f, 1.f,
		-2.f, -2.f, 0.f, static_cast<DWORD>(0xffffffff), 0.f, 1.f

	};

	TriggerMovable* m_trigger;
	Texture        m_texture;
	Sumahoneko*    m_pSumahoneko;
};
