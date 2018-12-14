/**
* @file MenuGameEnd.cpp
* @brief MenuGameEnd�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "MenuGameEnd.h"
#include "TitleMenu.h"
#include "../../../../GameLib/GameLib.h"


MenuGameEnd::MenuGameEnd()
{
}

MenuGameEnd::~MenuGameEnd()
{
	Finalize();
}

//����������
bool MenuGameEnd::Initialize()
{
	//�e�N�X�`���[�ǂݍ���
	if (!m_texture.Load("../Graphics/gameEnd.png"))
	{
		return false;
	}

	//���_�̍��W���Z�b�g
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 16 * 13 
		, 200.f
		, 80.f);

	//�n�߂͕`�悵�Ȃ�
	canRender = false;

	return true;
}

//�������
void MenuGameEnd::Finalize()
{
	m_texture.Finalize();
}

//�X�V����
void MenuGameEnd::Update(int step)
{
	if (step != STEP1)
	{
		//�X�e�b�v�P�ȊO�͕`�悷��
		canRender = true;
	}
}

//�`�悷��
void MenuGameEnd::Render()
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
