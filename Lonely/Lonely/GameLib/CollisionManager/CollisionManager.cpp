/**
* @file CollisionManager.cpp
* @brief CollisionManager�N���X�̃\�[�X�t�@�C��
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

//����������
void CollisionManager::Initialize()
{
}

//�������
void CollisionManager::Finalize()
{
	ReleaseCollision();
}

//�o�^����
void CollisionManager::RegisterCollision(CollisionBase *collision)
{
	m_pCollisionVec[collision->GetType()].push_back(collision);
}

//�������
void CollisionManager::ReleaseCollision()
{
	for (int i = 0; i < COLLISION_TYPE_MAX; ++i)
	{
		//Vector�z��̗v�f���O�Ȃ�֐����甲����
		if (m_pCollisionVec[i].size() == 0)
		{
			return;
		}

		//�v�f�����O�ɂ���
		m_pCollisionVec[i].clear();
		//�L���p�V�e�B�[���O�ɂ���
		m_pCollisionVec[i].shrink_to_fit();
	}
}


//�X�V����
void CollisionManager::Update()
{
	for (int i = 0; i < COLLISION_TYPE_MAX; i++)
	{
		for (int j = 0; j < COLLISION_TYPE_MAX; j++)
		{
			//collisionTargetType�Ŏw�肵���O���[�v�Ƃ��������蔻����`�F�b�N����
			if (((1 << ((CollisionBase*)m_pCollisionVec)[j].GetType) & (collisionTargetType[i])) == false)
			{
				continue;
			}

			//�c�̒��g����
			for (int k = 0; k < m_pCollisionVec[i].size(); k++)
			{
				//���̒��g����
				for (int l = 0; l < m_pCollisionVec[j].size(); l++)
				{
					//�����蔻����s��
					if ((m_pCollisionVec[i][k], m_pCollisionVec[j][l]))
					{

					}
				}
			}
		}
	}
}