/**
* @file TitleMenu.cpp
* @brief TitleMenuクラスのソースファイル
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
	bool isSuccess = soundsManager.Initialize();
	const TCHAR* filePath = _T("../Sounds/SE/スマホ猫/cry1.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("cry1"));


	return true;
}

//解放する
void TitleMenu::Finalize()
{
	SoundLibCWrapper_Free();
	m_menuPressEnter.Finalize();
	m_menuGameStart.Finalize();
	m_menuGameEnd.Finalize();
	m_menuCursor.Finalize();

}

//更新する
void TitleMenu::Update()
{
	switch (m_step)
	{
	case STEP1:

		if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			//BGMを鳴らす
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
			//BGMを鳴らす
			bool isSuccess = soundsManager.Start(_T("cry1"), false);

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
			//BGMを鳴らす
			bool isSuccess = soundsManager.Start(_T("cry1"), false);
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
