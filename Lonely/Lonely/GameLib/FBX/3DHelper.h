/**
* @file 3DHelper.h
* @brief 3DHelper�N���X�̃w�b�_�t�@�C��
* @author ���� �k��
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
* @brief �V���v���Ȓ��_���
*/
struct SimpleVertex
{
	float x, y, z;
	DWORD color;
};

/** 
* @brief �V���v���ȃe�N�X�`���\�t�����_���
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

	// �X�L�����b�V���p
	BYTE index[4];
	float weight[4];
};

struct MaterialData
{
	Texture			texture;	        // �e�N�X�`���\
	D3DMATERIAL9	material;		    // �}�e���A��
};


/** 
* @brief ���f�����
*/
struct MeshData
{
	UINT				fvf;			// �t�H�[�}�b�g
	D3DPRIMITIVETYPE	primType;		// �v���~�e�B�u�̕`����@
	UINT				primNum;		// �v���~�e�B�u��
	UINT				vertexNum;		// ���_��
	UINT				vertexStride;	// 1���_�ӂ�̃T�C�Y
	UINT				indexNum;		// �C���f�b�N�X��
	UINT				materialIndex;	// �}�e���A���ԍ�

	VertexBuffer		vertexBuffer;	// �v�_�o�b�t�@
	IndexBuffer			indexBuffer;	// �C���f�b�N�X�o�b�t�@
};


/** 
* @brief ���f���N���X
*/
class Model
{
public:

	Model();
	~Model();


	// ������
	bool Initialize(UINT meshNum, UINT materialNum);
	// ���
	virtual void Finalize();

	// �`��
	virtual void Render();

	// ���b�V�����̎擾
	UINT GetMeshNum() const { return m_meshNum; }
	// �}�e���A�����̎擾
	UINT GetMaterialNum() const { return m_materialNum; }
	// ���[���h�s��̎擾
	MeshData* GetMesh(UINT i) { return &m_pMesh[i]; }
	// ���[���h�s��̎擾
	MaterialData* GetMaterial(UINT i) { return &m_pMaterial[i]; }

	// ���[���h�s��̎擾
	D3DXMATRIX* GetWorld() { return &m_world; }

public:
	// ���f���̐���
	bool CreateTriangle();
	// ���f���̐���
	bool Create3DAxis(bool x = true, bool y = true, bool z = true);
	// ���f���̐���
	bool CreateShpere(int divideCount = 24, const char* pTexturePath = NULL);

	// �t���X�^���̈敗���f��(���C���[�t���[��)�̐���
	bool CreateViewFrustum();
	// �J���������f��(���C���[�t���[��)�̐���
	bool CreateCamera();


	// ���̓����蔻��
	int RayPick(const D3DXVECTOR3* pPos, const D3DXVECTOR3* pVec, float* pDist, D3DXVECTOR3* pOut);

private:
	// ���̓����蔻��
	int RayPick(UINT i, const D3DXVECTOR3* pPos, const D3DXVECTOR3* pVec, D3DXVECTOR3* pOut);
	// ���̓����蔻��
	bool RayPickTriangle(const D3DXVECTOR3* pTriangle, D3DXVECTOR3 pos, D3DXVECTOR3 vec, D3DXVECTOR3* pOut, float* pDist);

	// �}�e���A���̏�����
	virtual void InitMaterial();

protected:

	UINT			m_meshNum;		// ���b�V����
	UINT			m_materialNum;	// �}�e���A����

	MeshData*		m_pMesh;		// ���b�V�����
	MaterialData*	m_pMaterial;	// �}�e���A�����
	D3DXMATRIX		m_world;		// ���[���h�}�g���b�N�X
};
