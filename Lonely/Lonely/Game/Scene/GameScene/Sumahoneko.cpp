/**
* @file Sumahoneko.cpp
* @brief Sumahoneko�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "Sumahoneko.h"
#include "../../../GameLib/GameLib.h"

Sumahoneko::Sumahoneko()
{
	Initialize();
}

Sumahoneko::~Sumahoneko()
{
	Finalize();
}

//����������
bool Sumahoneko::Initialize()
{
	m_fbxStage.Load("../Graphics/stage2_1.fbx");
	m_fbxModel.Load("../Graphics/sumahoneko.fbx");
	m_shpere.CreateShpere(32);

	m_playerRadius = 0.1f;
	m_playerSpeed = 0.1f;
	return true;
}

//�������
void Sumahoneko::Finalize()
{
	m_fbxModel.Finalize();
	m_fbxStage.Finalize();
	m_shpere.Finalize();
}

//�X�V����
void Sumahoneko::Update()
{

}

//�`�悷��
void Sumahoneko::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// �ʏ폑�����݃��[�h�ɐݒ�
	pDirectX->SetRenderMode(DirectX::Normal, false);

	// Z�e�X�g�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// ���f���̕`��
	m_fbxModel.Render();
	m_fbxStage.Render();
}
