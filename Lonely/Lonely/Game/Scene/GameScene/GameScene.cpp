/**
* @file GameScene.h
* @brief GameSceneクラスのヘッダファイル
* @author 佐川　嗣苑
*/

#include "GameScene.h"
#include "Camera\TestCamera.h"
#include "UI.h"
#include "Sumahoneko.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	Finalize();
}


//初期化する
bool GameScene::Initialize()
{
	//ゲームシーンでどのカメラを使うか設定する
	m_pCameraManager->ChangeCamera(new TestCamera);

	//ObjectManagerのVector配列にゲームシーンで使うクラスを登録する
	m_pObjectManager->RegisterObject(new UI);
	m_pObjectManager->RegisterObject(new Sumahoneko);
	/*m_pObjectManager->RegisterObject(new TitleBackGround);
	m_pObjectManager->RegisterObject(new TitleMenu);
	m_pObjectManager->RegisterObject(new TitleLogo);*/

	return true;
}

//解放する
void GameScene::Finalize()
{
	m_pObjectManager->ReleaseObject();
}


//操作を更新する
void GameScene::Update()
{
	//このシーンのオブジェクトの更新を行う
	m_pObjectManager->Update();

	//カメラUpdate
	m_pCameraManager->Update();
}

//描画する
void GameScene::Render()
{
	//オブジェクトのRender
	m_pObjectManager->Render();
}
