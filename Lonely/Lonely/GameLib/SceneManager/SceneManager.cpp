/**
* @file SceneManager.cpp
* @brief SceneManagerクラスのソースファイル
* @author shion-sagawa
*/

#include "SceneManager.h"

#include "GameLib.h"

#include "Enum_Scene.h"
#include "../../Game/Scene/TitleScene/TitleScene.h"
#include "../../Game/Scene/DataSelectScene/DataSelectScene.h"
#include "../../Game/Scene/GameScene/GameScene.h"


SceneManager::SceneManager()
	: m_pScene(nullptr)
	, m_currentScene(TITLE_SCENE)
	, m_nextScene(TITLE_SCENE)
{
}

SceneManager::~SceneManager()
{
	Finalize();
}

//GameLibの初期化関数で一度だけSceneManagerの初期化関数が呼ばれる
void SceneManager::Initialize()
{
	CreateScene();
}

void SceneManager::Finalize()
{
	ReleaseScene();
}

void SceneManager::Update()
{
	//シーン遷移すべきなら遷移関数を呼ぶ
	if (m_currentScene != m_nextScene)
	{
		SwitchScene();
	}

	//現在のシーンの処理を更新する
	if (m_pScene)
	{
		m_pScene->Update();
	}
}

void SceneManager::Render()
{
	if (m_pScene)
	{
		m_pScene->Render();
	}
}

void SceneManager::SwitchScene()
{
	//現在のシーンを解放する
	ReleaseScene();

	//次のシーンを作成する
	CreateScene();
}

void SceneManager::ReleaseScene()
{
	m_pScene->Finalize();
	delete m_pScene;
	m_pScene = nullptr;
}

void SceneManager::CreateScene()
{
	//現在までのシーンを次のシーンへ変更
	m_currentScene = m_nextScene;

	switch (m_nextScene)
	{
	case TITLE_SCENE:

		m_pScene = new TitleScene();
		break;

	case DATA_SELECT_SCENE:

		m_pScene = new DataSelectScene();
		break;

	case GAME_SCENE:

		m_pScene = new GameScene();
		break;

	default:

		break;
	}

	m_pScene->Initialize();
}

void SceneManager::SwitchSceneNextFrame(int nextScene)
{
	m_nextScene = nextScene;
}
