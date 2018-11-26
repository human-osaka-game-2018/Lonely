/**
* @file GameLib.cpp
* @brief GameLibクラスのソースファイル
* @author 佐川　嗣苑
*/

#include "GameLib.h"

// DirectXLibの実体定義
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
	// フォントの初期化
	if (!m_font.Initialize())
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
void GameLib::Finalize(void)
{
	// フォントの解放
	m_font.Finalize();
	// 入力システムの解放
	m_input.Finalize();
	//オブジェクトマネージャの解放
	m_objectManager.Finalize();
	// シーンシステムの解放
	m_sceneManager.Finalize();
	// DirectXの解放
	m_directX.Finalize();
}

// メインループ
void GameLib::MainLoop(void)
{
	// メインループ
	while (!m_window.IsQuitMessage())
	{
		if (!m_window.UpdateMessage())
		{
			// 入力の更新
			m_input.Update();
			// シーンの更新
			m_sceneManager.Update();

			// 描画
			{
				m_directX.BeginRenderScene();

				// 画面のクリア
				m_directX.ClearBackBuffer(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
				// デフォルト描画設定の設定
				m_directX.SetDefaultRenderState();

				// シーンの描画
				m_sceneManager.Render();

				m_directX.EndRenderScene();
			}
			// 画面の表示
			m_directX.FlipDisp();
		}
	}
}