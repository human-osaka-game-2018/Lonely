/**
* @file TriggerDoor.cpp
* @brief TriggerDoorクラスのソースファイル
* @author shion-sagawa
*/

#include "TriggerDoor.h"

#include <d3dx9math.h>

#include "GameLib/GameLib.h"

#include "Scene/GameScene/SharedInformation/EnumGameState.h"
#include "CollisionManager/EnumCollision/Enum_CollisionType.h"
#include "CollisionManager/CollisionBase/CollisionBox.h"

TriggerDoor::TriggerDoor()
{
	Initialize();
}

TriggerDoor::~TriggerDoor()
{
	Finalize();
}

TriggerDoor::TriggerDoor(D3DXVECTOR3* position, D3DXVECTOR3* boxLength, QRApp* pQrApp)
{
	m_position.x = position->x;
	m_position.y = position->y;
	m_position.z = position->z;

	m_prevPosition.x = position->x;
	m_prevPosition.y = position->y;
	m_prevPosition.z = position->z;

	m_collides = false;
	m_pCollision = new CollisionBox(this, TRIGGER, boxLength);
	m_pQrApp = pQrApp;
	
	Initialize();
}

bool TriggerDoor::Initialize()
{
	m_pTexStorage->CreateTex(_T("Callout"),_T("../Graphics/Texture/hukidasi.png"));
	
	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_vertices, 0, WINDOW_HEIGHT -400, 300.f, 200.f);

	return true;
}

void TriggerDoor::Finalize()
{
	delete m_pCollision;
}

void TriggerDoor::Update()
{
	if (m_pSharedInformation->GetGameState() != PLAY)
	{
		return;
	}
	
	if (DIRECT_INPUT->KeyboardIsPressed(DIK_RETURN))
	{
		int QrNum = m_pQrApp->GetRetentionQrNum();

		//取得QR数がクリア条件数を超えていたらクリア
		if (this->m_collides == true && this->AchieveClearCondition(QrNum))
		{
			m_pSharedInformation->SetGameState(CLEAR);
		}
	}

	//衝突していたらcollidesはTrueになるので、常にfalseにしておく
	m_collides = false;

	//当たり判定を登録する
	m_pCollisionManager->RegisterCollision(m_pCollision);
}

void TriggerDoor::Render()
{
	if (m_collides == false)
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	pDirectX->SetRenderMode(DirectX::Normal, true);

	//頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("Callout")));
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(Simple2DVertex));
	
	
	char hukidasiString[50];
	sprintf_s(hukidasiString, 50, "ENTERキー\n\t→調べる");
	
	DEBUGFONT->DrawText(30, WINDOW->GetHeight() - 350, 0xff000000, hukidasiString);
}

