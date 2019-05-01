/**
* @file StoryIntroduction.cpp
* @brief StoryIntroductionクラスのソースファイル
* @author shion-sagawa
*/

#include "StoryIntroduction.h"

#include "GameLib.h"
#include "Scene/GameScene/SharedInformation/EnumGameState.h"

StoryIntroduction::StoryIntroduction()
{
	Initialize();
}

StoryIntroduction::~StoryIntroduction()
{
	Finalize();
}

//初期化する
bool StoryIntroduction::Initialize()
{
	m_pSharedInformation = SharedInformation::Instance.GetSharedInformation();
	m_pTexStorage = GameLib::Instance.GetTexStorage();
	
	//テクスチャを読み込む
	m_pTexStorage->CreateTex(m_textureKeys[0], _T("../Graphics/Texture/story1.png"));
	m_pTexStorage->CreateTex(m_textureKeys[1], _T("../Graphics/Texture/story2.png"));
	m_pTexStorage->CreateTex(m_textureKeys[2], _T("../Graphics/Texture/story3.png"));
	m_pTexStorage->CreateTex(m_textureKeys[3], _T("../Graphics/Texture/story4.png"));
	m_pTexStorage->CreateTex(m_textureKeys[4], _T("../Graphics/Texture/story5.png"));
	m_pTexStorage->CreateTex(m_textureKeys[5], _T("../Graphics/Texture/story6.png"));
	m_pTexStorage->CreateTex(m_textureKeys[6], _T("../Graphics/Texture/story7.png"));
	m_pTexStorage->CreateTex(m_textureKeys[7], _T("../Graphics/Texture/story8.png"));
	m_pTexStorage->CreateTex(m_textureKeys[8], _T("../Graphics/Texture/story9.png"));
	m_pTexStorage->CreateTex(_T("A_SKIP"), _T("../Graphics/Texture/A_SKIP.png"));

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

	HELPER_2D->SetVerticesFromLeftTopType(m_skipVertices
		, static_cast<float>(WINDOW->GetWidth()) - 130
		, static_cast<float>(WINDOW->GetHeight()) - 100
		, 100
		, 80);

	return true;
}

//解放する
void StoryIntroduction::Finalize()
{
	//テクスチャの解放を行う
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		m_pTexStorage->EraseTex(m_textureKeys[i]);
	}
}

//更新する
void StoryIntroduction::Update()
{
	if (m_pSharedInformation->GetGameState() != STORY_INTRODUCTION)
	{
		return;
	}
	
	//長押ししたら物語背景導入をSKIPできる
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_A))
	{
		++m_heldKeyCount;
		if (m_heldKeyCount >= 60)
		{
			m_pSharedInformation->SetGameState(PLAY);
		}
	}
	else
	{
		m_heldKeyCount = 0;
	}

	//Skip可能ボタンを点滅させる処理
	HELPER_2D->DecrementVerticesAlpha(m_skipVertices, &m_decrSkipCount, 90, 60, true);

	//アルファ値を減算する
	//減算し終わるとテクスチャ番号を進める
	if (HELPER_2D->DecrementVerticesAlpha(m_vertices, &m_decrementCount, 300, 270))
	{
		++m_currentTexNum;
		++m_nextTexNum;
		HELPER_2D->SetVerticesColor(m_vertices, (DWORD)0xffffffff);
	}

	//テクスチャが最後まで描画されたらゲームプレイへ移行
	if (m_currentTexNum == TEXTURE_MAX)
	{
		m_pSharedInformation->SetGameState(PLAY);
	}
}

//描画する
void StoryIntroduction::Render()
{
	if (m_pSharedInformation->GetGameState() != STORY_INTRODUCTION)
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// 頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	if(m_nextTexNum < TEXTURE_MAX)//2枚のストーリーページを描画する
	{ 
		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexStorage->GetTex(m_textureKeys[m_nextTexNum]));
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_backVertices, sizeof(Simple2DVertex));

		pDevice->SetTexture(0, m_pTexStorage->GetTex(m_textureKeys[m_currentTexNum]));
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
	}
	else{//最後だけ2枚描画しない
		pDevice->SetTexture(0, m_pTexStorage->GetTex(m_textureKeys[m_currentTexNum]));
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
	}

	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("A_SKIP")));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_skipVertices, sizeof(Simple2DVertex));
}
