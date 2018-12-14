/**
* @file TitleScene.cpp
* @brief TitleScene�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "TitleScene.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "TitleMenu/TitleMenu.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	Finalize();
}

//������X�V����
void TitleScene::Update()
{
	//�V�[����؂�ւ��邩�ǂ������`�F�b�N����

	//���̃V�[���̃I�u�W�F�N�g�̍X�V���s��
	m_pObjectManager->Update();

	//�J����Update
	//m_pCamera->Update();
}

//�`�悷��
void TitleScene::Render()
{
	//�I�u�W�F�N�g��Render
	m_pObjectManager->Render();
}

//����������
bool TitleScene::Initialize()
{
	//�I�u�W�F�N�g��NEW���āA�I�u�܂˂�Vector�ɂ߂�
	m_pObjectManager->RegisterObject(new TitleBackground);
	m_pObjectManager->RegisterObject(new TitleMenu);
	m_pObjectManager->RegisterObject(new TitleLogo);
	return true;
	//m_pObjectManager->RegisterObject(new Cursor);
	//m_pObjectManager->RegisterObject(new TitleMenu);
	//m_pObjectManager->RegisterObject(new TitleMenu2);
}

//�������
void TitleScene::Finalize()
{
	m_pObjectManager->ReleaseObject();
}
