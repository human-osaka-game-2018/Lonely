/**
* @file SceneManager.h
* @brief SceneManagerクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "SceneBase/SceneBase.h"

/**
* @brief シーンを管理するクラス
*/
class SceneManager
{
public:

	SceneManager();
	~SceneManager();

	/**
	* @brief 初期化を行う関数
	*/
	void Initialize();

	/**
	* @brief 解放を行う関数
	*/
	void Finalize();

	/**
	* @brief 操作の更新を行う関数
	*/
	void Update();

	/**
	* @brief 描画を行う関数
	*/
	void Render();

	/**
	* @brief 次のフレームにシーンを遷移するように設定する関数
	* @param (nextScene) 次にどのシーンに遷移するか
	*/
	void SwitchSceneNextFrame(int nextScene);
	
private:

	/**
	* @brief シーンを生成する関数
	*/
	void CreateScene();

	/**
	* @brief シーンを解放する関数
	*/
	void ReleaseScene();

	/**
	* @brief シーンの遷移（シーンの解放と生成）を行う関数
	*/
	void SwitchScene();

	SceneBase* m_pScene;          //!< 更新処理を行うシーンのポインタ
	int        m_currentScene;    //!< 現在のシーン
	int        m_nextScene;       //!< 次のシーン
};
