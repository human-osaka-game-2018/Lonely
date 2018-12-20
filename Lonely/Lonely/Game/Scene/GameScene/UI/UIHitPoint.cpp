/**
* @file UIHitPoint.cpp
* @brief UIHitPoint�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "UIHitPoint.h"
#include "../../../../GameLib/GameLib.h"

UIHitPoint::UIHitPoint()
{
	Initialize();
}

UIHitPoint::~UIHitPoint()
{
	Finalize();
}

//����������
bool UIHitPoint::Initialize()
{
	// assets�t�H���_����bridge.png���e�N�X�`���[�Ƃ��ēǂݍ���
	if (!m_texture.Load("../Graphics/UIHitPoint.png"))
	{
		return false;
	}

	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	// �e�N�X�`����2�̗ݏ�łȂ��Ƃ��Ɍ��ʂ𔭊�����
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 600.f, WINDOW_HEIGHT-100.f, 300.f, 50.f, 347.f/2048.f, 137.f/512.f, 0.f ,0.f);

	return true;
}

//�������
void UIHitPoint::Finalize()
{
	m_texture.Finalize();
}

void UIHitPoint::Update()
{
}

void UIHitPoint::Render()
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
