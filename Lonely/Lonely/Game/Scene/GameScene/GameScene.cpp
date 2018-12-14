/**
* @file GameScene.h
* @brief GameScene�N���X�̃w�b�_�t�@�C��
* @author ����@�k��
*/

#include "GameScene.h"
#include "UI.h"
#include "Player\Player.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	Finalize();
}

//������X�V����
void GameScene::Update()
{
	//�V�[����؂�ւ��邩�ǂ������`�F�b�N����

	//���̃V�[���̃I�u�W�F�N�g�̍X�V���s��
	m_pObjectManager->Update();

	//�J����Update
	//m_pCamera->Update();
}

//�`�悷��
void GameScene::Render()
{
	//�I�u�W�F�N�g��Render
	m_pObjectManager->Render();
}

//����������
bool GameScene::Initialize()
{
	//�I�u�W�F�N�g��NEW���āA�I�u�܂˂�Vector�ɂ߂�
	m_pObjectManager->RegisterObject(new UI);
	m_pObjectManager->RegisterObject(new Player);
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
