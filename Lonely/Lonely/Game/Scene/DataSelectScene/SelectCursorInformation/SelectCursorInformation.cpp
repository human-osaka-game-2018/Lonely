/**
* @file SelectCursorInformation.cpp
* @brief SelectCursorInformation�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "SelectCursorInformation.h"
#include "../../../../GameLib/GameLib.h"

SelectCursorInformation::SelectCursorInformation()
{
	Initialize();
}

SelectCursorInformation::~SelectCursorInformation()
{
	Finalize();
}

//����������
bool SelectCursorInformation::Initialize()
{
		return true;
}

//�������
void SelectCursorInformation::Finalize()
{
}

void SelectCursorInformation::Update()
{
	UpdateCatCursorState();
	UpdateMiniCursorState();
}

void SelectCursorInformation::UpdateCatCursorState()
{
	//�~�j�J�[�\�����哱���������Ă���Ƃ�
	if (m_catCursorIsActive == false)
	{
		return;
	}

	//�L�[����
	switch (m_catCursorState)
	{
	case DATA1:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_RIGHT))
		{
			m_catCursorState = DATA2;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_LEFT))
		{
			m_catCursorState = DATA3;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			m_miniCursorIsActive = true;
			m_catCursorIsActive = false;
			m_miniCursorState = CONTINUE;
		}
		break;

	case DATA2:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_RIGHT))
		{
			m_catCursorState = DATA3;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_LEFT))
		{
			m_catCursorState = DATA1;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			m_miniCursorIsActive = true;
			m_catCursorIsActive = false;
			m_miniCursorState = CONTINUE;
		}
		break;

	case DATA3:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_RIGHT))
		{
			m_catCursorState = DATA1;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_LEFT))
		{
			m_catCursorState = DATA2;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			m_miniCursorIsActive = true;
			m_catCursorIsActive = false;
			m_miniCursorState = CONTINUE;
		}
		break;
	}
}

void SelectCursorInformation::UpdateMiniCursorState()
{
	//�L�^�J�[�\�����哱���������Ă���Ƃ�
	if (m_miniCursorIsActive == false)
	{
		return;
	}

	//�L�[����
	switch (m_miniCursorState)
	{
	case CONTINUE:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_miniCursorState = BACK;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_miniCursorState = NEWGAME;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			//SCENEMANAGER->ChangeScene(new GameScene(m_catCursorState));
		}
		break;

	case NEWGAME:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_miniCursorState = CONTINUE;

		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_miniCursorState = BACK;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			//SCENEMANAGER->ChangeScene(new GameScene);
		}
		break;

	case BACK:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_miniCursorState = NEWGAME;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_miniCursorState = CONTINUE;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			m_catCursorIsActive = true;
			m_miniCursorIsActive = false;
			m_miniCursorState = NOT_RENDER;
		}
		break;
	}
}