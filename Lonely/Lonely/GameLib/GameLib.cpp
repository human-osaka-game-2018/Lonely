/**
* @file GameLib.cpp
* @brief GameLibクラスのソースファイル
* @author shion-sagawa
*/

#include "GameLib.h"

// GameLibの実体定義
GameLib GameLib::Instance;

GameLib::GameLib()
{
}

GameLib::~GameLib()
{
}

// DirectXLibの初期化
bool GameLib::Initialize(const wchar_t* pName, int width, int height, bool isFullscreen)
{
	// ウィンドウの生成
	if (!m_window.Create(pName, width, height))
	{
		return false;
	}
	// DirectXシステムの初期化
	if (!m_directX.Initialize(m_window.GetHandle(), width, height, isFullscreen))
	{
		return false;
	}
	//DirectInputの初期化
	if (!m_dxInput.Initialize(m_window.GetHandle()))
	{
		return false;
	}
	// フォントの初期化
	if (!m_font.Initialize())
	{
		return false;
	}
	//サウンドの初期化
	if (!m_soundsManager.Initialize())
	{
		return false;
	}

	// オブジェクトマネージャ


	// シーンシステムの初期化
	m_sceneManager.Initialize();
	// 入力システムの初期化
	m_input.Initialize();

	return true;
}

// DirectXLibの解放
void GameLib::Finalize()
{
	// フォントの解放
	m_font.Finalize();
	// 入力システムの解放
	m_input.Finalize();
	// サウンドマネージャの解放
	SoundLibCWrapper_Free();
	// オブジェクトマネージャの解放
	m_objectManager.Finalize();
	// シーンシステムの解放
	m_sceneManager.Finalize();
	// DirectXの解放
	m_directX.Finalize();
}

// メインループ
void GameLib::MainLoop()
{
	while (!m_window.IsQuitMessage())
	{
		if (!m_window.UpdateMessage())
		{
			//入力情報を更新する
			m_dxInput.UpdataInputState();

			//シーンの更新
			m_sceneManager.Update();

			//このフレームで入力された情報を保存する
			m_dxInput.StorePrevInputState();

			// 画面のクリア
			m_directX.ClearBackBuffer(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER /*| D3DCLEAR_STENCIL*/, 0xFF000000, 1.0f, 0);

			//描画可能状態にする
			m_directX.BeginRenderScene();
				
			// デフォルト描画設定
			m_directX.SetDefaultRenderState();

			// シーンの描画
			m_sceneManager.Render();

			//描画不可能状態にする
			m_directX.EndRenderScene();
			
			// 画面の表示
			m_directX.FlipDisp();
		}
	}
}
