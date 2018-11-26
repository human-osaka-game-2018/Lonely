/**
* @file SceneManager.cpp
* @brief SceneManagerクラスのソースファイル
* @author 佐川
*/

#include "../GameLib.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: m_pScene(NULL)
{}

SceneManager::~SceneManager()
{
	Finalize();
}

/**シーン管理の初期化*/
void SceneManager::Initialize()
{
	m_pScene = NULL;
}

/**シーン管理の解放*/
void SceneManager::Finalize()
{
	// 最後は解放して終わる
	if (m_pScene) { m_pScene->Finalize(); }
	SAFE_DELETE(m_pScene);
}

/**シーンの更新*/
void SceneManager::Update()
{
	if (m_pScene) m_pScene->Update();
}

/**シーンの描画*/
void SceneManager::Render()
{
	if (m_pScene) m_pScene->Render();

}

/**シーンの遷移*/
bool SceneManager::ChangeScene(SceneBase* pScene)
{
	// 現在のシーンを解放する
	if (m_pScene)
	{
		m_pScene->Finalize();
		SAFE_DELETE(m_pScene);
	}

	bool ret = true;
	// 次のシーンがあれば初期化する
	if (pScene)
	{
		ret = pScene->Initialize();
	}
	m_pScene = pScene;
	return ret;
}