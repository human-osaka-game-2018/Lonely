/**
* @file MiniCursor.cpp
* @brief MiniCursorクラスのソースファイル
* @author shion-sagawa
*/

#include "MiniCursor.h"
#include "../../../../GameLib/GameLib.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/Texture.h"


MiniCursor::MiniCursor()
{
	Initialize();
}

MiniCursor::MiniCursor(SelectCursorInformation* instance)
	: m_pSelectCursorInformation(instance)
{
	Initialize();
}

MiniCursor::~MiniCursor()
{
	Finalize();
}

//初期化する
bool MiniCursor::Initialize()
{
	// assetsフォルダ内のbridge.pngをテクスチャーとして読み込み
	if (!m_texture.Load("../Graphics/menuCursor.png"))
	{
		return false;
	}

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	// テクスチャが2の累乗でないときに効果を発揮する
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 50.f, 100.f, 75.f, 75.f, u, v);

    m_canRender = false;

	return true;
}

//解放する
void MiniCursor::Finalize()
{
	m_texture.Finalize();
}

void MiniCursor::Update()
{
	static int prevMiniCursorState = CONTINUE;
	int miniCursorState = m_pSelectCursorInformation->GetMiniCursorState();

	if (miniCursorState == prevMiniCursorState)
	{
		return;
	}

	m_canRender = true;

	switch (miniCursorState)
	{
	case CONTINUE:

		HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 220.f, 150.f);
		//if(ENTER){miniState = CONTINUE;}
		break;

	case NEWGAME:

		HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 220.f, 350.f);
		break;

	case BACK:

		HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 220.f, 550.f);
		break;

	case NOT_RENDER:

		m_canRender = false;
		break;
	}

	prevMiniCursorState = miniCursorState;
}

void MiniCursor::Render()
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
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
}
