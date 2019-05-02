/**
* @file TriggerMovable.cpp
* @brief TriggerMovableクラスのソースファイル
* @author shion-sagawa
*/

#include "TriggerMovable.h"

#include <d3dx9math.h>

#include "GameLib.h"
#include "CollisionManager/EnumCollision/Enum_CollisionType.h"
#include "CollisionManager/CollisionBase/CollisionBox.h"

TriggerMovable::TriggerMovable()
{
	Initialize();
}

TriggerMovable::~TriggerMovable()
{
	Finalize();
}

TriggerMovable::TriggerMovable(D3DXVECTOR3* position, D3DXVECTOR3* boxLength)
{
	m_position.x = position->x;
	m_position.y = position->y;
	m_position.z = position->z;

	m_prevPosition = m_position;
	m_followingPositionExceptY = m_position;

	m_triggerType = TRIGGER_MOVABLE;
	m_collides = false;
	m_pCollision = new CollisionBox(this, TRIGGER, boxLength);

	Initialize();
}

bool TriggerMovable::Initialize()
{
	m_pTexStorage->CreateTex(_T("MovableIcon"), _T("../Graphics/Texture/Icon_Push.png"));

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromLeftTopType(m_verticesCallout, 0.f, WINDOW_HEIGHT - 450.f, 300.f, 300.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_verticesMovableIcon, 100.f, WINDOW_HEIGHT - 300.f, 100.f, 100.f);


	return true;
}

void TriggerMovable::Finalize()
{
	delete m_pCollision;
}

void TriggerMovable::Update()
{
	//衝突していたらcollidesはTrueになるので、常にfalseにしておく
	m_collides = false;

	//当たり判定を登録する
	m_pCollisionManager->RegisterCollision(m_pCollision);
}

void TriggerMovable::Render()
{
	if (m_collides == false) 
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	pDirectX->SetRenderMode(DirectX::Normal, true);

	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);
	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("Callout")));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesCallout, sizeof(Simple2DVertex));

	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("MovableIcon")));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesMovableIcon, sizeof(Simple2DVertex));


	char hukidasiString[50];
	sprintf_s(hukidasiString, 50, " ENTERキー\n    + 移動");

	DEBUGFONT->DrawText(30, WINDOW->GetHeight() - 400, 0xff000000, hukidasiString);
}
