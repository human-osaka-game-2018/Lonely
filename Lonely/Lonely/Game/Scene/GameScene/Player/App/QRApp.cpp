/**
* @file QRApp.cpp
* @brief QRAppクラスのソースファイル
* @author shion-sagawa
*/

#include "QRApp.h"

#include "GameLib.h"
#include "Scene/GameScene/SharedInformation/SharedInformation.h"
#include "Scene/GameScene/SharedInformation/EnumGameState.h"


QRApp::QRApp()
{
	Initialize();
}

QRApp::~QRApp()
{
	Finalize();
}

bool QRApp::Initialize()
{
	m_pSharedInformation = SharedInformation::Instance.GetSharedInformation();
	m_pTexStorage = GameLib::Instance.GetTexStorage();
	m_font.Initialize(30);

	//テクスチャ読み込み
	m_pTexStorage->CreateTex(_T("Getting_QR"), _T("../Graphics/Texture/smartphone.png"));

	m_state = IS_NOT_GETTING;
	m_gettingStateCount = 0;
	m_retentionQrNum = 0;
	
	//頂点情報を設定
	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());
	HELPER_2D->SetVerticesFromCenterType(m_verticesGettingQR, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 250.f, 300.f);

	return true;
}

void QRApp::Finalize()
{
}

void QRApp::Update()
{
	if (m_state == IS_NOT_GETTING)
	{
		return;
	}

	//「QRとれますよ」「物体移動できますよ」などのヒント画面を取得QR数によって出していきたい



	const int FRAME_LIMIT = 60;
	if (m_state == IS_GETTING)
	{
		//QR取得したことを制限時間経過するまでスキップできないように
		if (m_gettingStateCount < FRAME_LIMIT)
		{
			++m_gettingStateCount;
		}//取得中表示の時間が経過したら
		else if (m_gettingStateCount >= FRAME_LIMIT)
		{
			if (DIRECT_INPUT->KeyboardIsHeld(DIK_RETURN))
			{
				m_state = IS_NOT_GETTING;
				//取得が完了したらカウントをゼロにする
				m_gettingStateCount = 0;
				//一次停止フラグをオフにする
				m_pSharedInformation->SetGameState(PLAY);
			}
		}
	}

	if (DIRECT_INPUT->KeyboardIsPressed(DIK_1))
	{
		m_retentionQrNum = 9;
	}

	//一次停止中なら返す
	if (m_pSharedInformation->GetGameState() == PAUSE)
	{
		return;
	}
}

void QRApp::Render()
{
	if (m_state == IS_NOT_GETTING)
	{
		return;
	}

	//取得中表示を描画する
	
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	pDirectX->SetRenderMode(DirectX::Normal, true);

	//頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("Getting_QR")));

	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesGettingQR, sizeof(Simple2DVertex));

	if (m_gettingStateCount > 10) 
	{
		char currentQrNumString[50];
		sprintf_s(currentQrNumString, 50, "QR数\n\t%2d / %2d", m_retentionQrNum, m_totalNumQr);
		DEBUGFONT->DrawText(540, 250, 0xff000000, currentQrNumString);

		if (m_gettingStateCount > 40)
		{
			if (m_retentionQrNum < m_totalNumQr)
			{
				char restQrNumString[50];
				sprintf_s(restQrNumString, 50, "残りQR数\n\t%2d個", m_totalNumQr - m_retentionQrNum);
				DEBUGFONT->DrawText(540, 450, 0xff000000, restQrNumString);
			}
			else
			{
				char clearString[50];
				sprintf_s(clearString, 50, "QR取得により\nパスワード完成！\n\n扉から脱出しよう！");
				m_font.DrawText(540, 450, 0xff000000, clearString);
			}
		}
	}
}

void QRApp::Acquire()
{
	m_state = IS_GETTING;
	++m_retentionQrNum;
}
