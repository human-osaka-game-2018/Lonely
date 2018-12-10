/**
* @file GameScene.h
* @brief GameScene�N���X�̃w�b�_�t�@�C��
* @author ����@�k��
*/

#include "GameScene.h"
#include "Camera\TestCamera.h"
#include "UI.h"
#include "Sumahoneko.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	Finalize();
}


//����������
bool GameScene::Initialize()
{
	//�Q�[���V�[���łǂ̃J�������g�����ݒ肷��
	m_pCameraManager->ChangeCamera(new TestCamera);

	//ObjectManager��Vector�z��ɃQ�[���V�[���Ŏg���N���X��o�^����
	m_pObjectManager->RegisterObject(new UI);
	m_pObjectManager->RegisterObject(new Sumahoneko);
	/*m_pObjectManager->RegisterObject(new TitleBackGround);
	m_pObjectManager->RegisterObject(new TitleMenu);
	m_pObjectManager->RegisterObject(new TitleLogo);*/

	return true;
}

//�������
void GameScene::Finalize()
{
	m_pObjectManager->ReleaseObject();
}


//������X�V����
void GameScene::Update()
{
	//���̃V�[���̃I�u�W�F�N�g�̍X�V���s��
	m_pObjectManager->Update();

	//�J����Update
	m_pCameraManager->Update();
}

//�`�悷��
void GameScene::Render()
{
	//�I�u�W�F�N�g��Render
	m_pObjectManager->Render();
}
