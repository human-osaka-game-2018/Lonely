/**
* @file MenuGameEnd.cpp
* @brief MenuGameEndクラスのソースファイル
* @author shion-sagawa
*/

#include "MenuGameEnd.h"
#include "TitleMenu.h"
#include "../../../../GameLib/GameLib.h"


MenuGameEnd::MenuGameEnd()
{
}

MenuGameEnd::~MenuGameEnd()
{
	Finalize();
}

//初期化する
bool MenuGameEnd::Initialize()
{
	//テクスチャー読み込み
	if (!m_texture.Load("../Graphics/gameEnd.png"))
	{
		return false;
	}

	//頂点の座標をセット
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 16 * 13 
		, 200.f
		, 80.f);

	//始めは描画しない
	canRender = false;

	return true;
}

//解放する
void MenuGameEnd::Finalize()
{
	m_texture.Finalize();
}

//更新する
void MenuGameEnd::Update(int step)
{
	if (step != STEP1)
	{
		//ステップ１以外は描画する
		canRender = true;
	}
}

//描画する
void MenuGameEnd::Render()
{
	if (canRender == false)
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
