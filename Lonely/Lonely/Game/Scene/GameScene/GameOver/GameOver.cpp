/**
* @file GameOver.cpp
* @brief GameOverクラスのソースファイル
* @author shion-sagawa
*/

#include "GameOver.h"

#include "GameLib.h"

#include "Scene/GameScene/GameOver/EnumGameOverState.h"
#include "Scene/GameScene/SharedInformation/EnumGameState.h"
#include "SceneManager/Enum_Scene.h"

GameOver::GameOver()
{
	Initialize();
}

GameOver::~GameOver()
{
	Finalize();
}

//初期化する
bool GameOver::Initialize()
{
	m_pSharedInformation = SharedInformation::Instance.GetSharedInformation();
	m_pTexStorage = GameLib::Instance.GetTexStorage();

	m_pTexStorage->CreateTex(_T("gameOver"), _T("../Graphics/Texture/gameOver.png"));
	m_pTexStorage->CreateTex(_T("backToTitle"), _T("../Graphics/Texture/backToTitle.png"));
	m_pTexStorage->CreateTex(_T("continue"), _T("../Graphics/Texture/continue.png"));



	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());
	//頂点の座標をセット
	HELPER_2D->SetVerticesFromLeftTopType(m_vertices
		, 0
		, 0
		, static_cast<float>(WINDOW->GetWidth())
		, static_cast<float>(WINDOW->GetHeight()));

	//ゲームオーバー
	HELPER_2D->SetVerticesFromCenterType(m_verticesGameOver
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 4
		, 360.f, 180.f);

	//コンテニュー
	HELPER_2D->SetVerticesFromCenterType(m_verticesContinue
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 16 * 11
		, 200.f
		, 80.f);

	//タイトルへ
	HELPER_2D->SetVerticesFromCenterType(m_verticesTitle
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 16 * 13
		, 200.f
		, 80.f);

	m_color = 0x00000000;
	HELPER_2D->SetVerticesColor(m_vertices, m_color);

	return true;
}

//解放する
void GameOver::Finalize()
{
	m_texture.Finalize();
}

//更新する
void GameOver::Update()
{
	if(m_pSharedInformation->GetGameState() != GAMEOVER)
	{ 
		return;
	}
	
	DWORD changeAlphaColor = static_cast<DWORD>(0x02000000);

	if (m_color <= static_cast<DWORD>(0x90000000))
	{
		m_color += changeAlphaColor;
	}
	else
	{
		m_finishFeedOut = true;
	}

	HELPER_2D->SetVerticesColor(m_vertices, m_color);


	if (m_finishFeedOut == false)
	{
		return;
	}

	if (m_gameOverState == BACK_TO_TITLE)
	{
		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_gameOverState = CONTINUE;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_gameOverState = CONTINUE;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			SCENEMANAGER->SwitchSceneNextFrame(TITLE_SCENE);
		}
	}
	else if (m_gameOverState == CONTINUE)
	{
		if (DIRECT_INPUT->KeyboardIsReleased(DIK_UP))
		{
			m_gameOverState = BACK_TO_TITLE;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_DOWN))
		{
			m_gameOverState = BACK_TO_TITLE;
		}
		else if (DIRECT_INPUT->KeyboardIsReleased(DIK_RETURN))
		{
			SCENEMANAGER->SwitchSceneNextFrame(GAME_SCENE);
		}
	}

}

//描画する
void GameOver::Render()
{
	if (m_pSharedInformation->GetGameState() != GAMEOVER)
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	pDevice->SetTexture(0, nullptr);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

	if (m_finishFeedOut == false)
	{
		return;
	}

	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);
	
	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("gameOver")));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesGameOver, sizeof(Simple2DVertex));

	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("backToTitle")));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesTitle, sizeof(Simple2DVertex));

	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("continue")));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesContinue, sizeof(Simple2DVertex));

}
