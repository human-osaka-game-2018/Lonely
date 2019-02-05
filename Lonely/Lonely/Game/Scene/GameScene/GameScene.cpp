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
#include "../../../GameLib/GameLib.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	Finalize();
}

void GameScene::Load()
{
	//ゲームシーンでどのカメラを使うか設定する
	m_pCameraManager->ChangeCamera(new TestCamera());

	//ObjectManagerのVector配列にゲームシーンで使うクラスを登録する
	m_pObjectManager->RegisterObject(new Sumahoneko());
	m_pObjectManager->RegisterObject(new UIBar());
	m_pObjectManager->RegisterObject(new UIFootsteps());
	m_pObjectManager->RegisterObject(new UIWaves());
	m_pObjectManager->RegisterObject(new UIHitPoint());
	m_pObjectManager->RegisterObject(new UIBattery());
	m_pObjectManager->RegisterObject(new UI());

	m_loadIsFinished = true;
}

//初期化する
bool GameScene::Initialize()
{
	m_loadIsFinished = false;

	m_catPawframecount = 0;
	m_catPawRendercount = 0;

	if (!m_texture.Load("../Graphics/loadBG.png"))
	{
		return false;
	}

	if (!m_catPaw.Load("../Graphics/catPaw.png"))
	{
		return false;
	}

	if (!m_loading.Load("../Graphics/loading.png"))
	{
		return false;
	}

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	// テクスチャが2の累乗でないときに効果を発揮する
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT, u, v);

	HELPER_2D->SetVerticesFromLeftTopType(m_loadingvertices, 750.f, 535.f, 512.f, 256.f);

	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[0].vertex, 20.f, 510.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[1].vertex, 220.f, 510.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[2].vertex, 370.f, 340.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[3].vertex, 570.f, 390.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[4].vertex, 580.f, 210.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[5].vertex, 780.f, 215.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[6].vertex, 920.f, 60.f, 170.f, 170.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_catPawvertices[7].vertex, 1120.f, 50.f, 170.f, 170.f);


	// SoundsManagerインスタンス生成後に1度のみ行う。
	bool isSuccess = soundsManager.Initialize();
	// 音声ファイルオープン
	// 第2引数は音声ファイルを識別するための任意の文字列をキーとして指定する。
	// この後の操作関数の呼び出し時には、ここで設定したキーを指定して音声を識別する。

	const TCHAR* filePath = _T("../Sounds/BGM/GameBGM.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("GameBGM"));

	m_loadImageThread = std::thread(&GameScene::Load, this);

	return true;
}

//解放する
void GameScene::Finalize()
{
	m_pObjectManager->ReleaseObject();

	bool isSuccess = soundsManager.Stop(_T("GameBGM"));
	SoundLibCWrapper_Free();

	if (m_loadImageThread.joinable())
	{
		m_loadImageThread.join();
	}
}


//操作を更新する
void GameScene::Update()
{
	if (m_loadIsFinished == false)
	{
		m_catPawframecount++;
		return;
	}

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
	if (m_loadIsFinished == false)
	{
		IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();

		//頂点に入れるデータを設定
		pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_texture.GetD3DTexture());

		//描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

		//テクスチャの設定
		pDevice->SetTexture(0, m_loading.GetD3DTexture());

		//描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_loadingvertices, sizeof(Simple2DVertex));

		//テクスチャの設定
		pDevice->SetTexture(0, m_catPaw.GetD3DTexture());

		if (m_catPawframecount == 20)
		{
			m_catPawRendercount++;
			m_catPawframecount = 0;
		}

		if (m_catPawRendercount == 9)
		{
			m_catPawRendercount = 0;
		}

		//描画
		for (int i = 0; i < m_catPawRendercount; i++)
		{
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_catPawvertices[i].vertex, sizeof(Simple2DVertex));
		}
		
		return;
	}
	
	//オブジェクトのRender
	m_pObjectManager->Render();
	
}
