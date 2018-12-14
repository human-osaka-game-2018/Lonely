/**
* @file 3DHelper.cpp
* @brief 3DHelper�N���X�̃\�[�X�t�@�C��
* @author ���� �k��
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

// ���f���̉��
void Model::Finalize(void)
{
	SAFE_DELETE_ARRAY(m_pMesh);
	SAFE_DELETE_ARRAY(m_pMaterial);
}

// �}�e���A�����̏�����
void Model::InitMaterial(void)
{
	D3DMATERIAL9 material;
	//	�ގ��ݒ�
	//	�A���r�G���g(��)�J���[
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	//	�f�B�t���[�Y(�f�ނ�)�J���[
	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 1.0f;
	material.Diffuse.b = 1.0f;
	material.Diffuse.a = 1.0f;
	//	�X�y�L�����[�i�e�J��j�J���[
	material.Specular.r = 1.0f;
	material.Specular.g = 1.0f;
	material.Specular.b = 1.0f;
	material.Specular.a = 1.0f;
	material.Power = 15.0f;
	//	�G�~�b�V�u�i�����j
	material.Emissive.r = 0.0f;
	material.Emissive.g = 0.0f;
	material.Emissive.b = 0.0f;
	material.Emissive.a = 0.0f;

	for (UINT i = 0; i < m_materialNum; i++)
	{
		GetMaterial(i)->material = material;
	}
}

// ���f���̐���
bool Model::CreateTriangle(void)
{
	float width = 1.0f;
	float height = sqrtf(3.0f) * width;
	// �摜�T�C�Y�ɍ��킹��UV���ǉ��������_�f�[�^
	const SimpleVertex vertices[] =
	{
		{ -width,	0.0f,	0.0f,		0xffafafff },
	{ 0.0f,		0.0f,	height,		0xffafafff },
	{ width,	0.0f,	0.0f,		0xffafafff },
	};

	Initialize(1, 1);
	// ���_�o�b�t�@�̐���
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

// ���f���̐���
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
	// ���_�f�[�^
	const SimpleVertex vertices[] =
	{
		// X�̎�
		{ 0.0f,				-width,			-width,		0xffff0000 & (x ? flag : 0) },
	{ 0.0f,				-width,			 width,		0xffff0000 & (x ? flag : 0) },
	{ 0.0f,				 width,			 width,		0xffff0000 & (x ? flag : 0) },
	{ 0.0f,				 width,			-width,		0xffff0000 & (x ? flag : 0) },
	{ height,			-width,			-width,		0xffff0000 & (x ? flag : 0) },
	{ height,			-width,			 width,		0xffff0000 & (x ? flag : 0) },
	{ height,			 width,			 width,		0xffff0000 & (x ? flag : 0) },
	{ height,			 width,			-width,		0xffff0000 & (x ? flag : 0) },
	// X�̖��
	{ height,			-top_width,	-top_width,		0xffff0000 & (x ? flag : 0) },
	{ height,			-top_width,	 top_width,		0xffff0000 & (x ? flag : 0) },
	{ height,			 top_width,	 top_width,		0xffff0000 & (x ? flag : 0) },
	{ height,			 top_width,	-top_width,		0xffff0000 & (x ? flag : 0) },
	{ top,					  0.0f,		  0.0f,		0xffff0000 & (x ? flag : 0) },

	// Y�̎�
	{ -width,			0.0f,			-width,		0xff00ff00 & (y ? flag : 0) },
	{ -width,			0.0f,			 width,		0xff00ff00 & (y ? flag : 0) },
	{ width,			0.0f,			 width,		0xff00ff00 & (y ? flag : 0) },
	{ width,			0.0f,			-width,		0xff00ff00 & (y ? flag : 0) },
	{ -width,			height,			-width,		0xff00ff00 & (y ? flag : 0) },
	{ -width,			height,			 width,		0xff00ff00 & (y ? flag : 0) },
	{ width,			height,			 width,		0xff00ff00 & (y ? flag : 0) },
	{ width,			height,			-width,		0xff00ff00 & (y ? flag : 0) },
	// Y�̖��
	{ -top_width,		height,		-top_width,		0xff00ff00 & (y ? flag : 0) },
	{ -top_width,		height,		 top_width,		0xff00ff00 & (y ? flag : 0) },
	{ top_width,		height,		 top_width,		0xff00ff00 & (y ? flag : 0) },
	{ top_width,		height,		-top_width,		0xff00ff00 & (y ? flag : 0) },
	{ 0.0f,			top,			  0.0f,		0xff00ff00 & (y ? flag : 0) },

	// Z�̎�
	{ -width,			-width,		0.0f,					0xff0000ff & (z ? flag : 0) },
	{ -width,			 width,		0.0f,					0xff0000ff & (z ? flag : 0) },
	{ width,			 width,		0.0f,					0xff0000ff & (z ? flag : 0) },
	{ width,			-width,		0.0f,					0xff0000ff & (z ? flag : 0) },
	{ -width + adjust,	-width,		height,					0xff0000ff & (z ? flag : 0) },
	{ -width + adjust,	 width,		height,					0xff0000ff & (z ? flag : 0) },
	{ width + adjust,	 width,		height,					0xff0000ff & (z ? flag : 0) },
	{ width + adjust,	-width,		height,					0xff0000ff & (z ? flag : 0) },
	// Z�̖��
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
	// ���_�o�b�t�@�̐���
	if (!GetMesh(0)->vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}
	// �C���f�b�N�X�o�b�t�@�̐���
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

// ���f���̐���
bool Model::CreateShpere(int divideCount, const char* pTexturePath)
{
	const float radius = 1.0f;
	const int DivideMax = 32;
	//	�v���~�e�B�u�̕\�����̐���
	divideCount = (divideCount > DivideMax) ? DivideMax : (divideCount < 4) ? 4 : divideCount;

	//	��̃v���~�e�B�u����̊p�x
	float angle = D3DXToRadian(360.0f / divideCount);

	float distu = 1.0f / (divideCount);
	float distv = 1.0f / (divideCount / 2);
	float tu = 0;
	float tv = 0;

	const int VertexNumMax = (DivideMax * (DivideMax / 2 - 2) * 2 + DivideMax * 2) * 3;
	//	�X�t�B�A�̒��_�̐ݒ�
	MeshVertex vertices[VertexNumMax];

	int index = 0;
	int i, j;
	//	�X�t�B�A�̏㕔
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

	//	�X�t�B�A�̒���
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

	//	�X�t�B�A�̉���
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
	// ���_�o�b�t�@�̐���
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

// �t���X�^���̈敗�̃��f���̐���
bool Model::CreateViewFrustum(void)
{
	const float width_front = 1.0f;
	const float width_back = 3.0f;
	const float back = 5.0f;

	// ���_�f�[�^
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
	// ���_�o�b�t�@�̐���
	if (!GetMesh(0)->vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}
	// �C���f�b�N�X�o�b�t�@�̐���
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

// �J���������f���̐���
bool Model::CreateCamera(void)
{
	const float width = 1.0f;
	const float camera_back_z = 3.0f;
	const float camera_back_w = 0.5f;
	const float camera_front_z = 3.5f;
	const float camera_front_w = 0.75f;

	// ���_�f�[�^
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
	// ���_�o�b�t�@�̐���
	if (!GetMesh(0)->vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}
	// �C���f�b�N�X�o�b�t�@�̐���
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


// ���f���`��
void Model::Render(void)
{
	if (m_materialNum == 0) return;

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	pDevice->SetTransform(D3DTS_WORLD, &m_world);

	for (UINT matIdx = 0; matIdx < m_materialNum; matIdx++)
	{
		MaterialData* pMaterial = GetMaterial(matIdx);
		// �e�N�X�`���[�̐ݒ�
		pDevice->SetTexture(0, pMaterial->texture.GetD3DTexture());

		pDevice->SetMaterial(&pMaterial->material);
		for (UINT meshIdx = 0; meshIdx < m_meshNum; meshIdx++)
		{
			MeshData* pMesh = GetMesh(meshIdx);
			if (matIdx != pMesh->materialIndex)
			{
				continue;
			}

			// ���_�o�b�t�@�̐ݒ�
			pDevice->SetStreamSource(0, pMesh->vertexBuffer.GetBuffer(), 0, pMesh->vertexStride);

			// ���_�t�H�[�}�b�g�̎w��
			pDevice->SetFVF(pMesh->fvf);

			if (pMesh->indexNum)
			{
				// �C���f�b�N�X�o�b�t�@�̐ݒ�
				pDevice->SetIndices(pMesh->indexBuffer.GetBuffer());
				// �`��
				pDevice->DrawIndexedPrimitive(pMesh->primType, 0, 0, pMesh->vertexNum, 0, pMesh->primNum);
			}
			else
			{
				// �`��
				pDevice->DrawPrimitive(pMesh->primType, 0, pMesh->primNum);
			}
		}
	}
}



// ���f���Ɛ��̓����蔻��
int Model::RayPick(const D3DXVECTOR3* pPos, const D3DXVECTOR3* pVec, float* pDist, D3DXVECTOR3* pOut)
{
	if (pDist == NULL) return -1;

	D3DXMATRIX invWorld;
	// ���f���̌����ɍ��킹�邽�߂ɋt�s����쐬����
	D3DXMatrixInverse(&invWorld, NULL, &m_world);

	D3DXVECTOR3 pos, vec;
	// ���C�̍��W�ƌ��������f���ɍ��킹��
	D3DXVec3TransformCoord(&pos, pPos, &invWorld);
	D3DXVec3TransformCoord(&vec, pVec, &invWorld);
	D3DXVec3Normalize(&vec, &vec);

	int primNum = 0;
	int ret = -1;
	// �S�Ẵ��b�V���Ɠ������Ă��邩�̔�������Ă���
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
		// ��_�����[���h��Ԃɖ߂�
		D3DXVec3TransformCoord(pOut, pOut, &m_world);
		// ��_�܂ł̋��������C�̒�����艓����Γ�����Ȃ�
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
�ʂƐ��̓����蔻��
����͂悭�g����n�ʂƂ̓����蔻��̎������w�т܂��B

�����蔻��ŕK�v�ȏ��͌�_(������ʒu)�̎Z�o�ł��B
�ł͌�_�����߂���@���������Ă����܂��傤�B

�Q�l�y�[�W
http://gameworkslab.jp/2018/10/20/�ʂƐ��̓����蔻��i�T�v�ҁj/
*/
bool Model::RayPickTriangle(const D3DXVECTOR3* pTriangle, D3DXVECTOR3 pos, D3DXVECTOR3 vec, D3DXVECTOR3* pOut, float* pDist)
{
	D3DXVECTOR3 p1 = pTriangle[0];
	D3DXVECTOR3 p2 = pTriangle[1];
	D3DXVECTOR3 p3 = pTriangle[2];
	// neart�͌��������ʂ̒��ōł��n�_����߂�����
	float neart = *pDist;

	/*
	1.��_�����߂鎮

	���_(p)�������(vec)��L�΂������ɖ�(p1, p2, p3)�ƌ�������_(p')�����߂鎮�͉��L�ƂȂ�܂��B
	�@ p' = p + vec * t

	�����Ō�_(p')�����߂�ɂ͎n�_(p)�ƌ���(vec)�͕������Ă��܂�������(t)���������Ă��܂���B
	�Ȃ̂Ő悸�͒���(t)�����߂�K�v������܂��B


	2.��_�܂ł̒��������߂���@

	��_�܂ł̒���(t)�����߂�ɂ͎O�p�֐����g���܂��B
	���Fcos�� = c / a

	�ł͎n�_(p)�����(p1, p2, p3)�ɐ����Ȑ�(n)�ƒ���(|n|)��������Β���(t)���o���܂��B
	������O�p�֐��̎��ɒu�������܂��B
	���Fcos�� = |n| / t

	����� t ���������ɕϊ������
	�A t = |n| / cos��

	���̎���������Β���(t)���o��̂Ō�_(p')���o���܂��B
	*/

	/*
	3.�ʂƐ����Ȑ������߂���@

	�ʂ̖@�������߂�ɂ͊O�ς��g���܂��B
	���Fa��b = |a||b|sin�Ƃ̒����������������Ȑ�

	�ʂ̕�1(p2 ? p1)�ƕ�2(p3 ? p1)�ŊO�ς��s���ΐ����Ȑ����o�܂��B
	�B (p2 ? p1)��(p3 ? p1) = |(p2 ? p1)||(p3 ? p1)|sin�Ƃ̒����������������Ȑ�

	���̎��ŏo���x�N�g���𐳋K������Β�����1�̒P�ʃx�N�g���ɂȂ�̂ŁA
	�����Ȍ����̒P�ʃx�N�g�����o���܂��B

	*/
	D3DXVECTOR3 normal;
	D3DXVec3Cross(&normal, &(p2 - p1), &(p3 - p1));

	// �@���ƃ��C�̌��������������Ă��Ȃ��ꍇ�͓�����Ȃ�
	if (D3DXVec3Dot(&normal, &vec) > 0.0f) return false;

	/*
	4.�ʂƐ����Ȑ��̒���(|n|)�����߂���@

	|n|�͎O�p�֐��ŋ��߂邱�Ƃ��ł��܂��B
	���Fcos�� = |n| / |(p1 ? p)|

	���̎���|n|���������ɂ���Ǝ��̎��ɂȂ�܂��B
	�C |n| = |(p1 ? p)|cos��

	���̎��̃Ƃ͖@��(n)�Ɠ_���王�_�ւ̌���(p1 ? p)�̊p�x�����Ă͂܂�܂��B
	�Ȃ̂�cos�Ƃ��o���ɂ͓��ς��g���܂��B
	���Fn�E(p1 ? p) = |n||(p1 ? p)|cos��

	���̎��� n �𐳋K�����Ă����Β�����1�ƂȂ�̂Ŏ��̎����o���܂��B
	���Fn�E(p1 ? p) = |(p1 ? p)|cos��

	���̉E�ӂ̎����C�̉E�ӂ̎��ƈ�v�����̂Ŏ��̎���|n|���o���邱�ƂɂȂ�܂��B
	�D |n| = n�E(p1 ? p)
	*/
	float ndist = D3DXVec3Dot(&(p1 - pos), &normal);

	/*
	5.��_�܂ł̒���(t)�����߂���@(������)

	��̇D�̎���|n|�͏o���̂ōŌ��cos�Ƃ��o����t���Z�o���܂��B
	�A t = |n| / cos��

	���̎��̃Ƃ͖@��(n)�Ɛ��̌���(vec)�̊p�x�����Ă͂܂�܂��B
	������cos�Ƃ��o���ɂ͓��ς��g���܂��B
	���Fn�Evec = |n||vec|cos��

	���ꂼ�ꐳ�K�����Ă���Β�����1�ɂȂ�̂�
	�E n�Evec = cos��
	�ƂȂ�܂��B

	����Œ���(t)�����������ł��܂��B
	�F t = (n�E(p1 ? p)) / (vec�En)
	*/
	float costheta = D3DXVec3Dot(&vec, &normal);
	float t = ndist / costheta;

	// ��_������A���͑��̖ʂ���������ΏՓ˂��Ă��Ȃ�
	if (t < 0.0f || neart < t) return false;

	/*
	6.��_�̎Z�o(���v�Z)

	�����܂łɋ��߂����̒���(t)����@�̎����g���Č�_�����߂܂�
	�@ p' = p + vec * t
	*/
	D3DXVECTOR3 p = pos + vec * t;

	/*
	7.�Փ˂���_(p')���ʂ̒��ɂ��邩�̔���

	��(p1, p2, p3)��3�_�̓����Ɍ�_(p')�������Ă��邩���`�F�b�N���܂��B

	�菇�Ƃ��Ă͉��L��2�ł��B
	�E���ꂼ����q���ӂƌ�_�̊O�ς��Ƃ��Đ����Ȑ����o���B
	�E�@���Ə�Ōv�Z���������Ȑ��œ��ς���0�ȉ��̒l�ɂȂ��Ă���Γ����ɂȂ�
	*/
	D3DXVECTOR3 vec1, vec2, vec3;
	D3DXVec3Cross(&vec1, &(p1 - p), &(p2 - p1));
	D3DXVec3Cross(&vec2, &(p2 - p), &(p3 - p2));
	D3DXVec3Cross(&vec3, &(p3 - p), &(p1 - p3));

	if (D3DXVec3Dot(&vec1, &normal) < 0.0f) return false;
	if (D3DXVec3Dot(&vec2, &normal) < 0.0f) return false;
	if (D3DXVec3Dot(&vec3, &normal) < 0.0f) return false;

	/*
	8.�{���ɏՓ˂����ʂ��H

	�Փ˂��Ă���̂ŏՓˏ󋵂�ۑ����Ă����܂��B
	����͉��L��ۑ����Ă��܂��B

	�E����������_
	�E��_�܂ł̋���
	*/

	*pOut = p;
	*pDist = t;

	return true;
}

// ���f���Ɛ��̓����蔻��
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
		// TRAIANGLESTRIP��TRIANGLELIST�ȊO�͖��Ή�
		return -1;
	}

	// ��������Ƃ�n�_�ƌ���
	D3DXVECTOR3 pos(*pPos), vec(*pVec);

	UINT16* pIndexData = NULL;
	BYTE* pVertexData;
	pVertexBuffer->Lock(0, pMesh->vertexStride * pMesh->vertexNum, (void**)&pVertexData, D3DLOCK_READONLY);
	if (pIndexBuffer) pIndexBuffer->Lock(0, sizeof(UINT16) * pMesh->indexNum, (void**)&pIndexData, D3DLOCK_READONLY);

	int	ret = -1;

	float neart = 10000.0f;
	int index1, index2, index3;
	// �ʂ̐����������蔻����s��
	for (UINT primIdx = 0; primIdx < pMesh->primNum; primIdx++)
	{
		// �ʂ��\������C���f�b�N�X�̎擾
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
		// �C���f�b�N�X�o�b�t�@������ꍇ�͂�������g�p����
		if (pIndexData)
		{
			index1 = pIndexData[index1];
			index2 = pIndexData[index2];
			index3 = pIndexData[index3];
		}

		// ���_�̍��W���������o��
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