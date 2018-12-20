/**
* @file ObjectManager.h
* @brief ObjectManager�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "Object.h"
#include <vector>

/**
* �I�u�W�F�N�g���Ǘ�����N���X
*/
class ObjectManager
{
public:

	ObjectManager();
	~ObjectManager();

	/**
	* @brief �C���X�^���X�𐶐�����֐�
	*/
	void Initialize();

	/**
	* @brief �C���X�^���X��j������֐�
	*/
	void Finalize();
	
	/**
	* @brief �I�u�W�F�N�g��o�^����֐�
	* @param �o�^�������h���N���X�̃|�C���^
	*/
	void RegisterObject(Object*);

	/**
	* @brief �I�u�W�F�N�g���������֐�
	*/
	void ReleaseObject();

	/**
	* @brief ����֐�
	*/
	void Update();

	/**
	* @brief �`��֐�
	*/
	void Render();
	
private:

	std::vector<Object*> m_pObjectVec;				//!< Object�N���X��
	//static ObjectManager* m_pObjectManager;					//!< ObjectManager�N���X�̃C���X�^���X�ւ̃|�C���^�ϐ�
};
