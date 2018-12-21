/**
* @file SelectStateManager.cpp
* @brief SelectStateManager�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "SelectStateManager.h"

SelectStateManager::SelectStateManager()
{
}

SelectStateManager::~SelectStateManager()
{
	//�I�u�W�F�N�g�̑S�J���̊֐����Ă�
}

//����������
void SelectStateManager::Initialize()
{
}

//�������
void SelectStateManager::Finalize()
{
	ReleaseObject();
}

//���̃N���X��h�������N���X�̑���֐����Ă�
void SelectStateManager::Update()
{
	for (int i = 0; i < m_pObjectVec.size(); i++)
	{
		m_pObjectVec[i]->Update();
	}
}

//���̃N���X��h�������N���X�̕`��֐����Ă�
void SelectStateManager::Render()
{
	for (int i = 0; i < m_pObjectVec.size(); i++) {
		m_pObjectVec[i]->Render();
	}
}

//���̃N���X��h�������N���X��o�^����
void SelectStateManager::RegisterObject(Object* object)
{
	m_pObjectVec.push_back(object);
}

//���̃N���X��h�������N���X���������
void SelectStateManager::ReleaseObject()
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
