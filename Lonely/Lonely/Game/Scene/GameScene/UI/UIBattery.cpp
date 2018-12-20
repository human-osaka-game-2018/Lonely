/**
* @file UIBattery.cpp
* @brief UIBattery�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "UIBattery.h"
#include "../../../../GameLib/GameLib.h"

UIBattery::UIBattery()
{
	Initialize();
}

UIBattery::~UIBattery()
{
	Finalize();
}

//����������
bool UIBattery::Initialize()
{
	// assets�t�H���_����bridge.png���e�N�X�`���[�Ƃ��ēǂݍ���
	/*if (!m_texture.Load("../Graphics/UIFootsteps.png"))
	{
		return false;
	}*/

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 150.f, WINDOW_HEIGHT - 90.f, 400.f, 35.f);

	return true;
}

//�������
void UIBattery::Finalize()
{
	m_texture.Finalize();
}

void UIBattery::Update()
{
}

void UIBattery::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//���_�ɓ����f�[�^��ݒ�
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//�`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));

	//�[�d����������`�悷��
	DEBUGFONT->DrawText(50, 680, 0xffffffff, "100%");
}
