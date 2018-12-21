/**
* @file CollisionManager.cpp
* @brief CollisionManagerクラスのソースファイル
* @author shion-sagawa
*/

#include "CollisionManager.h"

//class CollisionBase;
//class Object3DBase
//{
//public:
//	CollisionBase * m_Collision;
//
//	Object3DBase(CollisionType type)
//	{
//		m_Collision = new CollisionBase(this, type);
//	}
//};


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
void CollisionManager::RegisterCollision(CollisionBase *collision)
{
	m_pCollisionVec[collision->GetType()].push_back(collision);
}

//解放する
void CollisionManager::ReleaseCollision()
{
	for (int i = 0; i < COLLISION_TYPE_MAX; ++i)
	{
		//Vector配列の要素が０なら関数から抜ける
		if (m_pCollisionVec[i].size() == 0)
		{
			return;
		}

		//要素数を０にする
		m_pCollisionVec[i].clear();
		//キャパシティーを０にする
		m_pCollisionVec[i].shrink_to_fit();
	}
}


//更新する
void CollisionManager::Update()
{
	for (int i = 0; i < COLLISION_TYPE_MAX; i++)
	{
		for (int j = 0; j < COLLISION_TYPE_MAX; j++)
		{
			//collisionTargetTypeで指定したグループとだけ当たり判定をチェックする
			if (((1 << ((CollisionBase*)m_pCollisionVec)[j].GetType) & (collisionTargetType[i])) == false)
			{
				continue;
			}

			//縦の中身を回す
			for (int k = 0; k < m_pCollisionVec[i].size(); k++)
			{
				//横の中身を回す
				for (int l = 0; l < m_pCollisionVec[j].size(); l++)
				{
					//当たり判定を行う
					if ((m_pCollisionVec[i][k], m_pCollisionVec[j][l]))
					{

					}
				}
			}
		}
	}
}