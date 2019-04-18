/**
* @file TitleLogo.cpp
* @brief TitleLogoクラスのソースファイル
* @author shion-sagawa
*/

#include "TitleLogo.h"

#include "GameLib.h"

TitleLogo::TitleLogo()
{
	Initialize();
}

TitleLogo::~TitleLogo()
{
	Finalize();
}

//初期化する
bool TitleLogo::Initialize()
{
	//テクスチャ読み込み
	if (!m_texture.Load("../Graphics/Texture/TitleLogo.png"))
	{
		return false;
	}

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	//頂点の座標を設定する
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth())/2
		, static_cast<float>(WINDOW->GetHeight())/4
		, logoWidth, logoHeight);

	return true;
}

//解放する
void TitleLogo::Finalize()
{
	m_texture.Finalize();
}

//更新する
void TitleLogo::Update()
{
	//毎フレーム、一定値までロゴを大きくする処理
	if (logoWidth <= 480.f) 
	{
		logoHeight += 3.0f;
		logoWidth += 5.5f;

		//頂点の座標をセット
		HELPER_2D->SetVerticesFromCenterType(m_vertices
			, static_cast<float>(WINDOW->GetWidth()) / 2
			, static_cast<float>(WINDOW->GetHeight()) / 3 - 25
			, logoWidth, logoHeight);
		
	}
}

void TitleLogo::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

}
