/**
* @file CollisionSphere.cpp
* @brief CollisionSphereクラスのソースファイル
* @author shion-sagawa
*/
#pragma once

#include <d3dx9math.h>

#include "CollisionBase.h"

/**
* @brief 球の当たり判定クラス
*/
class CollisionSphere : public CollisionBase
{
public:

	CollisionSphere();
	~CollisionSphere();

	D3DXVECTOR3 GetCenter() { return m_center; }

	float GetRadius() { return m_radius; }

private:

	D3DXVECTOR3 m_center;    //!< 中心座標
	float       m_radius;    //!< 半径

};
