/**
* @file ObjectManager.cpp
* @brief ObjectManager�N���X�̃\�[�X�t�@�C��
* @author ����@�k��
*/

#include "ObjectManager.h"


////�I�u�W�F�N�g�}�l�[�W���̎���
//ObjectManager* ObjectManager::m_pObjectManager = nullptr;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	//�I�u�W�F�N�g�̑S�J���̊֐����Ă�
}
//
////�C���X�^���X�𐶐�����
//ObjectManager* ObjectManager::GetInstance()
//{
//	if (m_pObjectManager == nullptr)
//	{
//		m_pObjectManager = new ObjectManager;
//	}
//	return m_pObjectManager;
//}
//
////�C���X�^���X��j������
//void ObjectManager::ReleaseInstance()
//{
//	//�܂�ObjectManager�������Ă���Object��Vector�z�������������
//	ReleaseObject();
//
//	//���̂��Ƃ��̃C���X�^���X��j������
//	delete m_pObjectManager;
//	m_pObjectManager = nullptr;
//}

//����������
void ObjectManager::Initialize()
{
}

//�������
void ObjectManager::Finalize()
{
	ReleaseObject();
}

//���̃N���X��h�������N���X�̑���֐����Ă�
void ObjectManager::Update()
{
	for (int i = 0; i < m_pObjectVec.size(); i++)
	{
		m_pObjectVec[i]->Update();
	}
}

//���̃N���X��h�������N���X�̕`��֐����Ă�
void ObjectManager::Render()
{
	for (int i = 0; i < m_pObjectVec.size(); i++) {
		m_pObjectVec[i]->Render();
	}
}

//���̃N���X��h�������N���X��o�^����
void ObjectManager::ResisterObject(Object* object)
{
	m_pObjectVec.push_back(object);
}

//���̃N���X��h�������N���X���������
void ObjectManager::ReleaseObject()
{
	//Vector�z��̗v�f���O�Ȃ�֐����甲����
	if (m_pObjectVec.size() == 0)
	{
		return;
	}

	for (Object* pI : m_pObjectVec)
	{
		delete pI;
	}

	//�v�f�����O�ɂ���
	m_pObjectVec.clear();
	//�L���p�V�e�B�[���O�ɂ���
	m_pObjectVec.shrink_to_fit();
}