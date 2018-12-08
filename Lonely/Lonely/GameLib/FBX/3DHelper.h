/**
* @file 3DHelper.h
* @brief 3DHelperクラスのヘッダファイル
* @author 佐川 嗣苑
*/

#pragma once

#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "d3dx9math.h"

#define FVF_SIMPLE_3D		(D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define FVF_SIMPLE_TEX_3D   (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	FVF_MESH_VERTEX		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_DIFFUSE);
#define	FVF_MESH_TEX_VERTEX	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_DIFFUSE);


/** 
* @brief シンプルな頂点情報
*/
struct SimpleVertex
{
	float x, y, z;
	DWORD color;
};

/** 
* @brief シンプルなテクスチャ―付き頂点情報
*/
struct SimpleTexVertex
{
	float x, y, z;
	DWORD color;
	float u, v;
};

/**
* @brief 
*/
struct MeshVertex
{
	float x, y, z;
	float nx, ny, nz;
	DWORD color;
	float u, v;

	// スキンメッシュ用
	BYTE index[4];
	float weight[4];
};

struct MaterialData
{
	Texture			texture;	        // テクスチャ―
	D3DMATERIAL9	material;		    // マテリアル
};


/** 
* @brief モデル情報
*/
struct MeshData
{
	UINT				fvf;			// フォーマット
	D3DPRIMITIVETYPE	primType;		// プリミティブの描画方法
	UINT				primNum;		// プリミティブ数
	UINT				vertexNum;		// 頂点数
	UINT				vertexStride;	// 1頂点辺りのサイズ
	UINT				indexNum;		// インデックス数
	UINT				materialIndex;	// マテリアル番号

	VertexBuffer		vertexBuffer;	// 要点バッファ
	IndexBuffer			indexBuffer;	// インデックスバッファ
};


/** 
* @brief モデルクラス
*/
class Model
{
public:

	Model();
	~Model();


	// 初期化
	bool Initialize(UINT meshNum, UINT materialNum);
	// 解放
	virtual void Finalize();

	// 描画
	virtual void Render();

	// メッシュ数の取得
	UINT GetMeshNum() const { return m_meshNum; }
	// マテリアル数の取得
	UINT GetMaterialNum() const { return m_materialNum; }
	// ワールド行列の取得
	MeshData* GetMesh(UINT i) { return &m_pMesh[i]; }
	// ワールド行列の取得
	MaterialData* GetMaterial(UINT i) { return &m_pMaterial[i]; }

	// ワールド行列の取得
	D3DXMATRIX* GetWorld() { return &m_world; }

public:
	// モデルの生成
	bool CreateTriangle();
	// モデルの生成
	bool Create3DAxis(bool x = true, bool y = true, bool z = true);
	// モデルの生成
	bool CreateShpere(int divideCount = 24, const char* pTexturePath = NULL);

	// フラスタム領域風モデル(ワイヤーフレーム)の生成
	bool CreateViewFrustum();
	// カメラ風モデル(ワイヤーフレーム)の生成
	bool CreateCamera();


	// 線の当たり判定
	int RayPick(const D3DXVECTOR3* pPos, const D3DXVECTOR3* pVec, float* pDist, D3DXVECTOR3* pOut);

private:
	// 線の当たり判定
	int RayPick(UINT i, const D3DXVECTOR3* pPos, const D3DXVECTOR3* pVec, D3DXVECTOR3* pOut);
	// 線の当たり判定
	bool RayPickTriangle(const D3DXVECTOR3* pTriangle, D3DXVECTOR3 pos, D3DXVECTOR3 vec, D3DXVECTOR3* pOut, float* pDist);

	// マテリアルの初期化
	virtual void InitMaterial();

protected:

	UINT			m_meshNum;		// メッシュ数
	UINT			m_materialNum;	// マテリアル数

	MeshData*		m_pMesh;		// メッシュ情報
	MaterialData*	m_pMaterial;	// マテリアル情報
	D3DXMATRIX		m_world;		// ワールドマトリックス
};
