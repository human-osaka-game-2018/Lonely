/**
* @file Data1.cpp
* @brief Data1クラスのソースファイル
* @author shion-sagawa
*/

#include "Data1.h"
#include "../../../GameLib/GameLib.h"
#include "../../../GameLib/DirectX/DirectX.h"
#include "../../../GameLib/2DHelper/2DHelper.h"
#include "../../../GameLib/FBX/Texture.h"


Data1::Data1()
{
	Initialize();
}

Data1::~Data1()
{
	Finalize();
}

//初期化する
bool Data1::Initialize()
{
	// assetsフォルダ内のbridge.pngをテクスチャーとして読み込み
	if (!m_texture.Load("../Graphics/Title_BG.jpg"))
	{
		return false;
	}

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	// テクスチャが2の累乗でないときに効果を発揮する
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 400.f, 400.f, 500.f, 700.f, u, v);

	return true;
}

//解放する
void Data1::Finalize()
{
	m_texture.Finalize();
}

void Data1::Update()
{
}

void Data1::Render()
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
