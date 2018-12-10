/**
* @file UI.cpp
* @brief UIクラスのソースファイル
* @author 佐川　嗣苑
*/

#include "UI.h"
#include "../../../GameLib/GameLib.h"

UI::UI()
{
	Initialize();
}

UI::~UI()
{
	Finalize();
}

//初期化する
bool UI::Initialize()
{
	// assetsフォルダ内のbridge.pngをテクスチャーとして読み込み
	if (!m_texture.Load("../Graphics/TitleLogo.png"))
	{
		return false;
	}

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>((float)m_texture.GetHeight());

	//頂点の座標をセット
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 4
		, logoWidth, logoHeight);

	return true;
}

//解放する
void UI::Finalize()
{
	m_texture.Finalize();
}

//更新する
void UI::Update()
{
	//毎フレーム、一定値までロゴを大きくする処理
	if (logoWidth <= 200.f)
	{
		logoHeight += 4.f;
		logoWidth += 6.f;

		//頂点の座標をセット
		HELPER_2D->SetVerticesFromCenterType(m_vertices
			, static_cast<float>(WINDOW->GetWidth()) / 2
			, static_cast<float>(WINDOW->GetHeight()) / 3
			, logoWidth, logoHeight);

	}
}

void UI::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

}
