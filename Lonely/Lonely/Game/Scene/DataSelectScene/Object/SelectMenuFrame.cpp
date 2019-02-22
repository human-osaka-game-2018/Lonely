/**
* @file SelectMenuFrame.cpp
* @brief SelectMenuFrame�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "SelectMenuFrame.h"
#include "../../../../GameLib/GameLib.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/Texture.h"


SelectMenuFrame::SelectMenuFrame()
{
	Initialize();
}

SelectMenuFrame::SelectMenuFrame(SelectCursorInformation* instance)
	: m_pSelectCursorInformation(instance)
{
	Initialize();
}

SelectMenuFrame::~SelectMenuFrame()
{
	Finalize();
}

//����������
bool SelectMenuFrame::Initialize()
{
	// �e�N�X�`���[�T�C�Y����摜�T�C�Y��UV���擾(�摜��2�̗ݏ�ł����1.0f�ɂȂ�)
	// �e�N�X�`����2�̗ݏ�łȂ��Ƃ��Ɍ��ʂ𔭊�����
	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());
	
	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	DWORD color = 0xFF666699;
	DWORD backFrameColor = 0xAA000000;

	HELPER_2D->SetVerticesFromCenterType(m_vertices, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 450.f, 250.f, u, v);
	HELPER_2D->SetVerticesColor(m_vertices, color);

	HELPER_2D->SetVerticesFromCenterType(m_verticesBackFrame, 0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT);
	HELPER_2D->SetVerticesColor(m_verticesBackFrame, backFrameColor);
	
	m_canRender = false;

	return true;
}

//�������
void SelectMenuFrame::Finalize()
{
	m_texture.Finalize();
}

void SelectMenuFrame::Update()
{
	int miniCursorState = m_pSelectCursorInformation->GetMiniCursorState();
	
	if (miniCursorState == NOT_RENDER)
	{
		m_canRender = false;
		return;
	}

	m_canRender = true;
}

void SelectMenuFrame::Render()
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
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesBackFrame, sizeof(Simple2DVertex));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
}
