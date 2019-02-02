/**
* @file TrigarMovable.cpp
* @brief TrigarMovableクラスのソースファイル
* @author shion-sagawa
*/
#include <d3dx9math.h>

#include "TrigarMovable.h"
#include "../../../../GameLib/CollisionManager/EnumCollision/Enum_CollisionType.h"
#include "../../../../GameLib/CollisionManager/CollisionBase/CollisionBox.h"
#include "../../../../GameLib/GameLib.h"

TrigarMovable::TrigarMovable()
{
	Initialize();
}

TrigarMovable::~TrigarMovable()
{
	Finalize();
}

TrigarMovable::TrigarMovable(D3DXVECTOR3* position, D3DXVECTOR3* boxLength)
{
	m_position.x = position->x;
	m_position.y = position->y;
	m_position.z = position->z;

	m_prevPosition = m_position;
	m_followingPositionExceptY = m_position;

	m_trigarType = TRIGAR_MOVABLE;
	m_collides = false;
	m_pCollision = new CollisionBox(this, TRIGAR, boxLength);

	Initialize();
}

bool TrigarMovable::Initialize()
{
	if (!m_texture.Load("../Graphics/Icon_push.png"))
	{
		return false;
	}

	return true;
}

void TrigarMovable::Finalize()
{
	m_texture.Finalize();
	delete m_pCollision;
}

void TrigarMovable::Update()
{
	//衝突していたらcollidesはTrueになるので、常にfalseにしておく
	m_collides = false;

	//当たり判定を登録する
	m_pCollisionManager->RegisterCollision(m_pCollision);
}

void TrigarMovable::Render()
{
	if (m_collides == false) 
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// モデルの行列を算出
	D3DXMATRIX world;
	D3DXMATRIX rot, trans, scale;
	D3DXMatrixIdentity(&world);
	//D3DXMatrixIdentity(&rot);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);
	//ビュー逆行列を算出
	D3DXMATRIX matView, matInverseView;
	D3DXMatrixIdentity(&matView);
	//pDevice->GetTransform(D3DTS_VIEW, &matView);

	float m_radius = 0.2f;
	D3DXMatrixScaling(&scale, m_radius, m_radius, m_radius);
	//D3DXMatrixRotationY(&rot, (m_direction));
	D3DXMatrixTranslation(&trans, (m_position.x + 1.f), (m_position.y + 3.f), (m_position.z + 1.f));

	D3DXMatrixIdentity(&matInverseView);
	pDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInverseView, NULL, &matView);
	matInverseView._41 = 0.f;
	matInverseView._42 = 0.f;
	matInverseView._43 = 0.f;

	D3DXMatrixMultiply(&world, &world, &scale);
	D3DXMatrixMultiply(&world, &world, &matInverseView);
	D3DXMatrixMultiply(&world, &world, &trans);

	//ワールドトランスフォーム
	pDevice->SetTransform(D3DTS_WORLD, &world);


	//頂点に入れるデータを設定
	pDevice->SetFVF(FVF_SIMPLE_TEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(SimpleTexVertex));
}
