/**
* @file CollisionManager.h
* @brief CollisionManager�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include <vector>

#include "CollisionBase/CollisionBase.h"

/**
* @brief �����蔻��̃O���[�v�����i�g���ۂɕς��Ă��炤�K�v������j
*/
enum CollisionType
{
	PLAYER,
	ENEMY,
	MOVE_OBJ,
	DONT_MOVE_OBJ,
	COLLISION_TYPE_MAX,
};

/**
* �I�u�W�F�N�g���Ǘ�����N���X
*/
class CollisionManager
{
public:

	CollisionManager();
	~CollisionManager();

	/**
	* @brief �C���X�^���X�𐶐�����֐�
	*/
	void Initialize();

	/**
	* @brief �C���X�^���X��j������֐�
	*/
	void Finalize();

	/**
	* @brief ����֐�
	*/
	void Update();

	/**
	* @brief �I�u�W�F�N�g��o�^����֐�
	* @param �o�^�������h���N���X�̃|�C���^
	*/
	void RegisterCollision(CollisionBase*);

	/**
	* @brief �I�u�W�F�N�g���������֐�
	*/
	void ReleaseCollision();

private:

	std::vector<CollisionBase*> m_pCollisionVec[COLLISION_TYPE_MAX];    //!< �����蔻��I�u�W�F�N�g�����x�N�^�[�z��

	/**
	* @brief �ǂ�Ɠ����蔻����s�����i�g���ۂɕς��Ă��炤�K�v������j
	*/
	int collisionTargetType[] =
	{
		1 << PLAYER | 1 << ENEMY | 1 << MOVE_OBJ | 1 << DONT_MOVE_OBJ,	// Player
		1 << ENEMY | 1 << MOVE_OBJ | 1 << DONT_MOVE_OBJ,	            // Enemy
		1 << MOVE_OBJ | 1 << DONT_MOVE_OBJ,                             // MoveObj
		1 << DONT_MOVE_OBJ,                                             // DontMoveObj
	};

};
