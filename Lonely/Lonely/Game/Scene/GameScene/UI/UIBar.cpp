/**
* @file UIBar.cpp
* @brief UIBar�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "UIBar.h"
#include "../../../../GameLib/GameLib.h"

UIBar::UIBar()
{
	Initialize();
}

UIBar::~UIBar()
{
	Finalize();
}

//����������
bool UIBar::Initialize()
{

	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	// �e�N�X�`����2�̗ݏ�łȂ��Ƃ��Ɍ��ʂ𔭊�����
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 0.f, WINDOW_HEIGHT-100.f, WINDOW_WIDTH, 100, u, v);

	//��`�̐F����ς���
	DWORD color = 0xff666699;
	HELPER_2D->SetVerticesColor(m_vertices, color);

	return true;
}

//�������
void UIBar::Finalize()
{
	m_texture.Finalize();
}

void UIBar::Update()
{
}

void UIBar::Render()
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
