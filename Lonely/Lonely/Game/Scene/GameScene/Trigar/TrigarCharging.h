/**
* @file TrigarCharging.h
* @brief TrigarChargingクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

#include "TrigarBase.h"

/**
* @brief QRコード関係の処理のクラス
*/
class TrigarCharging : public TrigarBase
{
public:

	TrigarCharging();
	~TrigarCharging();

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

private:

	D3DXVECTOR3 m_position;           //!< プレイヤーの位置（フレームで移動した後の）
	D3DXVECTOR3 m_prevPosition;       //!< プレイヤーの位置（フレームで移動する前の）
	
};
