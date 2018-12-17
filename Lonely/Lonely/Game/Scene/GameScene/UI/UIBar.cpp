/**
* @file UIBar.cpp
* @brief UIBarクラスのソースファイル
* @author shion-sagawa
*/

#include "UIBar.h"
#include "../../../../GameLib/GameLib.h"

UIBar::UIBar()
{
	Initialize();
}

UIBar::~UIBar()
{
	Finalize();
}

//初期化する
bool UIBar::Initialize()
{

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	// テクスチャが2の累乗でないときに効果を発揮する
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 0.f, WINDOW_HEIGHT-100.f, WINDOW_WIDTH, 100, u, v);

	//矩形の色情報を変える
	DWORD color = 0xff666699;
	HELPER_2D->SetVerticesColor(m_vertices, color);

	return true;
}

//解放する
void UIBar::Finalize()
{
	m_texture.Finalize();
}

void UIBar::Update()
{
}

void UIBar::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
}
