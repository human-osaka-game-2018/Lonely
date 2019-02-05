/**
* @file UIHitPoint.cpp
* @brief UIHitPointクラスのソースファイル
* @author shion-sagawa
*/

#include "UIHitPoint.h"
#include "../../../../GameLib/GameLib.h"

UIHitPoint::UIHitPoint()
	: m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
{
	Initialize();
}

UIHitPoint::~UIHitPoint()
{
	Finalize();
}

//初期化する
bool UIHitPoint::Initialize()
{
	// assetsフォルダ内のbridge.pngをテクスチャーとして読み込み
	if (!m_texture.Load("../Graphics/Texture/UIHitPoint.png"))
	{
		return false;
	}

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	// テクスチャが2の累乗でないときに効果を発揮する
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 600.f, WINDOW_HEIGHT-100.f, 300.f, 50.f, 347.f/2048.f, 137.f/512.f, 0.f ,0.f);

	return true;
}

//解放する
void UIHitPoint::Finalize()
{
	m_texture.Finalize();
}

void UIHitPoint::Update()
{
	m_hp = m_pSharedInformation->GetHp();
	if (m_hp == 3)
	{
	}
	else if (m_hp == 2)
	{
		HELPER_2D->SetVerticesTuTv(m_vertices, 695.f / 2048.f, 137.f / 512.f, 348.f / 2048.f, 0.f);
	}
	else if (m_hp == 1)
	{
		HELPER_2D->SetVerticesTuTv(m_vertices, 1043.f / 2048.f, 137.f / 512.f, 696.f / 2048.f, 0.f);
	}
	else if (m_hp == 0)
	{
		HELPER_2D->SetVerticesTuTv(m_vertices, 1391.f / 2048.f, 137.f / 512.f, 1044.f / 2048.f, 0.f);
	}
	
}

void UIHitPoint::Render()
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
