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
#include "../../../GameLib/GameLib.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	Finalize();
}

void GameScene::Load()
{
	//�Q�[���V�[���łǂ̃J�������g�����ݒ肷��
	m_pCameraManager->ChangeCamera(new TestCamera());

	//ObjectManager��Vector�z��ɃQ�[���V�[���Ŏg���N���X��o�^����
	m_pObjectManager->RegisterObject(new Sumahoneko());
	m_pObjectManager->RegisterObject(new UIBar());
	m_pObjectManager->RegisterObject(new UIFootsteps());
	m_pObjectManager->RegisterObject(new UIWaves());
	m_pObjectManager->RegisterObject(new UIHitPoint());
	m_pObjectManager->RegisterObject(new UIBattery());
	m_pObjectManager->RegisterObject(new UI());

	m_loadIsFinished = true;
}

//����������
bool GameScene::Initialize()
{
	m_loadIsFinished = false;

	m_catPawframecount = 0;
	m_catPawRendercount = 0;

	if (!m_texture.Load("../Graphics/loadBG.png"))
	{
		return false;
	}

	if (!m_catPaw.Load("../Graphics/catPaw.png"))
	{
		return false;
	}

	if (!m_loading.Load("../Graphics/loading.png"))
	{
		return false;
	}

	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	// �e�N�X�`����2�̗ݏ�łȂ��Ƃ��Ɍ��ʂ𔭊�����
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, u, v);

	HELPER_2D->SetVerticesFromLeftTopType(m_loadingvertices, 750.f, 535.f, 512.f, 256.f);

	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[0].vertex, 20.f, 510.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[1].vertex, 220.f, 510.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[2].vertex, 370.f, 340.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[3].vertex, 570.f, 390.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[4].vertex, 580.f, 210.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[5].vertex, 780.f, 215.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[6].vertex, 920.f, 60.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[7].vertex, 1120.f, 50.f, 170.f, 170.f);


	// SoundsManager�C���X�^���X�������1�x�̂ݍs���B
	bool isSuccess = soundsManager.Initialize();
	// �����t�@�C���I�[�v��
	// ��2�����͉����t�@�C�������ʂ��邽�߂̔C�ӂ̕�������L�[�Ƃ��Ďw�肷��B
	// ���̌�̑���֐��̌Ăяo�����ɂ́A�����Őݒ肵���L�[���w�肵�ĉ��������ʂ���B

	const TCHAR* filePath = _T("../Sounds/BGM/GameBGM.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("GameBGM"));

	m_loadImageThread = std::thread(&GameScene::Load, this);

	return true;
}

//�������
void GameScene::Finalize()
{
	m_pObjectManager->ReleaseObject();

	bool isSuccess = soundsManager.Stop(_T("GameBGM"));
	SoundLibCWrapper_Free();

	if (m_loadImageThread.joinable())
	{
		m_loadImageThread.join();
	}
}


//������X�V����
void GameScene::Update()
{
	if (m_loadIsFinished == false)
	{
		m_catPawframecount++;
		return;
	}

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
	if (m_loadIsFinished == false)
	{
		IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();

		//���_�ɓ����f�[�^��ݒ�
		pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_texture.GetD3DTexture());

		//�`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_loading.GetD3DTexture());

		//�`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_loadingvertices, sizeof(Simple2DVertex));

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_catPaw.GetD3DTexture());

		if (m_catPawframecount == 20)
		{
			m_catPawRendercount++;
			m_catPawframecount = 0;
		}

		if (m_catPawRendercount == 9)
		{
			m_catPawRendercount = 0;
		}

		//�`��
		for (int i = 0; i < m_catPawRendercount; i++)
		{
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_catPawvertices[i].vertex, sizeof(Simple2DVertex));
		}
		
		return;
	}
	
	//�I�u�W�F�N�g��Render
	m_pObjectManager->Render();
	
}
