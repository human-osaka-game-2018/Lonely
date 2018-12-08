/**
* @file TitleLogo.cpp
* @brief TitleLogo�N���X�̃\�[�X�t�@�C��
* @author ����@�k��
*/

#include "TitleLogo.h"
#include "../../../GameLib/GameLib.h"

TitleLogo::TitleLogo()
{
	Initialize();
}

TitleLogo::~TitleLogo()
{
	Finalize();
}

//����������
bool TitleLogo::Initialize()
{
	// assets�t�H���_����bridge.png���e�N�X�`���[�Ƃ��ēǂݍ���
	if (!m_texture.Load("../Graphics/TitleLogo.png"))
	{
		return false;
	}

	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>((float)m_texture.GetHeight());

	//���_�̍��W���Z�b�g
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth())/2
		, static_cast<float>(WINDOW->GetHeight())/4
		, logoWidth, logoHeight);

	return true;
}

//�������
void TitleLogo::Finalize()
{
	m_texture.Finalize();
}

//�X�V����
void TitleLogo::Update()
{
	//���t���[���A���l�܂Ń��S��傫�����鏈��
	if (logoWidth <= 450.f) 
	{
		logoHeight += 4.f;
		logoWidth += 6.f;

		//���_�̍��W���Z�b�g
		HELPER_2D->SetVerticesFromCenterType(m_vertices
			, static_cast<float>(WINDOW->GetWidth()) / 2
			, static_cast<float>(WINDOW->GetHeight()) / 3
			, logoWidth, logoHeight);
		
	}
}

void TitleLogo::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	//�`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

}
