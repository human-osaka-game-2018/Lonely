﻿/**
* @file TriggerMovable.h
* @brief TriggerMovableクラスのヘッダファイル
* @author shion-sagawa
*/
#pragma once

#include "TriggerBase.h"

#include <d3dx9math.h>

/**
* @brief 動かせるトリガー関係の処理のクラス
*/
class TriggerMovable : public TriggerBase
{
public:

	TriggerMovable();
	~TriggerMovable();

	/**
	* @brief コンストラクタ(当たり判定がBOXのとき）
	* @param 中心の位置
	* @param BOXの軸の長さ
	*/
	TriggerMovable(D3DXVECTOR3* position, D3DXVECTOR3* boxLength);

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
	* @brief 
	*/
	bool IsCollided() { return m_collides; };

	void SetPosition(D3DXVECTOR3* movableObjectPosition)
	{
		m_position.x = movableObjectPosition->x; 
		m_position.y = movableObjectPosition->y;
		m_position.z = movableObjectPosition->z;

		m_followingPositionExceptY.x = movableObjectPosition->x;
		m_followingPositionExceptY.z = movableObjectPosition->z;
	}

private:

	SimpleTexVertex m_vertices[4] =
	{
		//   x,      y,   z,      color,  tu,  tv
		-2.f,  2.f, 0.f, static_cast<DWORD>(0xffffffff), 0.f, 0.f,
		2.f,  2.f, 0.f, static_cast<DWORD>(0xffffffff), 1.f, 0.f,
		2.f, -2.f, 0.f, static_cast<DWORD>(0xffffffff), 1.f, 1.f,
		-2.f, -2.f, 0.f, static_cast<DWORD>(0xffffffff), 0.f, 1.f

	};

	Texture         m_texture;                 
};
