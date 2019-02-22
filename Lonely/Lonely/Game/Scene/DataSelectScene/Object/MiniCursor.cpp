/**
* @file MiniCursor.cpp
* @brief MiniCursor�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "MiniCursor.h"
#include "../../../../GameLib/GameLib.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/Texture.h"


MiniCursor::MiniCursor()
{
	Initialize();
}

MiniCursor::MiniCursor(SelectCursorInformation* instance)
	: m_pSelectCursorInformation(instance)
{
	Initialize();
}

MiniCursor::~MiniCursor()
{
	Finalize();
}

//����������
bool MiniCursor::Initialize()
{
	// assets�t�H���_����bridge.png���e�N�X�`���[�Ƃ��ēǂݍ���
	if (!m_texture.Load("../Graphics/menuCursor.png"))
	{
		return false;
	}

	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	// �e�N�X�`����2�̗ݏ�łȂ��Ƃ��Ɍ��ʂ𔭊�����
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 50.f, 100.f, 75.f, 75.f, u, v);

    m_canRender = false;

	return true;
}

//�������
void MiniCursor::Finalize()
{
	m_texture.Finalize();
}

void MiniCursor::Update()
{
	static int prevMiniCursorState = CONTINUE;
	int miniCursorState = m_pSelectCursorInformation->GetMiniCursorState();

	if (miniCursorState == prevMiniCursorState)
	{
		return;
	}

	m_canRender = true;

	switch (miniCursorState)
	{
	case CONTINUE:

		HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 220.f, 150.f);
		//if(ENTER){miniState = CONTINUE;}
		break;

	case NEWGAME:

		HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 220.f, 350.f);
		break;

	case BACK:

		HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 220.f, 550.f);
		break;

	case NOT_RENDER:

		m_canRender = false;
		break;
	}

	prevMiniCursorState = miniCursorState;
}

void MiniCursor::Render()
{
	if (m_canRender == false) 
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//���_�ɓ����f�[�^��ݒ�
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_texture.GetD3DTexture());

	//�`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
}
