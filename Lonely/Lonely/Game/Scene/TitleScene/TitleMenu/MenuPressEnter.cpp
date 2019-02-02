/**
* @file MenuPressEnter.cpp
* @brief MenuPressEnterクラスのソースファイル
* @author shion-sagawa
*/

#include "MenuPressEnter.h"
#include "TitleMenu.h"
#include "../../../../GameLib/GameLib.h"


MenuPressEnter::MenuPressEnter()
{
}

MenuPressEnter::~MenuPressEnter()
{
	Finalize();
}

//初期化する
bool MenuPressEnter::Initialize()
{
	//テクスチャー読み込み
	if (!m_texture.Load("../Graphics/pressEnter.png"))
	{
		return false;
	}

	//頂点の座標をセット
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 4 * 3
		, 200.f
		, 80.f);

	return true;
}

//解放する
void MenuPressEnter::Finalize()
{
	m_texture.Finalize();
}

//更新する
void MenuPressEnter::Update(int step)
{
	if (step == STEP1) {
		//フレーム経過で色情報を変える
		frameCount++;
		if (frameCount > 60)
		{
			static DWORD regulateColor = static_cast<DWORD>(0xffffffff);

			//カラーが一定値達したら、フレームカウントを0に戻す
			(regulateColor <= static_cast<DWORD>(0x02ffffff)) ? frameCount = 0 : frameCount;

			regulateColor -= static_cast<DWORD>(0x03000000);

			HELPER_2D->SetVerticesColor(m_vertices, regulateColor);
		}
	}
	else {

		//ステップ１以外は描画しない
		m_canRender = false;
	}
}
	

//描画する
void MenuPressEnter::Render()
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
