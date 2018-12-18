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


	//BGM��炷
	bool isSuccess = soundsManager.Start(_T("TitleBGM"), true);

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

	// SoundsManager�C���X�^���X�������1�x�̂ݍs���B
	bool isSuccess = soundsManager.Initialize();
	// �����t�@�C���I�[�v��
	// ��2�����͉����t�@�C�������ʂ��邽�߂̔C�ӂ̕�������L�[�Ƃ��Ďw�肷��B
	// ���̌�̑���֐��̌Ăяo�����ɂ́A�����Őݒ肵���L�[���w�肵�ĉ��������ʂ���B
	const TCHAR* filePath = _T("../Sounds/BGM/TitleBGM.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("TitleBGM"));

	return true;
}

//�������
void TitleScene::Finalize()
{
	m_pObjectManager->ReleaseObject();

	bool isSuccess = soundsManager.Stop(_T("TitleBGM"));
	SoundLibCWrapper_Free();
}
