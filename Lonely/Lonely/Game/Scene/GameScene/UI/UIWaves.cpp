/**
* @file UIWaves.cpp
* @brief UIWaves�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "UIWaves.h"
#include "../../../../GameLib/GameLib.h"

UIWaves::UIWaves()
{
	Initialize();
}

UIWaves::~UIWaves()
{
	Finalize();
}

//����������
bool UIWaves::Initialize()
{
	// assets�t�H���_����bridge.png���e�N�X�`���[�Ƃ��ēǂݍ���
	if (!m_texture.Load("../Graphics/UIWaves.png"))
	{
		return false;
	}

	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	// �e�N�X�`����2�̗ݏ�łȂ��Ƃ��Ɍ��ʂ𔭊�����
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 1150.f, WINDOW_HEIGHT-100.f, 100.f, 50.f,186.f/1024.f, 120.f/256.f, 0.f, 0.f);

	return true;
}

//�������
void UIWaves::Finalize()
{
	m_texture.Finalize();
}

void UIWaves::Update()
{
}

void UIWaves::Render()
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
