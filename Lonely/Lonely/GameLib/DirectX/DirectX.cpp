/**
* @file	Direct3D.cpp
* @brief Direct3D�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa�@�k��
*/

#include "DirectX.h"

DirectX::DirectX()
	: m_pD3D(NULL)
	, m_pDevice(NULL)
{
}

DirectX::~DirectX()
{
	Finalize();
}


// DirectX�̏�����
bool DirectX::Initialize(HWND hWnd, int width, int height, bool isFullscreen)
{
	if (m_pD3D != NULL || m_pDevice != NULL) return false;

	// IDirect3D9�I�u�W�F�N�g�̍쐬
	if ((m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Device�̐ݒ�
	d3dpp.Windowed = !isFullscreen;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;//D3DMULTISAMPLE_NONE;//D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.Flags = 0;
	d3dpp.BackBufferCount = 1;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	// VSYNC�҂��L��)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// Direct3D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		d3dpp.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&d3dpp,
		&m_pDevice)))
	{
		SAFE_RELEASE(m_pD3D);
		return false;
	}
	m_d3dpp = d3dpp;
	return true;
}

// DirectX�̏I������
void DirectX::Finalize()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3D);
}


// �`��V�[���̊J�n
void DirectX::BeginRenderScene()
{
	if (m_pDevice != nullptr) m_pDevice->BeginScene();
}

// �`��V�[���̏I��
void DirectX::EndRenderScene()
{
	if (m_pDevice != nullptr) m_pDevice->EndScene();
}

// �o�b�N�o�b�t�@�̃N���A
void DirectX::ClearBackBuffer(DWORD target, D3DCOLOR color, float depth, DWORD stencil)
{
	if (m_pDevice) m_pDevice->Clear(0, NULL, target, color, depth, stencil);
}

// ��ʂ̃t���b�v
void DirectX::FlipDisp()
{
	if (m_pDevice == NULL) return;

	if (FAILED(m_pDevice->Present(NULL, NULL, NULL, NULL)))
	{
		m_pDevice->Reset(&m_d3dpp);
	}
}

// �����̕`��X�e�[�g��ݒ�
void DirectX::SetDefaultRenderState()
{
	// �J�����O���[�h
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// �t�B�����[�h
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// Z�o�b�t�@��L���ɂ��邩�H
	m_pDevice->SetRenderState(D3DRS_ZENABLE, true);
	// Z�o�b�t�@�̏������݂�L���ɂ��邩�H
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	// Z�e�X�g�̔�r���@
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	// ���u�����h��L���ɂ��邩�H
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	// ���e�X�g��L���ɂ��邩�H
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	// ���e�X�g�̔�����@
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
	// ���e�X�g�̎Q�ƒl
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//	�`��ݒ�
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	// �J���[�X�e�[�W�ݒ�
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	// ���X�e�[�W�ݒ�
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// �e�N�X�`���[�t�B���^�[�̐ݒ�
	m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// �e�N�X�`���[�̃A�h���b�V���O���[�h�̐ݒ�
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

// �`��X�e�[�g�̐ݒ�
void DirectX::SetRenderMode(ERenderMode mode, bool enableAlpha)
{
	// ���������ȏꍇ�͓��͂��ꂽ�J���[�����̂܂܎g��
	DWORD srcColorblend = D3DBLEND_ONE;
	DWORD dstColorblend = D3DBLEND_ZERO;
	if (enableAlpha)
	{
		// �����L���ȏꍇ�̓��l���J���[�ɉe��������
		srcColorblend = D3DBLEND_SRCALPHA;
		dstColorblend = D3DBLEND_INVSRCALPHA;
		// ���e�X�g�Ń��l��0�̏ꍇ�͕`������Ȃ��悤�ɐݒ�
		m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
		m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}
	// ���u�����h�ƃ��e�X�g�̗L����ݒ�
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, enableAlpha);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, enableAlpha);

	switch (mode)
	{
	case Normal:
		// �����L���F(SrcColor * 1) + (DestColor * 0)
		// ���������F(SrcColor * ��) + (DestColor * (1 - ��))
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, dstColorblend);
		break;
	case Add:
		// �����L���F(SrcColor * 1) + (DestColor * 1)
		// ���������F(SrcColor * ��) + (DestColor * 1)
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Subtract:
		// �����L���F(DestColor * 1) - (SrcColor * 1)
		// ���������F(DestColor * 1) - (SrcColor * ��)
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Multiple:
		// ���ʁF(SrcColor * 0) + (DestColor * SrcColor)
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	}
}
