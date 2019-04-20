/**
* @file StoryIntroduction.cpp
* @brief StoryIntroductionクラスのソースファイル
* @author shion-sagawa
*/

#include "StoryIntroduction.h"

#include "GameLib.h"

using tstring = std::basic_string<TCHAR>;

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

	//// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	//float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	//float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	//頂点の座標をセット
	HELPER_2D->SetVerticesFromLeftTopType(m_vertices
		, 0
		, 0
		, static_cast<float>(WINDOW->GetWidth())
		, static_cast<float>(WINDOW->GetHeight()));

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices
		, 0
		, 0
		, static_cast<float>(WINDOW->GetWidth())
		, static_cast<float>(WINDOW->GetHeight()));

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
	
	//アルファ値を減算していく処理を書きたい
	//でも引き続けるとオーバーフローが起こってしまう
	//だからビット演算しないとだめでは？
	

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

	m_nextTexID = m_currentTexID + 1;
	if(m_nextTexID < TEXTURE_MAX)//2枚のストーリーページを描画する
	{ 
		//テクスチャの設定
		pDevice->SetTexture(0, m_textureKeys[m_currentTexID]);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

		pDevice->SetTexture(0, m_textureKeys[m_nextTexID]);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
	}
	else{//最後だけ2枚描画しない
		pDevice->SetTexture(0, m_textureKeys[m_currentTexID]);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
	}
}
