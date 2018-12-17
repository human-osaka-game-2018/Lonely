/**
* @file UIFootsteps.cpp
* @brief UIFootsteps�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "UIFootsteps.h"
#include "../../../../GameLib/GameLib.h"

UIFootsteps::UIFootsteps()
{
	Initialize();
}

UIFootsteps::~UIFootsteps()
{
	Finalize();
}

//����������
bool UIFootsteps::Initialize()
{
	// assets�t�H���_����bridge.png���e�N�X�`���[�Ƃ��ēǂݍ���
	if (!m_texture.Load("../Graphics/UIFootsteps.png"))
	{
		return false;
	}

	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	// �e�N�X�`����2�̗ݏ�łȂ��Ƃ��Ɍ��ʂ𔭊�����
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 1000.f, WINDOW_HEIGHT-100.f, 100.f, 50.f, 203.f/1024.f, 120.f/256.f, 0.f, 0.f);

	return true;
}

//�������
void UIFootsteps::Finalize()
{
	m_texture.Finalize();
}

void UIFootsteps::Update()
{
}

void UIFootsteps::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//���_�ɓ����f�[�^��ݒ�
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//�`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
}
