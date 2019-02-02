/**
* @file UI.cpp
* @brief UIクラスのソースファイル
* @author shion-sagawa
*/

#include "UI.h"
#include "../../../../GameLib/GameLib.h"

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
	//m_pTexStrage = GameLib::Instance.GetTexStorage();

	//m_pTexStrage->CreateTex(_T("sumahoGamen"), _T("../Graphics/smart phone.png"));

	// assetsフォルダ内のbridge.pngをテクスチャーとして読み込み
	if (!m_texture.Load("../Graphics/smart phone.png"))
	{
		return false;
	}

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	//頂点の座標をセット
	HELPER_2D->SetVerticesFromLeftTopType(m_vertices
		, 30
		, 30
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
}

//描画する
void UI::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();
	pDirectX->SetRenderMode(DirectX::Normal, true);

	// 頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	//pDevice->SetTexture(0, m_pTexStrage->GetTex(_T("sumahoGamen")));
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

}
