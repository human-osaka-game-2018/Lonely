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
	if (m_catCursorIsActive == false)
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
	//猫型カーソルが主導権を持っているとき
	if (m_miniCursorIsActive == false)
	{
		return;
	}

	//キー操作
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