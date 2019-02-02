/**
* @file GameScene.cpp
* @brief GameSceneクラスのソースファイル
* @author shion-sagawa
*/

#include "GameScene.h"
#include "../../../GameLib/GameLib.h"
#include "Camera\TestCamera.h"
#include "UI\UI.h"
#include "UI\UIBar.h"
#include "UI\UIFootsteps.h"
#include "UI\UIHitPoint.h"
#include "UI\UIWaves.h"
#include "UI\UIBattery.h"
#include "Stage\Stage.h"
#include "Player\Sumahoneko.h"
#include "Enemy\Pasoken.h"
#include "Trigar\TrigarCharging.h"
#include "Trigar\TrigarMovable.h"
#include "Trigar\TrigarQR.h"
#include "StageObject\StageMovableObject.h"
#include "StageObject\StageStopedObject.h"
#include "GameOver\GameOver.h"

GameScene::GameScene()
	: m_pCollisionManager(GameLib::Instance.GetCollisionManager())
	, m_pSoundsManager(GameLib::Instance.GetSoundsManager())
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

	m_pObjectManager->RegisterObject(new Stage);
	Sumahoneko* pSumahoneko = new Sumahoneko;
	m_pObjectManager->RegisterObject(static_cast<Object*>(pSumahoneko));
	m_pObjectManager->RegisterObject(new Pasoken);
	m_pObjectManager->RegisterObject(new StageMovableObject(&D3DXVECTOR3(10.f, 0.f, 10.f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f),&D3DXVECTOR3(1.5f,1.5f,1.5f), pSumahoneko));
	m_pObjectManager->RegisterObject(new StageMovableObject(&D3DXVECTOR3(80.f, 0.f, 20.f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &D3DXVECTOR3(1.5f, 1.5f, 1.5f), pSumahoneko));
	m_pObjectManager->RegisterObject(new StageMovableObject(&D3DXVECTOR3(20.f, 0.f, 80.f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &D3DXVECTOR3(1.5f, 1.5f, 1.5f), pSumahoneko));
	

	//ObjectManagerのVector配列にゲームシーンで使うクラスを登録する
	m_pObjectManager->RegisterObject(new TrigarQR(&D3DXVECTOR3(50.f, 0.f, 0.f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f)));
	m_pObjectManager->RegisterObject(new TrigarQR(&D3DXVECTOR3(0.f, 0.f, 50.f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f)));
	m_pObjectManager->RegisterObject(new TrigarQR(&D3DXVECTOR3(-50.f, 0.f, -50.f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f)));
	m_pObjectManager->RegisterObject(new TrigarQR(&D3DXVECTOR3(-100.f, 0.f, -80.f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f)));


	//m_pObjectManager->RegisterObject(new GameOver);
	m_pObjectManager->RegisterObject(new UI);
	m_pObjectManager->RegisterObject(new UIBar);
	m_pObjectManager->RegisterObject(new UIFootsteps);
	m_pObjectManager->RegisterObject(new UIWaves);
	m_pObjectManager->RegisterObject(new UIHitPoint);
	m_pObjectManager->RegisterObject(new UIBattery);
	//m_pObjectManager->RegisterObject(new GameOver);

	// 第2引数は音声ファイルを識別するための任意の文字列をキーとして指定する。
	// この後の操作関数の呼び出し時には、ここで設定したキーを指定して音声を識別する。
	const TCHAR* filePath = _T("../Sounds/BGM/GameBGM.mp3");
	m_pSoundsManager->AddFile(filePath, _T("GameBGM"));
	


	return true;
}

//解放する
void GameScene::Finalize()
{
	m_pObjectManager->ReleaseObject();

	m_pSoundsManager->Stop(_T("GameBGM"));
}


//操作を更新する
void GameScene::Update()
{
	//BGMを鳴らす
	bool isSuccess = m_pSoundsManager->Start(_T("GameBGM"), true);

	//当たり判定を登録されてるのを解除する
	//当たり判定の登録はそれぞれのクラスで行う
	m_pCollisionManager->ReleaseCollision();

	//このシーンのオブジェクトの更新を行う
	m_pObjectManager->Update();

	//当たり判定を行う
	m_pCollisionManager->Update();

	//カメラUpdate
	m_pCameraManager->Update();
}

//描画する
void GameScene::Render()
{
	//オブジェクトのRender
	m_pObjectManager->Render();
}
