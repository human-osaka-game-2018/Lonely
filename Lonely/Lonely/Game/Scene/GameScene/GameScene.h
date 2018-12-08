/**
* @file GameScene.h
* @brief GameSceneクラスのヘッダファイル
* @author 佐川
*/

#pragma once

#include"../../../GameLib/SceneManager/SceneBase/SceneBase.h"

/**
* @brief ゲームシーンのクラス
*/
class GameScene : public SceneBase
{
public:

	GameScene();
	~GameScene();

	/**
	* @brief 初期化関数 
	*/
	bool Initialize();

	/**
	* @brief 解放関数
	*/
	void Finalize();

	/**
	* @brief 操作関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();

private:
	
};
