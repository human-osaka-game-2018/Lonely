/**
* @file SharedInformation.cpp
* @brief SharedInformation�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "SharedInformation.h"

// GameLib�̎��̒�`
SharedInformation SharedInformation::Instance;

SharedInformation::SharedInformation()
	: m_playerPosition({0.f,0.f,0.f})
	, m_cameraPosition({0.f,0.f,0.f})
	, m_cameraDirection(0.f)
	, m_cameraMode(DEFAULT_CAMERA)
	, m_playerInitiative(SUMAHONEKO)
{
	Initialize();
}

SharedInformation::~SharedInformation()
{
	Finalize();
}

//����������
bool SharedInformation::Initialize()
{
	//�Z�[�u�f�[�^�̏��ŏ���������
	//m_playerPosition = SaveData->GetPlayerPosition();
	//m_cameraPosition = SaveData->GetPlayerPosition();
	//m_cameraMode = saveData->GetCameraMode();

	return true;
}

//�������
void SharedInformation::Finalize()
{
	//�Z�[�u�f�[�^�̕ۑ�
}
