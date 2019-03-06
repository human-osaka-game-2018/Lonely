/**
* @file UIBattery.cpp
* @brief UIBatteryクラスのソースファイル
* @author shion-sagawa
*/

#include "UIBattery.h"
#include "../../../../GameLib/GameLib.h"

UIBattery::UIBattery()
{
	Initialize();
}

UIBattery::~UIBattery()
{
	Finalize();
}

//初期化する
bool UIBattery::Initialize()
{
	/*if (!m_texture.Load("../Graphics/UIFootsteps.png"))
	{
		return false;
	}*/

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 150.f, WINDOW_HEIGHT - 90.f, 400.f, 35.f);

	return true;
}

//解放する
void UIBattery::Finalize()
{
	m_texture.Finalize();
}

void UIBattery::Update()
{
}

void UIBattery::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

	//充電が何％かを描画する
	DEBUGFONT->DrawText(50, 680, 0xffffffff, "100%");
}
