/**
* @file UI.cpp
* @brief UI�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "UI.h"
#include "../../../../GameLib/GameLib.h"

UI::UI()
{
	Initialize();
}

UI::~UI()
{
	Finalize();
}

//����������
bool UI::Initialize()
{
	// assets�t�H���_����bridge.png���e�N�X�`���[�Ƃ��ēǂݍ���
	if (!m_texture.Load("../Graphics/smart phone.png"))
	{
		return false;
	}

	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	//���_�̍��W���Z�b�g
	HELPER_2D->SetVerticesFromLeftTopType(m_vertices
		, 20
		, 100
		, logoWidth, logoHeight);

	return true;
}

//�������
void UI::Finalize()
{
	m_texture.Finalize();
}

//�X�V����
void UI::Update()
{
}

//�`�悷��
void UI::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// ���_�ɓ����f�[�^��ݒ�
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	//�`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

}
