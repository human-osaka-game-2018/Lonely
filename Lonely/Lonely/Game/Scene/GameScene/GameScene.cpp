/**
* @file GameScene.h
* @brief GameSceneクラスのヘッダファイル
* @author 佐川　嗣苑
*/

#include "GameScene.h"
#include "UI.h"
#include "Player\Player.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	Finalize();
}

//操作を更新する
void GameScene::Update()
{
	//シーンを切り替えるかどうかをチェックする

	//このシーンのオブジェクトの更新を行う
	m_pObjectManager->Update();

	//カメラUpdate
	//m_pCamera->Update();
}

//描画する
void GameScene::Render()
{
	//オブジェクトのRender
	m_pObjectManager->Render();
}

//初期化する
bool GameScene::Initialize()
{
	//オブジェクトをNEWして、オブまねのVectorにつめる
	m_pObjectManager->RegisterObject(new UI);
	m_pObjectManager->RegisterObject(new Player);
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
