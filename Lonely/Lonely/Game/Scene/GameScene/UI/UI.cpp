/**
* @file UI.cpp
* @brief UIクラスのソースファイル
* @author shion-sagawa
*/

#include "UI.h"
#include "../../../../GameLib/GameLib.h"
#include "../SharedInformation/EnumGameState.h"

UI::UI()
	: m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
	, m_pSoundsManager(GameLib::Instance.GetSoundsManager())
{
	Initialize();
}

UI::~UI()
{
	Finalize();
}

//初期化する
bool UI::Initialize()
{
	m_pTexStorage = GameLib::Instance.GetTexStorage();
	m_pTexStorage->CreateTex(_T("sumahoGamen"), _T("../Graphics/Texture/smart phone.png"));

	if (!m_texture.Load("../Graphics/Texture/smart phone.png"))
	{
		return false;
	}

	float u = static_cast<float>(m_texture.GetSrcWidth()) / static_cast<float>(m_texture.GetWidth());
	float v = static_cast<float>(m_texture.GetSrcHeight()) / static_cast<float>(m_texture.GetHeight());

	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());
	m_minPositionY = 30;
	m_maxPositionY = WINDOW_HEIGHT - 150;
	m_positionY = m_maxPositionY;

	//頂点の座標をセット
	HELPER_2D->SetVerticesFromLeftTopType(m_vertices
		, 42
		, m_maxPositionY
		, m_width, m_height);

	const TCHAR* filePath = _T("../Sounds/SE/sumahoneko/catLikeButton1.mp3");
	m_pSoundsManager->AddFile(filePath, _T("catLikeButton1"));
	const TCHAR* filePath2 = _T("../Sounds/SE/sumahoneko/catLikeButton2.mp3");
	m_pSoundsManager->AddFile(filePath2, _T("catLikeButton2"));

	return true;
}

//解放する
void UI::Finalize()
{
	m_texture.Finalize();
}

//更新する
void UI::Update()
{
	if (m_pSharedInformation->GetGameState() != PLAY)
	{
		return;
	}

	if (DIRECT_INPUT->KeyboardIsReleased(DIK_F))
	{
		ChangeAppMenuState();
	}

	if (m_appMenuState == NOT_USING)
	{
		return;
	}

	const float accelerationVelocity = 20.f;
	const float initialVelocity = 20.f;

	if (m_appMenuState == STARTING)
	{
		++m_appMenuMoveCount;
		m_positionY -= initialVelocity + accelerationVelocity * m_appMenuMoveCount;
		if (m_positionY <= m_minPositionY)
		{
			m_positionY = m_minPositionY;
			m_appMenuState = USING;
			m_appMenuMoveCount = 0;
		}
		HELPER_2D->SetVerticesFromLeftTopType(m_vertices
			, 42
			, m_positionY
			, m_width, m_height);
	}
	else if (m_appMenuState == STOPPING)
	{
		++m_appMenuMoveCount;
		m_positionY += initialVelocity + accelerationVelocity * m_appMenuMoveCount;
		if (m_positionY >= m_maxPositionY)
		{
			m_positionY = m_maxPositionY;
			m_appMenuState = NOT_USING;
			m_appMenuMoveCount = 0;
		}
		HELPER_2D->SetVerticesFromLeftTopType(m_vertices
			, 42
			, m_positionY
			, m_width, m_height);
	}
}

//描画する
void UI::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();
	pDirectX->SetRenderMode(DirectX::Normal, true);

	// 頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);
	//テクスチャの設定
	//pDevice->SetTexture(0, m_texture.GetD3DTexture());
	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("sumahoGamen")));
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
}

void UI::ChangeAppMenuState()
{
	if (m_appMenuState == NOT_USING)
	{
		m_appMenuState = STARTING;
		m_pSoundsManager->Start(_T("catLikeButton2"), false);
	}
	else if (m_appMenuState == USING)
	{
		m_appMenuState = STOPPING;
		m_pSoundsManager->Start(_T("catLikeButton1"), false);
	}
}
