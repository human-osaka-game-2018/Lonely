/**
* @file TitleMenu.cpp
* @brief TitleMenu�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "TitleMenu.h"
#include "../../GameScene/GameScene.h"
#include "../../DataSelectScene/DataSelectScene.h"
#include "../../../../GameLib/GameLib.h"


TitleMenu::TitleMenu()
{
	Initialize();
}

TitleMenu::~TitleMenu()
{
	Finalize();
}

//����������
bool TitleMenu::Initialize()
{
	if (!m_menuPressEnter.Initialize())
	{
		return false;
	}
	if (!m_menuGameStart.Initialize())
	{
		return false;
	}
	if (!m_menuGameEnd.Initialize())
	{
		return false;
	}
	if (!m_menuCursor.Initialize())
	{
		return false;
	}


	// SoundsManager�C���X�^���X�������1�x�̂ݍs���B
	bool isSuccess = soundsManager.Initialize();
	const TCHAR* filePath = _T("../Sounds/SE/�X�}�z�L/cry1.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("cry1"));


	return true;
}

//�������
void TitleMenu::Finalize()
{
	SoundLibCWrapper_Free();
	m_menuPressEnter.Finalize();
	m_menuGameStart.Finalize();
	m_menuGameEnd.Finalize();
	m_menuCursor.Finalize();

}

//�X�V����
void TitleMenu::Update()
{
	switch (m_step)
	{
	case STEP1:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			//BGM��炷
			bool isSuccess = soundsManager.Start(_T("cry1"), false);

			m_step = STEP2;
		}
		break;

	case STEP2:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_step = STEP3;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_step = STEP3;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			//BGM��炷
			bool isSuccess = soundsManager.Start(_T("cry1"), false);

			//�Q�[���V�[����
			SCENEMANAGER->ChangeScene(new GameScene);
			
		}
		break;

	case STEP3:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_step = STEP2;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_step = STEP2;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			//BGM��炷
			bool isSuccess = soundsManager.Start(_T("cry1"), false);
			//�Q�[���I��
			PostQuitMessage(0);
			
		}
		break;	
	}
	
	m_menuPressEnter.Update(m_step);
	m_menuGameStart.Update(m_step);
	m_menuGameEnd.Update(m_step);
	m_menuCursor.Update(m_step);
}

//�`�悷��
void TitleMenu::Render()
{
	m_menuPressEnter.Render();
	m_menuGameStart.Render();
	m_menuGameEnd.Render();
	m_menuCursor.Render();
}
