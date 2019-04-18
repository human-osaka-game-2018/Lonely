/**
* @file MenuCursor.cpp
* @brief MenuCursorクラスのソースファイル
* @author shion-sagawa
*/

#include "MenuCursor.h"

#include "GameLib.h"
#include "TitleMenu.h"

MenuCursor::MenuCursor()
{
}

MenuCursor::~MenuCursor()
{
	Finalize();
}

//初期化する
bool MenuCursor::Initialize()
{
	//テクスチャー読み込み
	if (!m_texture.Load("../Graphics/Texture/menuCursor.png"))
	{
		return false;
	}

	//頂点情報を設定する
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 16 * 13
		, 30.f
		, 30.f);

	//始めは描画しない
	m_canRender = false;

	return true;
}

//解放する
void MenuCursor::Finalize()
{
	m_texture.Finalize();
}

//更新する
void MenuCursor::Update(int step)
{
	if (step == STEP1)
	{
		//ステップ１は描画しない
		m_canRender = false;
	}
	if (step == STEP2)
	{
		//描画する
		m_canRender = true;
		//頂点の座標をセット
		HELPER_2D->SetVerticesFromCenterType(m_vertices
			, static_cast<float>(WINDOW->GetWidth()) / 3
			, static_cast<float>(WINDOW->GetHeight()) / 16 * 11
			, 30.f
			, 30.f);
	}
	if (step == STEP3)
	{
		//描画する
		m_canRender = true;
		//頂点の座標をセット
		HELPER_2D->SetVerticesFromCenterType(m_vertices
			, static_cast<float>(WINDOW->GetWidth()) / 3
			, static_cast<float>(WINDOW->GetHeight()) / 16 * 13
			, 30.f
			, 30.f);
	}
}

//描画する
void MenuCursor::Render()
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
