/**
* @file 3DHelper.cpp
* @brief 3DHelperクラスのソースファイル
* @author 佐川 嗣苑
*/


#include "3DHelper.h"
#include "../GameLib.h"
#include <windows.h>
#include <stdio.h>
#include <d3dx9.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dinput8.lib")

Model::Model(void)
	: m_meshNum(0)
	, m_materialNum(0)
	, m_pMesh(NULL)
	, m_pMaterial(NULL)
{
}

Model::~Model(void)
{
	Finalize();
}

bool Model::Initialize(UINT meshNum, UINT materialNum)
{
	Finalize();

	m_meshNum = meshNum;
	m_materialNum = materialNum;

	m_pMesh = new MeshData[meshNum];
	m_pMaterial = new MaterialData[materialNum];
	ZeroMemory(m_pMesh, sizeof(MeshData) * meshNum);
	ZeroMemory(m_pMaterial, sizeof(MaterialData) * materialNum);

	InitMaterial();
	D3DXMatrixIdentity(&m_world);
	return true;
}

// モデルの解放
void Model::Finalize(void)
{
	SAFE_DELETE_ARRAY(m_pMesh);
	SAFE_DELETE_ARRAY(m_pMaterial);
}

// マテリアル情報の初期化
void Model::InitMaterial(void)
{
	D3DMATERIAL9 material;
	//	材質設定
	//	アンビエント(環境)カラー
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	//	ディフューズ(素材の)カラー
	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 1.0f;
	material.Diffuse.b = 1.0f;
	material.Diffuse.a = 1.0f;
	//	スペキュラー（テカり）カラー
	material.Specular.r = 1.0f;
	material.Specular.g = 1.0f;
	material.Specular.b = 1.0f;
	material.Specular.a = 1.0f;
	material.Power = 15.0f;
	//	エミッシブ（発光）
	material.Emissive.r = 0.0f;
	material.Emissive.g = 0.0f;
	material.Emissive.b = 0.0f;
	material.Emissive.a = 0.0f;

	for (UINT i = 0; i < m_materialNum; i++)
	{
		GetMaterial(i)->material = material;
	}
}

// モデルの生成
bool Model::CreateTriangle(void)
{
	float width = 1.0f;
	float height = sqrtf(3.0f) * width;
	// 画像サイズに合わせてUVも追加した頂点データ
	const SimpleVertex vertices[] =
	{
		{ -width,	0.0f,	0.0f,		0xffafafff },
	{ 0.0f,		0.0f,	height,		0xffafafff },
	{ width,	0.0f,	0.0f,		0xffafafff },
	};

	Initialize(1, 1);
	// 頂点バッファの生成
	MeshData* pMesh = GetMesh(0);
	if (!pMesh->vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}

	pMesh->fvf = FVF_SIMPLE_3D;
	pMesh->primType = D3DPT_TRIANGLESTRIP;
	pMesh->primNum = ARRAYSIZE(vertices) - 2;
	pMesh->vertexNum = ARRAYSIZE(vertices);
	pMesh->vertexStride = sizeof(SimpleVertex);
	pMesh->indexNum = 0;
	pMesh->materialIndex = 0;

	return true;
}

// モデルの生成
bool Model::Create3DAxis(bool x, bool y, bool z)
{
	const float width = 0.002f;
	const float height = 0.15f;
	const float top_width = width * 4;
	const float top = 0.17f;
	const float adjust = 0.0f;//-0.05f;

	D3DCOLOR flag = 0xffffffff;

	D3DXVECTOR3 vec(adjust, 0.0f, height);
	D3DXVec3Normalize(&vec, &vec);
	// 頂点データ
	const SimpleVertex vertices[] =
	{
		// Xの軸
		{ 0.0f,				-width,			-width,		0xffff0000 & (x ? flag : 0) },
	{ 0.0f,				-width,			 width,		0xffff0000 & (x ? flag : 0) },
	{ 0.0f,				 width,			 width,		0xffff0000 & (x ? flag : 0) },
	{ 0.0f,				 width,			-width,		0xffff0000 & (x ? flag : 0) },
	{ height,			-width,			-width,		0xffff0000 & (x ? flag : 0) },
	{ height,			-width,			 width,		0xffff0000 & (x ? flag : 0) },
	{ height,			 width,			 width,		0xffff0000 & (x ? flag : 0) },
	{ height,			 width,			-width,		0xffff0000 & (x ? flag : 0) },
	// Xの矢印
	{ height,			-top_width,	-top_width,		0xffff0000 & (x ? flag : 0) },
	{ height,			-top_width,	 top_width,		0xffff0000 & (x ? flag : 0) },
	{ height,			 top_width,	 top_width,		0xffff0000 & (x ? flag : 0) },
	{ height,			 top_width,	-top_width,		0xffff0000 & (x ? flag : 0) },
	{ top,					  0.0f,		  0.0f,		0xffff0000 & (x ? flag : 0) },

	// Yの軸
	{ -width,			0.0f,			-width,		0xff00ff00 & (y ? flag : 0) },
	{ -width,			0.0f,			 width,		0xff00ff00 & (y ? flag : 0) },
	{ width,			0.0f,			 width,		0xff00ff00 & (y ? flag : 0) },
	{ width,			0.0f,			-width,		0xff00ff00 & (y ? flag : 0) },
	{ -width,			height,			-width,		0xff00ff00 & (y ? flag : 0) },
	{ -width,			height,			 width,		0xff00ff00 & (y ? flag : 0) },
	{ width,			height,			 width,		0xff00ff00 & (y ? flag : 0) },
	{ width,			height,			-width,		0xff00ff00 & (y ? flag : 0) },
	// Yの矢印
	{ -top_width,		height,		-top_width,		0xff00ff00 & (y ? flag : 0) },
	{ -top_width,		height,		 top_width,		0xff00ff00 & (y ? flag : 0) },
	{ top_width,		height,		 top_width,		0xff00ff00 & (y ? flag : 0) },
	{ top_width,		height,		-top_width,		0xff00ff00 & (y ? flag : 0) },
	{ 0.0f,			top,			  0.0f,		0xff00ff00 & (y ? flag : 0) },

	// Zの軸
	{ -width,			-width,		0.0f,					0xff0000ff & (z ? flag : 0) },
	{ -width,			 width,		0.0f,					0xff0000ff & (z ? flag : 0) },
	{ width,			 width,		0.0f,					0xff0000ff & (z ? flag : 0) },
	{ width,			-width,		0.0f,					0xff0000ff & (z ? flag : 0) },
	{ -width + adjust,	-width,		height,					0xff0000ff & (z ? flag : 0) },
	{ -width + adjust,	 width,		height,					0xff0000ff & (z ? flag : 0) },
	{ width + adjust,	 width,		height,					0xff0000ff & (z ? flag : 0) },
	{ width + adjust,	-width,		height,					0xff0000ff & (z ? flag : 0) },
	// Zの矢印
	{ -top_width + adjust,	-top_width,		height,			0xff0000ff & (z ? flag : 0) },
	{ -top_width + adjust,	 top_width,		height,			0xff0000ff & (z ? flag : 0) },
	{ top_width + adjust,	 top_width,		height,			0xff0000ff & (z ? flag : 0) },
	{ top_width + adjust,	-top_width,		height,			0xff0000ff & (z ? flag : 0) },
	{ vec.x * top * 1.05f,	0.0f,	vec.z * top * 1.05f,	0xff0000ff & (z ? flag : 0) },
	};

	const int AxisNum = 3;
	const int BarVertexNum = 8;
	const int BarTriangleNum = 6 * 2;
	const int ArrowVertexNum = 5;
	const int ArrowTriangleNum = 1 * 2 + 4;
	const int TotalTriangleNum = (BarTriangleNum + ArrowTriangleNum) * AxisNum;
	const int TotalIndexNum = TotalTriangleNum * 3;
	UINT16 indeces[TotalIndexNum]{};
	int vertexOffset = 0;
	int index = 0;
	for (int i = 0; i < AxisNum; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			indeces[index * 3 + 0] = vertexOffset + j * 4 + 0;
			indeces[index * 3 + 1] = vertexOffset + j * 4 + 1;
			indeces[index * 3 + 2] = vertexOffset + j * 4 + 2;
			index++;
			indeces[index * 3 + 0] = vertexOffset + j * 4 + 0;
			indeces[index * 3 + 1] = vertexOffset + j * 4 + 2;
			indeces[index * 3 + 2] = vertexOffset + j * 4 + 3;
			index++;
		}

		for (int j = 0; j < (BarTriangleNum / 2) - 2; j++)
		{
			indeces[index * 3 + 0] = vertexOffset + (j + 0) % 4;
			indeces[index * 3 + 1] = vertexOffset + (j + 1) % 4;
			indeces[index * 3 + 2] = vertexOffset + (j + 0) % 4 + 4;
			index++;
			indeces[index * 3 + 0] = vertexOffset + (j + 1) % 4;
			indeces[index * 3 + 1] = vertexOffset + (j + 0) % 4 + 4;
			indeces[index * 3 + 2] = vertexOffset + (j + 1) % 4 + 4;
			index++;
		}
		vertexOffset += BarVertexNum;

		for (int j = 0; j < ArrowTriangleNum - 2; j++)
		{
			indeces[index * 3 + 0] = vertexOffset + (j + 0) % 4;
			indeces[index * 3 + 1] = vertexOffset + (j + 1) % 4;
			indeces[index * 3 + 2] = vertexOffset + 4;
			index++;
		}
		indeces[index * 3 + 0] = vertexOffset + 0;
		indeces[index * 3 + 1] = vertexOffset + 1;
		indeces[index * 3 + 2] = vertexOffset + 2;
		index++;
		indeces[index * 3 + 0] = vertexOffset + 0;
		indeces[index * 3 + 1] = vertexOffset + 2;
		indeces[index * 3 + 2] = vertexOffset + 3;
		index++;
		vertexOffset += ArrowVertexNum;
	}

	Initialize(1, 1);
	// 頂点バッファの生成
	if (!GetMesh(0)->vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}
	// インデックスバッファの生成
	if (!GetMesh(0)->indexBuffer.Create(sizeof(indeces), indeces))
	{
		return false;
	}

	m_pMesh->fvf = FVF_SIMPLE_3D;
	m_pMesh->primType = D3DPT_TRIANGLELIST;
	m_pMesh->primNum = ARRAYSIZE(indeces) / 3;
	m_pMesh->vertexNum = ARRAYSIZE(vertices);
	m_pMesh->vertexStride = sizeof(SimpleVertex);
	m_pMesh->indexNum = ARRAYSIZE(indeces);
	m_pMesh->materialIndex = 0;

	return true;
}

// モデルの生成
bool Model::CreateShpere(int divideCount, const char* pTexturePath)
{
	const float radius = 1.0f;
	const int DivideMax = 32;
	//	プリミティブの表示数の制限
	divideCount = (divideCount > DivideMax) ? DivideMax : (divideCount < 4) ? 4 : divideCount;

	//	一つのプリミティブ当りの角度
	float angle = D3DXToRadian(360.0f / divideCount);

	float distu = 1.0f / (divideCount);
	float distv = 1.0f / (divideCount / 2);
	float tu = 0;
	float tv = 0;

	const int VertexNumMax = (DivideMax * (DivideMax / 2 - 2) * 2 + DivideMax * 2) * 3;
	//	スフィアの頂点の設定
	MeshVertex vertices[VertexNumMax];

	int index = 0;
	int i, j;
	//	スフィアの上部
	for (i = 0; i < divideCount; i++)
	{
		vertices[index + 0].x = 0;
		vertices[index + 0].y = radius;
		vertices[index + 0].z = 0;
		vertices[index + 0].u = tu;
		vertices[index + 0].v = 0;
		vertices[index + 0].color = 0xffffffff;
		vertices[index + 0].nx = vertices[index + 0].x;
		vertices[index + 0].ny = vertices[index + 0].y;
		vertices[index + 0].nz = vertices[index + 0].z;

		vertices[index + 1].x = sinf(i*angle) * radius * sinf(angle);
		vertices[index + 1].y = cosf(angle) * radius;
		vertices[index + 1].z = cosf(i*angle) * radius * sinf(angle);
		vertices[index + 1].u = tu;
		vertices[index + 1].v = tv + distv;
		vertices[index + 1].color = 0xffffffff;
		vertices[index + 1].nx = vertices[index + 1].x;
		vertices[index + 1].ny = vertices[index + 1].y;
		vertices[index + 1].nz = vertices[index + 1].z;

		vertices[index + 2].x = sinf((i + 1)*angle) * radius * sinf(angle);
		vertices[index + 2].y = cosf(angle) * radius;
		vertices[index + 2].z = cosf((i + 1)*angle) * radius * sinf(angle);
		vertices[index + 2].u = tu - distu;
		vertices[index + 2].v = tv + distv;
		vertices[index + 2].color = 0xffffffff;
		vertices[index + 2].nx = vertices[index + 2].x;
		vertices[index + 2].ny = vertices[index + 2].y;
		vertices[index + 2].nz = vertices[index + 2].z;
		tu -= distu;
		index += 3;
	}
	tu = 0;
	tv += distv;

	//	スフィアの中部
	for (i = 1; i < divideCount / 2 - 1; i++)
	{
		for (j = 0; j < divideCount; j++)
		{
			vertices[index + 0].x = sinf(j*angle) * radius * sinf(i*angle);
			vertices[index + 0].y = cosf(i*angle) * radius;
			vertices[index + 0].z = cosf(j*angle) * radius * sinf(i*angle);
			vertices[index + 0].u = tu;
			vertices[index + 0].v = tv;
			vertices[index + 0].color = 0xffffffff;
			vertices[index + 0].nx = vertices[index + 0].x;
			vertices[index + 0].ny = vertices[index + 0].y;
			vertices[index + 0].nz = vertices[index + 0].z;

			vertices[index + 1].x = sinf(j*angle) * radius * sinf((i + 1)*angle);
			vertices[index + 1].y = cosf((i + 1)*angle) * radius;
			vertices[index + 1].z = cosf(j*angle) * radius * sinf((i + 1)*angle);
			vertices[index + 1].u = tu;
			vertices[index + 1].v = tv + distv;
			vertices[index + 1].color = 0xffffffff;
			vertices[index + 1].nx = vertices[index + 1].x;
			vertices[index + 1].ny = vertices[index + 1].y;
			vertices[index + 1].nz = vertices[index + 1].z;

			vertices[index + 2].x = sinf((j + 1)*angle) * radius * sinf(i*angle);
			vertices[index + 2].y = cosf(i*angle) * radius;
			vertices[index + 2].z = cosf((j + 1)*angle) * radius * sinf(i*angle);
			vertices[index + 2].u = tu - distu;
			vertices[index + 2].v = tv;
			vertices[index + 2].color = 0xffffffff;
			vertices[index + 2].nx = vertices[index + 2].x;
			vertices[index + 2].ny = vertices[index + 2].y;
			vertices[index + 2].nz = vertices[index + 2].z;

			index += 3;
			vertices[index + 0].x = sinf((j + 1)*angle) * radius * sinf(i*angle);
			vertices[index + 0].y = cosf(i*angle) * radius;
			vertices[index + 0].z = cosf((j + 1)*angle) * radius * sinf(i*angle);
			vertices[index + 0].u = tu - distu;
			vertices[index + 0].v = tv;
			vertices[index + 0].color = 0xffffffff;
			vertices[index + 0].nx = vertices[index + 0].x;
			vertices[index + 0].ny = vertices[index + 0].y;
			vertices[index + 0].nz = vertices[index + 0].z;

			vertices[index + 1].x = sinf(j*angle) * radius * sinf((i + 1)*angle);
			vertices[index + 1].y = cosf((i + 1)*angle) * radius;
			vertices[index + 1].z = cosf(j*angle) * radius * sinf((i + 1)*angle);
			vertices[index + 1].u = tu;
			vertices[index + 1].v = tv + distv;
			vertices[index + 1].color = 0xffffffff;
			vertices[index + 1].nx = vertices[index + 1].x;
			vertices[index + 1].ny = vertices[index + 1].y;
			vertices[index + 1].nz = vertices[index + 1].z;

			vertices[index + 2].x = sinf((j + 1)*angle) * radius * sinf((i + 1)*angle);
			vertices[index + 2].y = cosf((i + 1)*angle) * radius;
			vertices[index + 2].z = cosf((j + 1)*angle) * radius * sinf((i + 1)*angle);
			vertices[index + 2].u = tu - distu;
			vertices[index + 2].v = tv + distv;
			vertices[index + 2].color = 0xffffffff;
			vertices[index + 2].nx = vertices[index + 2].x;
			vertices[index + 2].ny = vertices[index + 2].y;
			vertices[index + 2].nz = vertices[index + 2].z;

			tu -= distu;
			index += 3;
		}
		tu = 0;
		tv += distv;
	}

	//	スフィアの下部
	for (i = 0; i < divideCount; i++) {
		vertices[index + 0].x = sinf(i*angle) * radius * sinf((divideCount / 2 - 1)*angle);
		vertices[index + 0].y = cosf((divideCount / 2 - 1)*angle) * radius;
		vertices[index + 0].z = cosf(i*angle) * radius * sinf((divideCount / 2 - 1)*angle);
		vertices[index + 0].u = tu;
		vertices[index + 0].v = tv;
		vertices[index + 0].color = 0xffffffff;
		vertices[index + 0].nx = vertices[index + 0].x;
		vertices[index + 0].ny = vertices[index + 0].y;
		vertices[index + 0].nz = vertices[index + 0].z;

		vertices[index + 1].x = 0;
		vertices[index + 1].y = -radius;
		vertices[index + 1].z = 0;
		vertices[index + 1].u = tu;
		vertices[index + 1].v = tv + distv;
		vertices[index + 1].color = 0xffffffff;
		vertices[index + 1].nx = vertices[index + 1].x;
		vertices[index + 1].ny = vertices[index + 1].y;
		vertices[index + 1].nz = vertices[index + 1].z;

		vertices[index + 2].x = sinf((i + 1)*angle) * radius * sinf((divideCount / 2 - 1)*angle);
		vertices[index + 2].y = cosf((divideCount / 2 - 1)*angle) * radius;
		vertices[index + 2].z = cosf((i + 1)*angle) * radius * sinf((divideCount / 2 - 1)*angle);
		vertices[index + 2].u = tu - distu;
		vertices[index + 2].v = tv;
		vertices[index + 2].color = 0xffffffff;
		vertices[index + 2].nx = vertices[index + 2].x;
		vertices[index + 2].ny = vertices[index + 2].y;
		vertices[index + 2].nz = vertices[index + 2].z;

		tu -= distu;
		index += 3;
	}

	Initialize(1, 1);
	// 頂点バッファの生成
	if (!GetMesh(0)->vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}

	int fvf = FVF_MESH_VERTEX;
	if (pTexturePath)
	{
		if (!GetMaterial(0)->texture.Load(pTexturePath))
		{
			return false;
		}
		fvf = FVF_MESH_TEX_VERTEX;
	}

	m_pMesh->fvf = fvf;
	m_pMesh->primType = D3DPT_TRIANGLELIST;
	m_pMesh->primNum = index / 3;
	m_pMesh->vertexNum = index;
	m_pMesh->vertexStride = sizeof(MeshVertex);
	m_pMesh->indexNum = 0;
	m_pMesh->materialIndex = 0;

	return true;
}

// フラスタム領域風のモデルの生成
bool Model::CreateViewFrustum(void)
{
	const float width_front = 1.0f;
	const float width_back = 3.0f;
	const float back = 5.0f;

	// 頂点データ
	const SimpleVertex vertices[] =
	{
		{ -width_front,			-width_front,		0.0f,		0xff000000 },
	{ -width_front,			 width_front,		0.0f,		0xff000000 },
	{ width_front,			 width_front,		0.0f,		0xff000000 },
	{ width_front,			-width_front,		0.0f,		0xff000000 },

	{ -width_back,			-width_back,		back,		0xff000000 },
	{ -width_back,			 width_back,		back,		0xff000000 },
	{ width_back,			 width_back,		back,		0xff000000 },
	{ width_back,			-width_back,		back,		0xff000000 },
	};

	UINT16 indeces[] =
	{
		0, 1, 1, 2, 2, 3, 3, 0,
		4, 5, 5, 6, 6, 7, 7, 4,
		0, 4, 1, 5, 2, 6, 3, 7,
	};

	Initialize(1, 1);
	// 頂点バッファの生成
	if (!GetMesh(0)->vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}
	// インデックスバッファの生成
	if (!GetMesh(0)->indexBuffer.Create(sizeof(indeces), indeces))
	{
		return false;
	}

	m_pMesh->fvf = FVF_SIMPLE_3D;
	m_pMesh->primType = D3DPT_LINELIST;
	m_pMesh->primNum = ARRAYSIZE(indeces) / 2;
	m_pMesh->vertexNum = ARRAYSIZE(vertices);
	m_pMesh->vertexStride = sizeof(SimpleVertex);
	m_pMesh->indexNum = ARRAYSIZE(indeces);
	m_pMesh->materialIndex = 0;

	return true;
}

// カメラ風モデルの生成
bool Model::CreateCamera(void)
{
	const float width = 1.0f;
	const float camera_back_z = 3.0f;
	const float camera_back_w = 0.5f;
	const float camera_front_z = 3.5f;
	const float camera_front_w = 0.75f;

	// 頂点データ
	const SimpleVertex vertices[] =
	{
		{ -width,			-width,				0.0f,			0xff000000 },
	{ -width,			 width,				0.0f,			0xff000000 },
	{ width,			 width,				0.0f,			0xff000000 },
	{ width,			-width,				0.0f,			0xff000000 },

	{ -width,			-width,				camera_back_z,	0xff000000 },
	{ -width,			 width,				camera_back_z,	0xff000000 },
	{ width,			 width,				camera_back_z,	0xff000000 },
	{ width,			-width,				camera_back_z,	0xff000000 },

	{ -camera_back_w,	-camera_back_w,		camera_back_z,	0xff000000 },
	{ -camera_back_w,	 camera_back_w,		camera_back_z,	0xff000000 },
	{ camera_back_w,	 camera_back_w,		camera_back_z,	0xff000000 },
	{ camera_back_w,	-camera_back_w,		camera_back_z,	0xff000000 },

	{ -camera_front_w,	-camera_front_w,	camera_front_z,	0xff000000 },
	{ -camera_front_w,	 camera_front_w,	camera_front_z,	0xff000000 },
	{ camera_front_w,	 camera_front_w,	camera_front_z,	0xff000000 },
	{ camera_front_w,	-camera_front_w,	camera_front_z,	0xff000000 },
	};

	UINT16 indeces[8 * 6 + 8]{};

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int idx1 = j * 2 + i * 8 * 3;
			indeces[idx1 + 0] = (j + 0) % 4 + i * 8;
			indeces[idx1 + 1] = (j + 1) % 4 + i * 8;

			int idx2 = j * 2 + i * 8 * 3 + 8;
			indeces[idx2 + 0] = (j + 0) % 4 + 4 + i * 8;
			indeces[idx2 + 1] = (j + 1) % 4 + 4 + i * 8;

			int idx3 = j * 2 + i * 8 * 3 + 8 * 2;
			indeces[idx3 + 0] = (j + 0) + i * 8;
			indeces[idx3 + 1] = (j + 4) + i * 8;

			int idx4 = j * 2 + 6 * 8;
			indeces[idx4 + 0] = (j + 4);
			indeces[idx4 + 1] = (j + 8);
		}
	}

	Initialize(1, 1);
	// 頂点バッファの生成
	if (!GetMesh(0)->vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}
	// インデックスバッファの生成
	if (!GetMesh(0)->indexBuffer.Create(sizeof(indeces), indeces))
	{
		return false;
	}

	m_pMesh->fvf = FVF_SIMPLE_3D;
	m_pMesh->primType = D3DPT_LINELIST;
	m_pMesh->primNum = ARRAYSIZE(indeces) / 2;
	m_pMesh->vertexNum = ARRAYSIZE(vertices);
	m_pMesh->vertexStride = sizeof(SimpleVertex);
	m_pMesh->indexNum = ARRAYSIZE(indeces);
	m_pMesh->materialIndex = 0;

	return true;
}


// モデル描画
void Model::Render(void)
{
	if (m_materialNum == 0) return;

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	pDevice->SetTransform(D3DTS_WORLD, &m_world);

	for (UINT matIdx = 0; matIdx < m_materialNum; matIdx++)
	{
		MaterialData* pMaterial = GetMaterial(matIdx);
		// テクスチャーの設定
		pDevice->SetTexture(0, pMaterial->texture.GetD3DTexture());

		pDevice->SetMaterial(&pMaterial->material);
		for (UINT meshIdx = 0; meshIdx < m_meshNum; meshIdx++)
		{
			MeshData* pMesh = GetMesh(meshIdx);
			if (matIdx != pMesh->materialIndex)
			{
				continue;
			}

			// 頂点バッファの設定
			pDevice->SetStreamSource(0, pMesh->vertexBuffer.GetBuffer(), 0, pMesh->vertexStride);

			// 頂点フォーマットの指定
			pDevice->SetFVF(pMesh->fvf);

			if (pMesh->indexNum)
			{
				// インデックスバッファの設定
				pDevice->SetIndices(pMesh->indexBuffer.GetBuffer());
				// 描画
				pDevice->DrawIndexedPrimitive(pMesh->primType, 0, 0, pMesh->vertexNum, 0, pMesh->primNum);
			}
			else
			{
				// 描画
				pDevice->DrawPrimitive(pMesh->primType, 0, pMesh->primNum);
			}
		}
	}
}



// モデルと線の当たり判定
int Model::RayPick(const D3DXVECTOR3* pPos, const D3DXVECTOR3* pVec, float* pDist, D3DXVECTOR3* pOut)
{
	if (pDist == NULL) return -1;

	D3DXMATRIX invWorld;
	// モデルの向きに合わせるために逆行列を作成する
	D3DXMatrixInverse(&invWorld, NULL, &m_world);

	D3DXVECTOR3 pos, vec;
	// レイの座標と向きをモデルに合わせる
	D3DXVec3TransformCoord(&pos, pPos, &invWorld);
	D3DXVec3TransformCoord(&vec, pVec, &invWorld);
	D3DXVec3Normalize(&vec, &vec);

	int primNum = 0;
	int ret = -1;
	// 全てのメッシュと当たっているかの判定をしていく
	for (UINT i = 0; i < m_meshNum; i++)
	{
		int retTemp = RayPick(i, &pos, &vec, pOut);
		if (retTemp != -1)
		{
			ret = retTemp + primNum;
		}
		primNum += m_pMesh[i].primNum;
	}
	if (ret != -1)
	{
		// 交点をワールド空間に戻す
		D3DXVec3TransformCoord(pOut, pOut, &m_world);
		// 交点までの距離がレイの長さより遠ければ当たらない
		float hitDist = D3DXVec3Length(&(*pOut - *pPos));
		if (*pDist < hitDist)
		{
			return -1;
		}
		*pDist = hitDist;
	}
	return ret;
}


/*
面と線の当たり判定
今回はよく使われる地面との当たり判定の実装を学びます。

当たり判定で必要な情報は交点(当たる位置)の算出です。
では交点を求める方法を実装していきましょう。

参考ページ
http://gameworkslab.jp/2018/10/20/面と線の当たり判定（概要編）/
*/
bool Model::RayPickTriangle(const D3DXVECTOR3* pTriangle, D3DXVECTOR3 pos, D3DXVECTOR3 vec, D3DXVECTOR3* pOut, float* pDist)
{
	D3DXVECTOR3 p1 = pTriangle[0];
	D3DXVECTOR3 p2 = pTriangle[1];
	D3DXVECTOR3 p3 = pTriangle[2];
	// neartは交差した面の中で最も始点から近い長さ
	float neart = *pDist;

	/*
	1.交点を求める式

	視点(p)から向き(vec)を伸ばした時に面(p1, p2, p3)と交差する点(p')を求める式は下記となります。
	① p' = p + vec * t

	ここで交点(p')を求めるには始点(p)と向き(vec)は分かっていますが長さ(t)が分かっていません。
	なので先ずは長さ(t)を求める必要があります。


	2.交点までの長さを求める方法

	交点までの長さ(t)を求めるには三角関数を使います。
	式：cosθ = c / a

	では始点(p)から面(p1, p2, p3)に垂直な線(n)と長さ(|n|)が分かれば長さ(t)が出せます。
	これを三角関数の式に置き換えます。
	式：cosθ = |n| / t

	これを t を解く式に変換すると
	② t = |n| / cosθ

	この式を解ければ長さ(t)が出るので交点(p')が出せます。
	*/

	/*
	3.面と垂直な線を求める方法

	面の法線を求めるには外積を使います。
	式：aｘb = |a||b|sinθの長さを持った垂直な線

	面の辺1(p2 ? p1)と辺2(p3 ? p1)で外積を行えば垂直な線が出ます。
	③ (p2 ? p1)ｘ(p3 ? p1) = |(p2 ? p1)||(p3 ? p1)|sinθの長さを持った垂直な線

	この式で出たベクトルを正規化すれば長さが1の単位ベクトルになるので、
	垂直な向きの単位ベクトルが出せます。

	*/
	D3DXVECTOR3 normal;
	D3DXVec3Cross(&normal, &(p2 - p1), &(p3 - p1));

	// 法線とレイの向きが向き合っていない場合は当たらない
	if (D3DXVec3Dot(&normal, &vec) > 0.0f) return false;

	/*
	4.面と垂直な線の長さ(|n|)を求める方法

	|n|は三角関数で求めることができます。
	式：cosθ = |n| / |(p1 ? p)|

	この式を|n|を解く式にすると次の式になります。
	④ |n| = |(p1 ? p)|cosθ

	この時のθは法線(n)と点から視点への向き(p1 ? p)の角度が当てはまります。
	なのでcosθを出すには内積を使います。
	式：n・(p1 ? p) = |n||(p1 ? p)|cosθ

	この時に n を正規化しておけば長さが1となるので次の式が出せます。
	式：n・(p1 ? p) = |(p1 ? p)|cosθ

	この右辺の式が④の右辺の式と一致したので次の式で|n|を出せることになります。
	⑤ |n| = n・(p1 ? p)
	*/
	float ndist = D3DXVec3Dot(&(p1 - pos), &normal);

	/*
	5.交点までの長さ(t)を求める方法(完結編)

	上の⑤の式で|n|は出たので最後にcosθを出してtを算出します。
	② t = |n| / cosθ

	この時のθは法線(n)と線の向き(vec)の角度が当てはまります。
	ここもcosθを出すには内積を使います。
	式：n・vec = |n||vec|cosθ

	それぞれ正規化してあれば長さは1になるので
	⑥ n・vec = cosθ
	となります。

	これで長さ(t)を解く式ができます。
	⑦ t = (n・(p1 ? p)) / (vec・n)
	*/
	float costheta = D3DXVec3Dot(&vec, &normal);
	float t = ndist / costheta;

	// 交点が後方、又は他の面よりも遠ければ衝突していない
	if (t < 0.0f || neart < t) return false;

	/*
	6.交点の算出(実計算)

	ここまでに求めた線の長さ(t)から①の式を使って交点を求めます
	① p' = p + vec * t
	*/
	D3DXVECTOR3 p = pos + vec * t;

	/*
	7.衝突する点(p')が面の中にあるかの判定

	面(p1, p2, p3)の3点の内側に交点(p')が入っているかをチェックします。

	手順としては下記の2つです。
	・それぞれを繋ぐ辺と交点の外積をとって垂直な線を出す。
	・法線と上で計算した垂直な線で内積して0以下の値になっていれば内側にない
	*/
	D3DXVECTOR3 vec1, vec2, vec3;
	D3DXVec3Cross(&vec1, &(p1 - p), &(p2 - p1));
	D3DXVec3Cross(&vec2, &(p2 - p), &(p3 - p2));
	D3DXVec3Cross(&vec3, &(p3 - p), &(p1 - p3));

	if (D3DXVec3Dot(&vec1, &normal) < 0.0f) return false;
	if (D3DXVec3Dot(&vec2, &normal) < 0.0f) return false;
	if (D3DXVec3Dot(&vec3, &normal) < 0.0f) return false;

	/*
	8.本当に衝突した面か？

	衝突しているので衝突状況を保存していきます。
	今回は下記を保存しています。

	・当たった交点
	・交点までの距離
	*/

	*pOut = p;
	*pDist = t;

	return true;
}

// モデルと線の当たり判定
int Model::RayPick(UINT i, const D3DXVECTOR3* pPos, const D3DXVECTOR3* pVec, D3DXVECTOR3* pOut)
{
	MeshData* pMesh = GetMesh(i);
	if (pMesh->vertexBuffer.GetBuffer() == NULL) return -1;

	IDirect3DVertexBuffer9* pVertexBuffer = pMesh->vertexBuffer.GetBuffer();
	IDirect3DIndexBuffer9* pIndexBuffer = pMesh->indexNum ? pMesh->indexBuffer.GetBuffer() : NULL;

	switch (pMesh->primType)
	{
	case D3DPT_TRIANGLESTRIP:
	case D3DPT_TRIANGLELIST:
		break;
	default:
		// TRAIANGLESTRIPとTRIANGLELIST以外は未対応
		return -1;
	}

	// 当たりをとる始点と向き
	D3DXVECTOR3 pos(*pPos), vec(*pVec);

	UINT16* pIndexData = NULL;
	BYTE* pVertexData;
	pVertexBuffer->Lock(0, pMesh->vertexStride * pMesh->vertexNum, (void**)&pVertexData, D3DLOCK_READONLY);
	if (pIndexBuffer) pIndexBuffer->Lock(0, sizeof(UINT16) * pMesh->indexNum, (void**)&pIndexData, D3DLOCK_READONLY);

	int	ret = -1;

	float neart = 10000.0f;
	int index1, index2, index3;
	// 面の数だけ当たり判定を行う
	for (UINT primIdx = 0; primIdx < pMesh->primNum; primIdx++)
	{
		// 面を構成するインデックスの取得
		switch (pMesh->primType)
		{
		case D3DPT_TRIANGLESTRIP:
			index1 = primIdx + 0;
			index2 = primIdx + 1;
			index3 = primIdx + 2;
			break;
		case D3DPT_TRIANGLELIST:
			index1 = primIdx * 3 + 0;
			index2 = primIdx * 3 + 1;
			index3 = primIdx * 3 + 2;
			break;
		}
		// インデックスバッファがある場合はそちらを使用する
		if (pIndexData)
		{
			index1 = pIndexData[index1];
			index2 = pIndexData[index2];
			index3 = pIndexData[index3];
		}

		// 頂点の座標部分を取り出す
		D3DXVECTOR3 Triangle[3] =
		{
			*(D3DXVECTOR3*)(pVertexData + pMesh->vertexStride * index1),
			*(D3DXVECTOR3*)(pVertexData + pMesh->vertexStride * index2),
			*(D3DXVECTOR3*)(pVertexData + pMesh->vertexStride * index3)
		};
		if (RayPickTriangle(Triangle, pos, vec, pOut, &neart))
		{
			ret = (int)primIdx;
		}
	}

	if (pIndexBuffer) pIndexBuffer->Unlock();
	pVertexBuffer->Unlock();

	return ret;
}