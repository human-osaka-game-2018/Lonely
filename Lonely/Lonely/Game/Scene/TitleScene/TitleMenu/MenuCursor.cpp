/**
* @file MenuCursor.cpp
* @brief MenuCursor�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "MenuCursor.h"
#include "TitleMenu.h"
#include "../../../../GameLib/GameLib.h"


MenuCursor::MenuCursor()
{
}

MenuCursor::~MenuCursor()
{
	Finalize();
}

//����������
bool MenuCursor::Initialize()
{
	//�e�N�X�`���[�ǂݍ���
	if (!m_texture.Load("../Graphics/menuCursor.png"))
	{
		return false;
	}

	//���_�̍��W���Z�b�g
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 16 * 13
		, 30.f
		, 30.f);

	//�n�߂͕`�悵�Ȃ�
	canRender = false;

	return true;
}

//�������
void MenuCursor::Finalize()
{
	m_texture.Finalize();
}

//�X�V����
void MenuCursor::Update(int step)
{
	if (step == STEP1)
	{
		//�X�e�b�v�P�͕`�悵�Ȃ�
		canRender = false;
	}
	if (step == STEP2)
	{
		//�`�悷��
		canRender = true;
		//���_�̍��W���Z�b�g
		HELPER_2D->SetVerticesFromCenterType(m_vertices
			, static_cast<float>(WINDOW->GetWidth()) / 3
			, static_cast<float>(WINDOW->GetHeight()) / 16 * 11
			, 30.f
			, 30.f);
	}
	if (step == STEP3)
	{
		//�`�悷��
		canRender = true;
		//���_�̍��W���Z�b�g
		HELPER_2D->SetVerticesFromCenterType(m_vertices
			, static_cast<float>(WINDOW->GetWidth()) / 3
			, static_cast<float>(WINDOW->GetHeight()) / 16 * 13
			, 30.f
			, 30.f);
	}
}

//�`�悷��
void MenuCursor::Render()
{
	if (canRender == false)
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	//�`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
}
