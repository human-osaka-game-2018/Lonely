/**
* @file TitleMenu.cpp
* @brief TitleMenuクラスのソースファイル
* @author 佐川　嗣苑
*/

#include "TitleMenu.h"
#include "../../GameScene/GameScene.h"
#include "../../../../GameLib/GameLib.h"


TitleMenu::TitleMenu()
{
	Initialize();
}

TitleMenu::~TitleMenu()
{
	Finalize();
}

//初期化する
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

	return true;
}

//解放する
void TitleMenu::Finalize()
{
}

//更新する
void TitleMenu::Update()
{
	switch (m_step)
	{
	case STEP1:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
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
			//ゲームシーンへ
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
			//ゲーム終了
			PostQuitMessage(0);
		}
		break;	
	}
	
	m_menuPressEnter.Update(m_step);
	m_menuGameStart.Update(m_step);
	m_menuGameEnd.Update(m_step);
	m_menuCursor.Update(m_step);
}

//描画する
void TitleMenu::Render()
{
	m_menuPressEnter.Render();
	m_menuGameStart.Render();
	m_menuGameEnd.Render();
	m_menuCursor.Render();
}
