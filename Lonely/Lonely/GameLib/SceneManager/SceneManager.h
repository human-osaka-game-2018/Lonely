/**
* @file SceneManager.h
* @brief SceneManagerクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

//#include "..\GameLib.h"
#include "SceneBase\SceneBase.h"

/**
* シーンを管理するクラス
*/
class SceneManager
{
public:
	SceneManager(void);
	~SceneManager(void);

	/**初期化を行う関数*/
	void Initialize(void);
	/**解放を行う関数*/
	void Finalize(void);
	/**操作の更新を行う関数*/
	void Update(void);
	/**描画を行う関数*/
	void Render(void);

	/**シーンの遷移を行う関数*/
	bool ChangeScene(SceneBase* pScene);
	
private:

	SceneBase* m_pScene;											   
};

//旧バージョンのシーンマネージャ、戻すかもしれないから置いている
//enum SCENE_STATE
//{
//	INIT,
//	MAIN,
//	RELEASE
//};
//
//class SceneManager
//{
//public:
//	///**インスタンスを生成する関数*/
//	//static SceneManager* GetInstance();
//	///**インスタンスを破棄する関数*/
//	//void ReleaseInstance();
//	/**初期化する関数*/
//	void Initialize(void);
//	/**ゲームの処理をまとめて実行する関数*/
//	void DevideSceneOperation();
//
//private:
//	/**コンストラクタ*/
//	SceneManager();
//	/**デストラクタ*/
//	~SceneManager();
//	/**シーンを切り替える関数*/
//	void ChangeScene();
//	/**操作関数*/
//	void Update();
//	/**描画関数*/
//	void Render();
//
//	static SceneManager*  m_pSceneManager;             //!< SceneManagerクラスのインスタンスへのポインタ変数
//	SceneBase* m_pScene = nullptr;					   //!< Sceneクラスのインスタンスへのポインタ変数
//	int m_currentScene = TITLE_SCENE;				   //!< 今どのシーンなのかを保存する
//	int m_nextScene = DATA_SELECT_SCENE;			   //!< 次どのシーンなのかを保存する
//	int m_sceneState = INIT;						   //!< シーンがどんな状態なのかを保存する
//	
//	
//};

//SceneManager* SceneManager::m_pSceneManager = nullptr;
//
//SceneManager* SceneManager::GetInstance() 
//{
//	if (m_pSceneManager == nullptr) 
//	{ 
//		m_pSceneManager = new SceneManager;						//シーンマネージャのインスタンスを生成する
//	}
//	return m_pSceneManager;
//}
//
//void SceneManager::ReleaseInstance()
//{
//	delete m_pSceneManager;										//シーンマネージャのインスタンスを破棄する
//	m_pSceneManager = nullptr;
//}
//
//void SceneManager::ChangeScene()
//{
//	if (m_currentScene == m_nextScene)
//	{
//		return;
//	}
//
//	switch (m_nextScene)
//	{
//	case SCENE_ID::TITLE_SCENE:									//タイトルシーンに移るとき
//
//		delete m_pScene;
//
//		m_currentScene = SCENE_ID::TITLE_SCENE;
//		m_pScene = new TitleScene();
//
//		break;
//	case SCENE_ID::DATA_SELECT_SCENE:							//データセレクトシーンに移るとき
//
//		delete m_pScene;
//
//		m_currentScene = SCENE_ID::DATA_SELECT_SCENE;
//		m_pScene = new DataSelectScene();
//
//		break;
//	case SCENE_ID::GAME_SCENE:									//ゲームシーンに移るとき
//
//		delete m_pScene;
//
//		m_currentScene = SCENE_ID::GAME_SCENE;
//		m_pScene = new GameScene();
//
//		break;
//	default:
//
//		break;
//	}
//}
//
//void SceneManager::DevideSceneOperation() 
//{
//	switch (m_sceneState)
//	{
//	case INIT:
//		m_pScene->Init();										//シーンでの情報を初期化する
//		break;
//	case MAIN:
//		//m_pScene->UpdateInput
//		m_pScene->Update();										//ゲームの操作処理を行う
//		m_pScene->Render();										//ゲームの描画処理を行う
//		break;
//	case RELEASE:
//		m_pScene->Release();									//シーンでの情報を解放する
//		break;
//	}
//
//	m_pScene->UpdateNextScene(&m_nextScene);					//シーンの情報を新しくする
//	ChangeScene();												//シーンが切り替える必要があれば切り替える
//}
