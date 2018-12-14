/**
* @file TitleScene.h
* @brief TitleScene�N���X�̃w�b�_�t�@�C��
* @author ����@�k��
*/

#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

//������X�V����
void TitleScene::Update()
{
	//�I�u�W�F�N�gUpdate 
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
	m_pObjectManager->ResisterObject(new TitleBackGround);
	return true;
	//return true;
	//m_pObjectManager->ResisterObject(new TitleLogo);
	//m_pObjectManager->ResisterObject(new Cursor);
	//m_pObjectManager->ResisterObject(new TitleMenu1);
	//m_pObjectManager->ResisterObject(new TitleMenu2);
}

//�������
void TitleScene::Finalize()
{

}