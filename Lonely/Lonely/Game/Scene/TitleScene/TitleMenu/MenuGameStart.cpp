/**
* @file MenuGameStart.cpp
* @brief MenuGameStart�N���X�̃\�[�X�t�@�C��
* @author ����@�k��
*/

#include "MenuGameStart.h"
#include "TitleMenu.h"
#include "../../../../GameLib/GameLib.h"


MenuGameStart::MenuGameStart()
{
}

MenuGameStart::~MenuGameStart()
{
	Finalize();
}

//����������
bool MenuGameStart::Initialize()
{
	//�e�N�X�`���[�ǂݍ���
	if (!m_texture.Load("../Graphics/gameStart.png"))
	{
		return false;
	}

	//���_�̍��W���Z�b�g
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 16 * 11
		, 200.f
		, 80.f);

	//�n�߂͕`�悵�Ȃ�
	canRender = false;

	return true;
}

//�������
void MenuGameStart::Finalize()
{
	m_texture.Finalize();
}

//�X�V����
void MenuGameStart::Update(int step)
{
	if (step != STEP1)
	{
		//�X�e�b�v�P�ȊO�͕`�悷��
		canRender = true;
	}
}

//�`�悷��
void MenuGameStart::Render()
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
