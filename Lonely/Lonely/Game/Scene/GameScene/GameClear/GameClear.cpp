/**
* @file GameClear.cpp
* @brief GameClearクラスのソースファイル
* @author shion-sagawa
*/

#include "GameClear.h"

#include "GameLib.h"
#include "Scene/GameScene/SharedInformation/EnumGameState.h"
#include "SceneManager/Enum_Scene.h"

GameClear::GameClear()
{
	Initialize();
}

GameClear::~GameClear()
{
	Finalize();
}

//初期化する
bool GameClear::Initialize()
{
	m_pSharedInformation = SharedInformation::Instance.GetSharedInformation();
	m_pTexStorage = GameLib::Instance.GetTexStorage();

	//テクスチャを読み込む
	m_pTexStorage->CreateTex(m_textureKeys[0], _T("../Graphics/Texture/gameClear1.PNG"));
	m_pTexStorage->CreateTex(m_textureKeys[1], _T("../Graphics/Texture/gameClear2.PNG"));
	m_pTexStorage->CreateTex(m_textureKeys[2], _T("../Graphics/Texture/gameClear3.PNG"));
	m_pTexStorage->CreateTex(m_textureKeys[3], _T("../Graphics/Texture/gameClear4.PNG"));
	m_pTexStorage->CreateTex(m_textureKeys[4], _T("../Graphics/Texture/gameClear5.PNG"));
	

	//頂点の座標をセット
	HELPER_2D->SetVerticesFromLeftTopType(m_vertices
		, 0
		, 0
		, static_cast<float>(WINDOW->GetWidth())
		, static_cast<float>(WINDOW->GetHeight()));
	HELPER_2D->SetVerticesFromLeftTopType(m_backVertices
		, 0
		, 0
		, static_cast<float>(WINDOW->GetWidth())
		, static_cast<float>(WINDOW->GetHeight()));

	return true;
}

//解放する
void GameClear::Finalize()
{
	//テクスチャの解放を行う
	for (int i = 0; i < CLEAR_TEXTURE_MAX; ++i)
	{
		m_pTexStorage->EraseTex(m_textureKeys[i]);
	}
}

//更新する
void GameClear::Update()
{
	if (m_pSharedInformation->GetGameState() != GAMECLEAR)
	{
		return;
	}

	//アルファ値を減算する
	//減算し終わるとテクスチャ番号を進める
	if (m_nextTexNum < CLEAR_TEXTURE_MAX) 
	{
		if (HELPER_2D->DecrementVerticesAlpha(m_vertices, &m_decrementCount, 150, 120))
		{
			++m_currentTexNum;
			++m_nextTexNum;
			HELPER_2D->SetVerticesColor(m_vertices, (DWORD)0xffffffff);
		}
	}

	//エンディング終了後エンターキー入力でタイトルへ移行
	if (m_nextTexNum == CLEAR_TEXTURE_MAX)
	{
		if (DIRECT_INPUT->KeyboardIsPressed(DIK_RETURN))
		{
			SCENEMANAGER->SwitchSceneNextFrame(TITLE_SCENE);
		}
	}
}

//描画する
void GameClear::Render()
{
	if (m_pSharedInformation->GetGameState() != GAMECLEAR)
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// 頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	if (m_nextTexNum < CLEAR_TEXTURE_MAX)//2枚のストーリーページを描画する
	{
		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexStorage->GetTex(m_textureKeys[m_nextTexNum]));
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_backVertices, sizeof(Simple2DVertex));

		pDevice->SetTexture(0, m_pTexStorage->GetTex(m_textureKeys[m_currentTexNum]));
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
	}
	else {//最後だけ2枚描画しない
		pDevice->SetTexture(0, m_pTexStorage->GetTex(m_textureKeys[m_currentTexNum]));
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
	}
}
