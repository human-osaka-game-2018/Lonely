/**
* @file	Direct3D.cpp
* @brief Direct3Dクラスのソースファイル
* @author shion-sagawa　嗣苑
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


// DirectXの初期化
bool DirectX::Initialize(HWND hWnd, int width, int height, bool isFullscreen)
{
	if (m_pD3D != NULL || m_pDevice != NULL) return false;

	// IDirect3D9オブジェクトの作成
	if ((m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Deviceの設定
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
	// VSYNC待ち有り)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// Direct3Dデバイスの生成
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

// DirectXの終了処理
void DirectX::Finalize()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3D);
}


// 描画シーンの開始
void DirectX::BeginRenderScene()
{
	if (m_pDevice != nullptr) m_pDevice->BeginScene();
}

// 描画シーンの終了
void DirectX::EndRenderScene()
{
	if (m_pDevice != nullptr) m_pDevice->EndScene();
}

// バックバッファのクリア
void DirectX::ClearBackBuffer(DWORD target, D3DCOLOR color, float depth, DWORD stencil)
{
	if (m_pDevice) m_pDevice->Clear(0, NULL, target, color, depth, stencil);
}

// 画面のフリップ
void DirectX::FlipDisp()
{
	if (m_pDevice == NULL) return;

	if (FAILED(m_pDevice->Present(NULL, NULL, NULL, NULL)))
	{
		m_pDevice->Reset(&m_d3dpp);
	}
}

// 初期の描画ステートを設定
void DirectX::SetDefaultRenderState()
{
	// カリングモード
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// フィルモード
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// Zバッファを有効にするか？
	m_pDevice->SetRenderState(D3DRS_ZENABLE, true);
	// Zバッファの書き込みを有効にするか？
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	// Zテストの比較方法
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	// αブレンドを有効にするか？
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	// αテストを有効にするか？
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	// αテストの判定方法
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
	// αテストの参照値
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//	描画設定
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	// カラーステージ設定
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	// αステージ設定
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// テクスチャーフィルターの設定
	m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// テクスチャーのアドレッシングモードの設定
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

// 描画ステートの設定
void DirectX::SetRenderMode(ERenderMode mode, bool enableAlpha)
{
	// αが無効な場合は入力されたカラーをそのまま使う
	DWORD srcColorblend = D3DBLEND_ONE;
	DWORD dstColorblend = D3DBLEND_ZERO;
	if (enableAlpha)
	{
		// αが有効な場合はα値をカラーに影響させる
		srcColorblend = D3DBLEND_SRCALPHA;
		dstColorblend = D3DBLEND_INVSRCALPHA;
		// αテストでα値が0の場合は描画をしないように設定
		m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
		m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}
	// αブレンドとαテストの有無を設定
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, enableAlpha);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, enableAlpha);

	switch (mode)
	{
	case Normal:
		// αが有効：(SrcColor * 1) + (DestColor * 0)
		// αが無効：(SrcColor * α) + (DestColor * (1 - α))
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, dstColorblend);
		break;
	case Add:
		// αが有効：(SrcColor * 1) + (DestColor * 1)
		// αが無効：(SrcColor * α) + (DestColor * 1)
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Subtract:
		// αが有効：(DestColor * 1) - (SrcColor * 1)
		// αが無効：(DestColor * 1) - (SrcColor * α)
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Multiple:
		// 共通：(SrcColor * 0) + (DestColor * SrcColor)
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	}
}
