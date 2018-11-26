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

	/**
	* @brief コンストラクタ
	*/
	GameScene();

	/**
	* @briefデストラクタ
	*/
	~GameScene();

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

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

//void GameScene::Run() 
//{
//	
//}

void GameScene::Update()
{
	//キーUpdate
	//オブジェクトのコントロール
	//カメラのコントロール
}

void GameScene::Render()
{
	//オブジェクトのレンダー
}