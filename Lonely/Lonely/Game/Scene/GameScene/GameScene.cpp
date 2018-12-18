/**
* @file GameScene.cpp
* @brief GameScene�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "GameScene.h"
#include "Camera\TestCamera.h"
#include "UI\UI.h"
#include "UI\UIBar.h"
#include "UI\UIFootsteps.h"
#include "UI\UIHitPoint.h"
#include "UI\UIWaves.h"
#include "UI\UIBattery.h"
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
	m_pObjectManager->RegisterObject(new UIBar);
	m_pObjectManager->RegisterObject(new UIFootsteps);
	m_pObjectManager->RegisterObject(new UIWaves);
	m_pObjectManager->RegisterObject(new UIHitPoint);
	m_pObjectManager->RegisterObject(new UIBattery);
	m_pObjectManager->RegisterObject(new Sumahoneko);
	/*m_pObjectManager->RegisterObject(new TitleBackground);
	m_pObjectManager->RegisterObject(new TitleMenu);
	m_pObjectManager->RegisterObject(new TitleLogo);*/

	// SoundsManager�C���X�^���X�������1�x�̂ݍs���B
	bool isSuccess = soundsManager.Initialize();
	// �����t�@�C���I�[�v��
	// ��2�����͉����t�@�C�������ʂ��邽�߂̔C�ӂ̕�������L�[�Ƃ��Ďw�肷��B
	// ���̌�̑���֐��̌Ăяo�����ɂ́A�����Őݒ肵���L�[���w�肵�ĉ��������ʂ���B
	const TCHAR* filePath = _T("../Sounds/BGM/GameBGM.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("GameBGM"));
	


	return true;
}

//�������
void GameScene::Finalize()
{
	m_pObjectManager->ReleaseObject();

	bool isSuccess = soundsManager.Stop(_T("GameBGM"));
	SoundLibCWrapper_Free();
}


//������X�V����
void GameScene::Update()
{
	//BGM��炷
	bool isSuccess = soundsManager.Start(_T("GameBGM"), true);


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
