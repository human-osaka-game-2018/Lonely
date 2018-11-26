/**
* @file TitleBackGround.cpp
* @brief TitleBackGroundクラスのソースファイル
* @author 佐川　嗣苑
*/

#include "TitleBackGround.h"
#include "../../../GameLib/GameLib.h"

TitleBackGround::TitleBackGround()
{
	Initialize();
}

TitleBackGround::~TitleBackGround()
{
	Finalize();
}

//初期化する
bool TitleBackGround::Initialize()
{
	// assetsフォルダ内のbridge.pngをテクスチャーとして読み込み
	if (!m_texture.Load("../Grafics/Title_BG"))
	{
		return false;
	}
	// 画像サイズから幅と高さを設定
	float rect[] =
	{
		10.0f, 10.0f,
		10.0f + (float)m_texture.GetSrcWidth(), 10.0f + (float)m_texture.GetSrcHeight(),
	};
	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	float u = (float)m_texture.GetSrcWidth() / (float)m_texture.GetWidth();
	float v = (float)m_texture.GetSrcHeight() / (float)m_texture.GetHeight();
	// 画像サイズに合わせてUVも追加した頂点データ
	const Simple2DVertex vertices[4] =
	{
		// 1つ目の矩形
		{ rect[0], rect[1], 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
	{ rect[2], rect[1], 0.0f, 1.0f, 0xffffffff,    u, 0.0f },
	{ rect[0], rect[3], 0.0f, 1.0f, 0xffffffff, 0.0f,    v },
	{ rect[2], rect[3], 0.0f, 1.0f, 0xffffffff,    u,    v },
	};
	// 頂点バッファの生成
	if (!m_vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}
	return true;
}

//解放する
void TitleBackGround::Finalize()
{
	m_texture.Finalize();
	m_vertexBuffer.Finalize();
}

void TitleBackGround::Update()
{
	////ワールドトランスフォーム（絶対座標変換）
	//D3DXMATRIXA16 matWorld, matPosition;
	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixTranslation(&matPosition, pThing->vecPosition.x, pThing->vecPosition.y,
	//	pThing->vecPosition.z);
	//D3DXMatrixMultiply(&matWorld, &matWorld, &matPosition);
	//pDevice->SetTransform(D3DTS_WORLD, &matWorld);
}

void TitleBackGround::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//通常書き込みモード
	pDirectX->SetRenderMode(DirectX::Normal, false);

	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//頂点バッファの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, m_vertexBuffer.GetBuffer(), 0, sizeof(Simple2DVertex));

	//描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//// レンダリング	 
	//for (DWORD i = 0; i<pThing->dwNumMaterials; i++)
	//{
	//	if (pThing->exsists == false) {
	//		continue;
	//	}

	//	pDevice->SetMaterial(&pThing->pMeshMaterials[i]);
	//	pDevice->SetTexture(0, pThing->pMeshTextures[i]);
	//	pThing->pMesh->DrawSubset(i);
	//}
}