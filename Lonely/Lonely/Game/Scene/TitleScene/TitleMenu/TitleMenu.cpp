/**
* @file TitleMenu.cpp
* @brief TitleMenuクラスのソースファイル
* @author shion-sagawa
*/

#include "TitleMenu.h"

#include "GameLib.h"

#include "SceneManager\Enum_Scene.h"
#include "../../GameScene/GameScene.h"
#include "../../DataSelectScene/DataSelectScene.h"



TitleMenu::TitleMenu()
	: m_pSoundsManager(GameLib::Instance.GetSoundsManager())
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


	// SoundsManagerインスタンス生成後に1度のみ行う。
	const TCHAR* filePath = _T("../Sounds/SE/sumahoneko/button.mp3");
	m_pSoundsManager->AddFile(filePath, _T("button"));


	return true;
}

//解放する
void TitleMenu::Finalize()
{
	SoundLibCWrapper_Free();

}

//更新する
void TitleMenu::Update()
{
	switch (m_step)
	{
	case STEP1:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			m_pSoundsManager->Start(_T("button"), false);

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
			m_pSoundsManager->Start(_T("button"), false);

			//ゲームシーンへ
			SCENEMANAGER->SwitchSceneNextFrame(GAME_SCENE);
			
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
			m_pSoundsManager->Start(_T("button"), false);
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
