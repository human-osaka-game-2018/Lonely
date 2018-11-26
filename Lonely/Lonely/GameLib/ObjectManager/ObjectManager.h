/**
* @file ObjectManager.h
* @brief ObjectManager�N���X�̃w�b�_�t�@�C��
* @author ����
*/

#pragma once
#include "Object.h"

/**
* �I�u�W�F�N�g���Ǘ�����N���X
*/
class ObjectManager
{
public:

	///**
	//* @brief �C���X�^���X�𐶐�����֐�
	//*/
	//static ObjectManager* GetInstance();

	///**
	//* @brief �C���X�^���X��j������֐�
	//*/
	//static void ReleaseInstance();

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
	void ResisterObject(Object*);

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

	static std::vector<Object*> m_pObjectVec;				//!< Object�N���X��
	//static ObjectManager* m_pObjectManager;					//!< ObjectManager�N���X�̃C���X�^���X�ւ̃|�C���^�ϐ�
};
