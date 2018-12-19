/**
* @file SelectCursorInformation.cpp
* @brief SelectCursorInformationクラスのソースファイル
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

//初期化する
bool SelectCursorInformation::Initialize()
{
		return true;
}

//解放する
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
	//ミニカーソルが主導権を持っているとき
	if (m_miniCursorIsActive)
	{
		return;
	}

	//キー操作
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
		}
		break;
	}
}

void SelectCursorInformation::UpdateMiniCursorState()
{
	//ミニカーソルが主導権を持っているとき
	if (m_catCursorIsActive)
	{
		return;
	}

	//キー操作
	switch (m_miniCursorState)
	{
	case CONTINUE:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_catCursorState = BACK;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_catCursorState = NEWGAME;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			//SCENEMANAGER->ChangeScene(new GameScene(m_catCursorState));
		}
		break;

	case NEWGAME:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_catCursorState = CONTINUE;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_catCursorState = BACK;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			//SCENEMANAGER->ChangeScene(new GameScene);
		}
		break;

	case BACK:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_catCursorState = NEWGAME;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_catCursorState = CONTINUE;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			m_catCursorIsActive = true;
			m_miniCursorIsActive = false;
		}
		break;
	}
}