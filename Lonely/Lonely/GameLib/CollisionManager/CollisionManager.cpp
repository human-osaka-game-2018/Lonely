/**
* @file CollisionManager.cpp
* @brief CollisionManagerクラスのソースファイル
* @author shion-sagawa
*/

#include "CollisionManager.h"

#include <d3dx9math.h>

#include "CollisionBase\CollisionBase.h"
#include "CollisionBase\CollisionBox.h"
#include "CollisionBase\CollisionSphere.h"


CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	Finalize();
}

//初期化する
void CollisionManager::Initialize()
{
}

//解放する
void CollisionManager::Finalize()
{
	ReleaseCollision();
}

//登録する
void CollisionManager::RegisterCollision(CollisionBase* pCollision)
{
	m_pCollisionVec[pCollision->GetType()].push_back(pCollision);
}

//解放する
void CollisionManager::ReleaseCollision()
{
	for (int i = 0; i < COLLISION_TYPE_MAX; ++i)
	{
		//Vector配列の要素が０なら関数から抜ける
		if (m_pCollisionVec[i].size() == 0)
		{
			continue;
		}

		//要素数を０にする
		m_pCollisionVec[i].clear();
		//キャパシティーを０にする
		m_pCollisionVec[i].shrink_to_fit();
	}
}

//毎フレーム更新する
void CollisionManager::Update()
{
	for (int i = 0; i < COLLISION_TYPE_MAX; i++)
	{
		//縦の中身がない場合は戻す
		if (m_pCollisionVec[i].size() == 0)
		{
			continue;
		}

		for (int j = 0; j < COLLISION_TYPE_MAX; j++)
		{
			//横の中身がない場合は戻す
			if (m_pCollisionVec[j].size() == 0)
			{
				continue;
			}

			//collisionTargetTypeで指定したグループとだけ当たり判定をチェックする
			if (((collisionTargetType[i]) & ((1 << (m_pCollisionVec[j][0]->GetType())))) == false)
			{
				continue;
			}

			//縦の中身を回す
			for (unsigned int k = 0; k < m_pCollisionVec[i].size(); k++)
			{
				//横の中身を回す
				for (unsigned int l = 0; l < m_pCollisionVec[j].size(); l++)
				{
					////自分と自分を判定しないため
					if (m_pCollisionVec[i][k] == m_pCollisionVec[j][l])
					{
						continue;
					}

					//当たり判定をチェックする
					if (this->DetectsCollision(m_pCollisionVec[i][k], m_pCollisionVec[j][l]))
					{
						m_pCollisionVec[i][k]->OnCollision(m_pCollisionVec[j][l], m_isRiding);
						m_pCollisionVec[j][l]->OnCollision(m_pCollisionVec[i][k], m_isRiding);
					}
				}
			}
		}
	}
}

bool CollisionManager::DetectsCollision(CollisionBase* colliderA, CollisionBase* colliderB)
{
	int shapeA = colliderA->GetShape();
	int shapeB = colliderB->GetShape();

	bool isCollidesXYZ = false;
	bool isCollidesXZ = false;

	if ((shapeA == SPHERE) && (shapeB == SPHERE))
	{
		isCollidesXYZ = SphereCollidesWithSphere(colliderA, colliderB);
	}
	else if ((shapeA == BOX) && (shapeB == BOX))
	{
		isCollidesXZ = BoxCollidesWithBoxXZ(colliderA, colliderB);
		isCollidesXYZ = BoxCollidesWithBoxXYZ(colliderA, colliderB);

		//衝突判定した結果、上に乗っているときの処理
		if ((isCollidesXZ == false) && (isCollidesXYZ == true))
		{
			m_isRiding = true;
		}
		else
		{
			m_isRiding = false;
		}
	}
	else
	{
		isCollidesXYZ = false;
	}

	return isCollidesXYZ;
}

//球と球の当たり判定
bool CollisionManager::SphereCollidesWithSphere(CollisionBase* colliderA, CollisionBase* colliderB)
{
	//BaseからSphereへのダウンキャストを行う
	CollisionSphere* sphereA = dynamic_cast<CollisionSphere*>(colliderA);
	CollisionSphere* sphereB = dynamic_cast<CollisionSphere*>(colliderB);

	//半径を取得
	float radiusA = sphereA->GetRadius();
	float radiusB = sphereB->GetRadius();
	//中心座標を取得
	D3DXVECTOR3 centerA = sphereA->GetCenter();
	D3DXVECTOR3 centerB = sphereB->GetCenter();

	//球AとBの中心座標の差を計算する
	D3DXVECTOR3 difference;
	difference.x = centerA.x - centerB.x;
	difference.y = centerA.y - centerB.y;
	difference.z = centerA.z - centerB.z;

	//三平方の定理で、ベクトルの長さを計算する
	//差分ベクトルの長さは、２点間の距離
	float distanceFromCenterToCenter = sqrtf(
		difference.x * difference.x + 
		difference.y * difference.y + 
		difference.z * difference.z);

	//距離が半径の輪より大きければ当たっていない
	if (distanceFromCenterToCenter >  (radiusA + radiusB))
	{
		return false;
	}

	return true;
}

// 分離軸に投影された軸成分から投影線分長を算出
float CollisionManager::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = static_cast<float>(fabs(D3DXVec3Dot(Sep, e1)));
	float r2 = static_cast<float>(fabs(D3DXVec3Dot(Sep, e2)));
	float r3 = e3 ? static_cast<float>(fabs(D3DXVec3Dot(Sep, e3))) : 0;

	return r1 + r2 + r3;
}

// 直方体と直方体の当たり判定
bool CollisionManager::BoxCollidesWithBoxXZ(CollisionBase* collider1, CollisionBase* collider2)
{
	CollisionBox* box1 = dynamic_cast<CollisionBox*>(collider1);
	CollisionBox* box2 = dynamic_cast<CollisionBox*>(collider2);

	// 各方向ベクトルの確保
	// （N***:標準化方向ベクトル）
	D3DXVECTOR3 NAe1 = box1->GetDirect(0), Ae1 = NAe1 * box1->GetLength(0);
	D3DXVECTOR3 NAe2 = box1->GetDirect(1), Ae2 = NAe2 * box1->GetLength(1);
	D3DXVECTOR3 NAe3 = box1->GetDirect(2), Ae3 = NAe3 * box1->GetLength(2);
	D3DXVECTOR3 NBe1 = box2->GetDirect(0), Be1 = NBe1 * box2->GetLength(0);
	D3DXVECTOR3 NBe2 = box2->GetDirect(1), Be2 = NBe2 * box2->GetLength(1);
	D3DXVECTOR3 NBe3 = box2->GetDirect(2), Be3 = NBe3 * box2->GetLength(2);
	D3DXVECTOR3 Interval = box1->GetFollowingPositionExceptY() - box2->GetFollowingPositionExceptY();

	// 分離軸 : Ae1
	float rA = D3DXVec3Length(&Ae1);
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NAe1)));
	if (L > rA + rB)
		return false; // 衝突していない

	// 分離軸 : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NAe2)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NAe3)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NBe1)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NBe2)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NBe3)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

// 直方体と直方体の当たり判定
bool CollisionManager::BoxCollidesWithBoxXYZ(CollisionBase* collider1, CollisionBase* collider2)
{
	CollisionBox* box1 = dynamic_cast<CollisionBox*>(collider1);
	CollisionBox* box2 = dynamic_cast<CollisionBox*>(collider2);

	// 各方向ベクトルの確保
	// （N***:標準化方向ベクトル）
	D3DXVECTOR3 NAe1 = box1->GetDirect(0), Ae1 = NAe1 * box1->GetLength(0);
	D3DXVECTOR3 NAe2 = box1->GetDirect(1), Ae2 = NAe2 * box1->GetLength(1);
	D3DXVECTOR3 NAe3 = box1->GetDirect(2), Ae3 = NAe3 * box1->GetLength(2);
	D3DXVECTOR3 NBe1 = box2->GetDirect(0), Be1 = NBe1 * box2->GetLength(0);
	D3DXVECTOR3 NBe2 = box2->GetDirect(1), Be2 = NBe2 * box2->GetLength(1);
	D3DXVECTOR3 NBe3 = box2->GetDirect(2), Be3 = NBe3 * box2->GetLength(2);
	D3DXVECTOR3 Interval = box1->GetPosition() - box2->GetPosition();

	// 分離軸 : Ae1
	float rA = D3DXVec3Length(&Ae1);
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NAe1)));
	if (L > rA + rB)
		return false; // 衝突していない

					  // 分離軸 : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NAe2)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NAe3)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NBe1)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NBe2)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &NBe3)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = static_cast<float>(fabs(D3DXVec3Dot(&Interval, &Cross)));
	if (L > rA + rB)
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

