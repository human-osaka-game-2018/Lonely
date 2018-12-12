/**
* @file GameLib.cpp
* @brief GameLib�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "GameLib.h"

// GameLib�̎��̒�`
GameLib GameLib::Instance;

GameLib::GameLib()
{
}

GameLib::~GameLib()
{
}

// DirectXLib�̏�����
bool GameLib::Initialize(const wchar_t* pName, int width, int height, bool isFullscreen)
{
	// �E�B���h�E�̐���
	if (!m_window.Create(pName, width, height))
	{
		return false;
	}
	// DirectX�V�X�e���̏�����
	if (!m_directX.Initialize(m_window.GetHandle(), width, height, isFullscreen))
	{
		return false;
	}
	//DirectInput�̏�����
	if (!m_dxInput.Initialize(m_window.GetHandle()))
	{
		return false;
	}
	// �t�H���g�̏�����
	if (!m_font.Initialize())
	{
		return false;
	}

	// �I�u�W�F�N�g�}�l�[�W��


	// �V�[���V�X�e���̏�����
	m_sceneManager.Initialize();
	// ���̓V�X�e���̏�����
	m_input.Initialize();

	return true;
}

// DirectXLib�̉��
void GameLib::Finalize()
{
	// �t�H���g�̉��
	m_font.Finalize();
	// ���̓V�X�e���̉��
	m_input.Finalize();
	//�I�u�W�F�N�g�}�l�[�W���̉��
	m_objectManager.Finalize();
	// �V�[���V�X�e���̉��
	m_sceneManager.Finalize();
	// DirectX�̉��
	m_directX.Finalize();
}

// ���C�����[�v
void GameLib::MainLoop()
{
	while (!m_window.IsQuitMessage())
	{
		if (!m_window.UpdateMessage())
		{
			//���͏����X�V����
			m_dxInput.UpdataInputState();

			//�V�[���̍X�V
			m_sceneManager.Update();

			//���̃t���[���œ��͂��ꂽ����ۑ�����
			m_dxInput.StorePrevInputState();

			// ��ʂ̃N���A
			m_directX.ClearBackBuffer(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);

			//�`��\��Ԃɂ���
			m_directX.BeginRenderScene();
				
			// �f�t�H���g�`��ݒ�
			m_directX.SetDefaultRenderState();

			// �V�[���̕`��
			m_sceneManager.Render();

			//�`��s�\��Ԃɂ���
			m_directX.EndRenderScene();
			
			// ��ʂ̕\��
			m_directX.FlipDisp();
		}
	}
}
