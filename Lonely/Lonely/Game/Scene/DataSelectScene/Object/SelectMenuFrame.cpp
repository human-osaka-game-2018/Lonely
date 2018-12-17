/**
* @file SelectMenuFrame.cpp
* @brief SelectMenuFrameクラスのソースファイル
* @author shion-sagawa
*/

#include "SelectMenuFrame.h"
#include "../../../../GameLib/GameLib.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/Texture.h"


SelectMenuFrame::SelectMenuFrame()
{
	Initialize();
}

SelectMenuFrame::SelectMenuFrame(SelectCursorInformation* instance)
	: m_pSelectCursorInformation(instance)
{
	Initialize();
}

SelectMenuFrame::~SelectMenuFrame()
{
	Finalize();
}

//初期化する
bool SelectMenuFrame::Initialize()
{
	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	// テクスチャが2の累乗でないときに効果を発揮する
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());
	
	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	DWORD color = 0xFF666699;
	DWORD backFrameColor = 0xAA000000;

	HELPER_2D->SetVerticesFromCenterType(m_vertices, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 450.f, 250.f, u, v);
	HELPER_2D->SetVerticesColor(m_vertices, color);

	HELPER_2D->SetVerticesFromCenterType(m_verticesBackFrame, 0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT);
	HELPER_2D->SetVerticesColor(m_verticesBackFrame, backFrameColor);
	
	m_canRender = false;

	return true;
}

//解放する
void SelectMenuFrame::Finalize()
{
	m_texture.Finalize();
}

void SelectMenuFrame::Update()
{
	int miniCursorState = m_pSelectCursorInformation->GetMiniCursorState();
	
	if (miniCursorState == NOT_RENDER)
	{
		m_canRender = false;
		return;
	}

	m_canRender = true;
}

void SelectMenuFrame::Render()
{
	if (m_canRender == false)
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesBackFrame, sizeof(Simple2DVertex));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
}
