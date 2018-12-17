/**
* @file GameScene.cpp
* @brief GameSceneクラスのソースファイル
* @author shion-sagawa
*/

#include "GameScene.h"
#include "Camera\TestCamera.h"
#include "UI\UI.h"
#include "UI\UIBar.h"
#include "UI\UIFootsteps.h"
#include "UI\UIHitPoint.h"
#include "UI\UIWaves.h"
#include "UI\UIBattery.h"
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
	m_pObjectManager->RegisterObject(new UIBar);
	m_pObjectManager->RegisterObject(new UIFootsteps);
	m_pObjectManager->RegisterObject(new UIWaves);
	m_pObjectManager->RegisterObject(new UIHitPoint);
	m_pObjectManager->RegisterObject(new UIBattery);
	m_pObjectManager->RegisterObject(new Sumahoneko);
	/*m_pObjectManager->RegisterObject(new TitleBackground);
	m_pObjectManager->RegisterObject(new TitleMenu);
	m_pObjectManager->RegisterObject(new TitleLogo);*/

	// SoundsManagerインスタンス生成後に1度のみ行う。
	bool isSuccess = soundsManager.Initialize();
	// 音声ファイルオープン
	// 第2引数は音声ファイルを識別するための任意の文字列をキーとして指定する。
	// この後の操作関数の呼び出し時には、ここで設定したキーを指定して音声を識別する。
	const TCHAR* filePath = _T("../Sounds/BGM/GameBGM.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("GameBGM"));
	


	return true;
}

//解放する
void GameScene::Finalize()
{
	m_pObjectManager->ReleaseObject();

	bool isSuccess = soundsManager.Stop(_T("GameBGM"));
	SoundLibCWrapper_Free();
}


//操作を更新する
void GameScene::Update()
{
	//BGMを鳴らす
	bool isSuccess = soundsManager.Start(_T("GameBGM"), true);


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
