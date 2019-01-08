/**
* @file CatCursor.cpp
* @brief CatCursorクラスのソースファイル
* @author shion-sagawa
*/

#include "CatCursor.h"
#include "../../../../GameLib/GameLib.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/Texture.h"


CatCursor::CatCursor()
{
	Initialize();
}

CatCursor::CatCursor(SelectCursorInformation* instance)
	: m_pSelectCursorInformation(instance)
{
	Initialize();
}

CatCursor::~CatCursor()
{
	Finalize();
}

//初期化する
bool CatCursor::Initialize()
{
	// assetsフォルダ内のbridge.pngをテクスチャーとして読み込み
	if (!m_texture.Load("../Graphics/saveframe.png"))
	{
		return false;
	}

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	// テクスチャが2の累乗でないときに効果を発揮する
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 50.f, 50.f, 380.f, 600.f, u, v);

	return true;
}

//解放する
void CatCursor::Finalize()
{
	m_texture.Finalize();
}

void CatCursor::Update()
{
	static int prevCatCursorState = DATA1;
	int catCursorState = m_pSelectCursorInformation->GetCatCursorState();


	if (catCursorState == prevCatCursorState)
	{
		return;
	}

	switch (catCursorState)
	{
	case DATA1:

		HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 50.f, 50.f);
		//if(ENTER){miniState = CONTINUE;}
		break;

	case DATA2:

		HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 450.f, 50.f);
		break;
	
	case DATA3:

		HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 850.f, 50.f);
		break;
	}

	prevCatCursorState = catCursorState;
}

void CatCursor::Render()
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
