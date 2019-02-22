/**
* @file MenuPressEnter.cpp
* @brief MenuPressEnter�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "MenuPressEnter.h"
#include "TitleMenu.h"
#include "../../../../GameLib/GameLib.h"


MenuPressEnter::MenuPressEnter()
{
}

MenuPressEnter::~MenuPressEnter()
{
	Finalize();
}

//����������
bool MenuPressEnter::Initialize()
{
	//�e�N�X�`���[�ǂݍ���
	if (!m_texture.Load("../Graphics/pressEnter.png"))
	{
		return false;
	}

	//���_�̍��W���Z�b�g
	HELPER_2D->SetVerticesFromCenterType(m_vertices
		, static_cast<float>(WINDOW->GetWidth()) / 2
		, static_cast<float>(WINDOW->GetHeight()) / 4 * 3
		, 200.f
		, 80.f);

	return true;
}

//�������
void MenuPressEnter::Finalize()
{
	m_texture.Finalize();
}

//�X�V����
void MenuPressEnter::Update(int step)
{
	if (step == STEP1) {
		//�t���[���o�߂ŐF����ς���
		frameCount++;
		if (frameCount > 60)
		{
			static DWORD regulateColor = static_cast<DWORD>(0xffffffff);

			//�J���[�����l�B������A�t���[���J�E���g��0�ɖ߂�
			(regulateColor <= static_cast<DWORD>(0x02ffffff)) ? frameCount = 0 : frameCount;

			regulateColor -= static_cast<DWORD>(0x03000000);

			HELPER_2D->SetVerticesColor(m_vertices, regulateColor);
		}
	}
	else {

		//�X�e�b�v�P�ȊO�͕`�悵�Ȃ�
		m_canRender = false;
	}
}
	

//�`�悷��
void MenuPressEnter::Render()
{
	if (m_canRender == false)
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
