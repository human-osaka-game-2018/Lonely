
/**
* @file CameraManager.cpp
* @brief CameraManager�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "CameraManager.h"
#include "../GameLib.h"

CameraManager::CameraManager()
	: m_pCamera(nullptr)
{}

CameraManager::~CameraManager()
{
	Finalize();
}

//������
void CameraManager::Initialize()
{
	m_pCamera = nullptr;
}

//���
void CameraManager::Finalize()
{
	// �Ō�͉�����ďI���
	if (m_pCamera) { m_pCamera->Finalize(); }
	SAFE_DELETE(m_pCamera);
}

//�J�����̍X�V
void CameraManager::Update()
{
	if (m_pCamera) m_pCamera->Update();
}

//�J�����̕ύX
void CameraManager::ChangeCamera(CameraBase* pCamera)
{
	// ���݂̃V�[�����������
	if (m_pCamera)
	{
		m_pCamera->Finalize();
		SAFE_DELETE(m_pCamera);
	}

	// ���̃V�[��������Ώ���������
	if (pCamera)
	{
		pCamera->Initialize();
	}

	m_pCamera = pCamera;
}