/**
* @file GameScene.cpp
* @brief GameSceneクラスのソースファイル
* @author shion-sagawa
*/

#include "GameScene.h"

#include "GameLib.h"

#include "Camera/MainCamera.h"
#include "UI/UI.h"
#include "UI/UIBar.h"
#include "UI/UIFootsteps.h"
#include "UI/UIHitPoint.h"
#include "UI/UIWaves.h"
#include "UI/UIBattery.h"
#include "Stage/Stage.h"
#include "Player/Sumahoneko.h"
#include "Player/App/QRApp.h"
#include "Enemy/Pasoken.h"
#include "Trigger/TriggerCharging.h"
#include "Trigger/TriggerMovable.h"
#include "Trigger/TriggerQR.h"
#include "StageObject/StageMovableObject.h"
#include "StageObject/StageStopedObject.h"
#include "StoryIntroduction/StoryIntroduction.h"
#include "GameOver/GameOver.h"

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
	SharedInformation::Instance.Initialize();
	//ゲームシーンでどのカメラを使うか設定する
	m_pCameraManager->ChangeCamera(new MainCamera);
	
	//このシーンで使うクラスをObjectManagerに登録する
	m_pObjectManager->RegisterObject(new Stage);
	Sumahoneko* pSumahoneko = new Sumahoneko;
	QRApp* pQrApp = pSumahoneko->GetQrApp();
	m_pObjectManager->RegisterObject(static_cast<Object*>(pSumahoneko));
	m_pObjectManager->RegisterObject(new Pasoken);
	m_pObjectManager->RegisterObject(new StageMovableObject(&D3DXVECTOR3(10.f, 0.f, 10.f), &D3DXVECTOR3(3.0f, 5.0f, 3.0f),&D3DXVECTOR3(4.f,4.f,4.f), pSumahoneko));
	m_pObjectManager->RegisterObject(new StageMovableObject(&D3DXVECTOR3(80.f, 0.f, 20.f), &D3DXVECTOR3(3.0f, 5.0f, 3.0f), &D3DXVECTOR3(4.f, 4.f, 4.f), pSumahoneko));
	m_pObjectManager->RegisterObject(new StageMovableObject(&D3DXVECTOR3(20.f, 0.f, 80.f), &D3DXVECTOR3(3.0f, 5.0f, 3.0f), &D3DXVECTOR3(4.f, 4.f, 4.f), pSumahoneko));
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3(  47.0f,  0.1f, -61.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//本棚下
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3( 112.0f,  0.1f, -67.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//机の横
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3(  -4.5f,  0.1f, 170.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//穴の中
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3(-113.0f,  0.1f,  12.5f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//ベッドの横
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3( -90.0f, 11.0f, -32.5f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//布団の中
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3(-191.5f, 39.0f,  30.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//柱の上
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3(-114.5f, 25.0f,  54.5f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//壁付け棚の上
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3(  22.0f, 16.0f, -56.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//本棚の上
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3( -38.5f, 20.0f, -56.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//ベッドの隣の机の上
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3( -40.5f, 12.0f,  32.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//本棚横の机の上
	m_pObjectManager->RegisterObject(new TriggerQR(&D3DXVECTOR3(  87.0f, 22.5f, -50.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), pQrApp));//倒れている椅子の上
	m_pObjectManager->RegisterObject(new UI);
	m_pObjectManager->RegisterObject(new UIBar);
	m_pObjectManager->RegisterObject(new UIHitPoint);
	m_pObjectManager->RegisterObject(new StoryIntroduction);
	m_pObjectManager->RegisterObject(new GameOver);

	//音声ファイルの読み込み
	const TCHAR* filePath = _T("../Sounds/BGM/tokiwokoete.mp3");
	m_pSoundsManager->AddFile(filePath, _T("GameBGM"));
	
	m_pSoundsManager->Start(_T("GameBGM"), true);

	return true;
}

//解放する
void GameScene::Finalize()
{
	m_pObjectManager->ReleaseObject();

	m_pCollisionManager->ReleaseCollision();

	m_pSoundsManager->Stop(_T("GameBGM"));
}


//操作を更新する
void GameScene::Update()
{
	
	//当たり判定を登録されてるのを一度解除する
	//当たり判定の登録はそれぞれのクラスで判定したいときに行う
	m_pCollisionManager->ReleaseCollision();

	//このシーンのオブジェクトの更新を行う
	m_pObjectManager->Update();

	//登録されているオブジェクトの当たり判定を行う
	m_pCollisionManager->Update();

	//カメラの更新を行う
	m_pCameraManager->Update();
}

//描画する
void GameScene::Render()
{
	//オブジェクトのRender
	m_pObjectManager->Render();
}
