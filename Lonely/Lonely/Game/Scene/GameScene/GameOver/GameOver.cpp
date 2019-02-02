/**
* @file GameOver.cpp
* @brief GameOverクラスのソースファイル
* @author shion-sagawa
*/

#include "GameOver.h"
#include "../../../../GameLib/GameLib.h"

GameOver::GameOver()
{
	Initialize();
}

GameOver::~GameOver()
{
	Finalize();
}

//初期化する
bool GameOver::Initialize()
{
	m_pTexStrage = GameLib::Instance.GetTexStorage();

	//m_pTexStrage->CreateTex(_T("sumahoGamen"), _T("../Graphics/smart phone.png"));


	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());
	//頂点の座標をセット
	HELPER_2D->SetVerticesFromLeftTopType(m_vertices
		, 0
		, 0
		, static_cast<float>(WINDOW->GetWidth())
		, static_cast<float>(WINDOW->GetHeight()));

	m_vertices[0].z = 0.f;
	m_vertices[1].z = 0.f;
	m_vertices[2].z = 0.f;
	m_vertices[3].z = 0.f;

	/*if (!m_texture.Load("../Graphics/smart phone.png"))
	{
		return false;
	}*/

	return true;
}

//解放する
void GameOver::Finalize()
{
	m_texture.Finalize();
}

//更新する
void GameOver::Update()
{
	//++m_count;
	DWORD changeAlphaColor = static_cast<DWORD>(0x02000000);

	if (m_color >= static_cast<DWORD>(0x00ffffff))
	{
		m_color -= changeAlphaColor;
	}

	HELPER_2D->SetVerticesColor(m_vertices, m_color);
}

//描画する
void GameOver::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// 頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	//pDevice->SetTexture(0, m_pTexStrage->GetTex(_T("sumahoGamen")));
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

}
