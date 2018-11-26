/**
* @file TitleBackGround.cpp
* @brief TitleBackGround�N���X�̃\�[�X�t�@�C��
* @author ����@�k��
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

//����������
bool TitleBackGround::Initialize()
{
	// assets�t�H���_����bridge.png���e�N�X�`���[�Ƃ��ēǂݍ���
	if (!m_texture.Load("../Grafics/Title_BG"))
	{
		return false;
	}
	// �摜�T�C�Y���畝�ƍ�����ݒ�
	float rect[] =
	{
		10.0f, 10.0f,
		10.0f + (float)m_texture.GetSrcWidth(), 10.0f + (float)m_texture.GetSrcHeight(),
	};
	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	float u = (float)m_texture.GetSrcWidth() / (float)m_texture.GetWidth();
	float v = (float)m_texture.GetSrcHeight() / (float)m_texture.GetHeight();
	// �摜�T�C�Y�ɍ��킹��UV���ǉ��������_�f�[�^
	const Simple2DVertex vertices[4] =
	{
		// 1�ڂ̋�`
		{ rect[0], rect[1], 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
	{ rect[2], rect[1], 0.0f, 1.0f, 0xffffffff,    u, 0.0f },
	{ rect[0], rect[3], 0.0f, 1.0f, 0xffffffff, 0.0f,    v },
	{ rect[2], rect[3], 0.0f, 1.0f, 0xffffffff,    u,    v },
	};
	// ���_�o�b�t�@�̐���
	if (!m_vertexBuffer.Create(sizeof(vertices), vertices))
	{
		return false;
	}
	return true;
}

//�������
void TitleBackGround::Finalize()
{
	m_texture.Finalize();
	m_vertexBuffer.Finalize();
}

void TitleBackGround::Update()
{
	////���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
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

	//�ʏ폑�����݃��[�h
	pDirectX->SetRenderMode(DirectX::Normal, false);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//���_�o�b�t�@�̐ݒ�
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, m_vertexBuffer.GetBuffer(), 0, sizeof(Simple2DVertex));

	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//// �����_�����O	 
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