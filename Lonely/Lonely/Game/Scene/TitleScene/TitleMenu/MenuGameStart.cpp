/**
* @file MenuGameStart.cpp
* @brief MenuGameStartクラスのソースファイル
* @author shion-sagawa
*/

#include "MenuGameStart.h"

#include "GameLib.h"
#include "TitleMenu.h"

MenuGameStart::MenuGameStart()
{
}

MenuGameStart::~MenuGameStart()
{
	Finalize();
}

//初期化する
bool MenuGameStart::Initialize()
{
	//テクスチャー読み込み
	if (!m_texture.Load("../Graphics/Texture/gameStart.png"))
	{
		return false;
	}

	//頂点情報を設定する
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 16 * 11
		, 200.f
		, 80.f);

	//始めは描画しない
	m_canRender = false;

	return true;
}

//解放する
void MenuGameStart::Finalize()
{
	m_texture.Finalize();
}

//更新する
void MenuGameStart::Update(int step)
{
	if (step != STEP1)
	{
		//ステップ１以外は描画する
		m_canRender = true;
	}
}

//描画する
void MenuGameStart::Render()
{
	if (m_canRender == false)
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
}
