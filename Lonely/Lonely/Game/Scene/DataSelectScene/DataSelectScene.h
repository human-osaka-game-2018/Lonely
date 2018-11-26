/**
* @file DataSelectScene.h
* @brief DataSelectSceneクラスのヘッダファイル
* @author 佐川
*/

#pragma once

#include "../../../GameLib/SceneManager/SceneBase/SceneBase.h"

/**
* @brief データセレクトシーンのクラス
*/
class DataSelectScene : public SceneBase
{
public:

	DataSelectScene();
	~DataSelectScene();
	
	/**
	* @brief 初期化する関数
	*/
	bool Initialize();

	/**
	* @brief 解放する関数
	*/
	void Finalize();

	/**
	* @brief 操作を更新する関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();

private:

};

DataSelectScene::DataSelectScene()
{
}

DataSelectScene::~DataSelectScene()
{
}

bool DataSelectScene::Initialize()
{
}

void DataSelectScene::Finalize()
{
}

void DataSelectScene::Update()
{

}

void DataSelectScene::Render()
{

}