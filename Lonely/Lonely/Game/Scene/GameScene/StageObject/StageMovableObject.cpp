/**
* @file StageMovableObject.cpp
* @brief StageMovableObjectクラスのソースファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

#include "StageMovableObject.h"
//#include "../../../../GameLib/CollisionManager/EnumCollision/Enum_CollisionType.h"
//#include "../../../../GameLib/CollisionManager/CollisionBase/CollisionBox.h"
#include "../../../../GameLib/GameLib.h"
#include "../SharedInformation/EnumGameState.h"

StageMovableObject::StageMovableObject()
{
}

StageMovableObject::~StageMovableObject()
{
	Finalize();
}

StageMovableObject::StageMovableObject(D3DXVECTOR3* position, D3DXVECTOR3* myBoxLength, D3DXVECTOR3* triggersBoxLength, Sumahoneko* pSumahoneko)
{
	m_position.x = position->x;
	m_position.y = position->y;
	m_position.z = position->z;

	m_prevPosition = m_position;
	m_followingPositionExceptY = m_position;

	m_pSumahoneko = pSumahoneko;

	m_trigger = (new TriggerMovable(position, triggersBoxLength));

	m_collides = false;
	m_pCollision = new CollisionBox(this, STAGE_OBJECT, myBoxLength);

	Initialize();
}

bool StageMovableObject::Initialize()
{
	m_fbxModel.Load("../Graphics/fbxModel/danbol.fbx");
	m_shpere.CreateShpere(32);
	m_radius = 0.8f;
	m_rotation = 0.f;
	return true;

	if (!m_texture.Load("../Graphics/Texture/Icon_Push.png"))
	{
		return false;
	}

	return true;
}

void StageMovableObject::Finalize()
{
	m_fbxModel.Finalize();
	m_texture.Finalize();
}

void StageMovableObject::Update()
{
	
	//一次停止中なら返す
	if (m_pSharedInformation->GetGameState() == PAUSE)
	{
		return;
	}

	if (m_trigger->IsCollided())
	{
		if (DIRECT_INPUT->KeyboardIsHeld(DIK_RETURN))
		{
			//移動処理を行う前の値を保存しておく
			m_prevPosition = m_position;

			//移動処理を行う
			D3DXVECTOR3 playerMovement = m_pSharedInformation->GetPlayerMovement();
			m_position.x += playerMovement.x;
			m_position.z += playerMovement.z;
			m_followingPositionExceptY.x += playerMovement.x;
			m_followingPositionExceptY.z += playerMovement.z;

			m_trigger->SetPosition(&m_position);

			m_pCollision->SetType(PLAYER_WITH_OBJECT);
		}
		else
		{
			m_pCollision->SetType(STAGE_OBJECT);
		}
	}
	else
	{
		m_pCollision->SetType(STAGE_OBJECT);
	}

	//衝突していたらcollidesはTrueになるので、常にfalseにしておく
	m_collides = false;

	//当たり判定を登録する
	m_pCollisionManager->RegisterCollision(m_pCollision);

	m_trigger->Update();
}

void StageMovableObject::Render()
{
	m_trigger->Render();

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// 通常書き込みモードに設定
	pDirectX->SetRenderMode(DirectX::Normal, false);

	// Zテストの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	// モデルの行列を算出
	D3DXMATRIX rot, trans, scale;
	D3DXMatrixScaling(&scale, m_radius, m_radius, m_radius);
	D3DXMatrixRotationY(&rot, (m_rotation));
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	D3DXMatrixMultiply(m_shpere.GetWorld(), &scale, &rot);
	D3DXMatrixMultiply(m_shpere.GetWorld(), m_shpere.GetWorld(), &trans);

	*m_fbxModel.GetWorld() = *m_shpere.GetWorld();

	// モデルの描画
	m_fbxModel.Render();

	if (m_collides == false)
	{
		return;
	}

	// モデルの行列を算出
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	//D3DXMatrixIdentity(&rot);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);
	//ビュー逆行列を算出
	D3DXMATRIX matView, matInverseView;

	float m_radius = 1.2f;
	D3DXMatrixScaling(&scale, m_radius, m_radius, m_radius);
	//D3DXMatrixRotationY(&rot, (m_direction));
	D3DXMatrixTranslation(&trans, m_position.x, (m_position.y + 0.75f), m_position.z);
	//D3DXMatrixTranslation(&trans, 7.0f, 0.5f, 10.0f);
	//D3DXMatrixMultiply(&world, &scale, &matInverseView);


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

void StageMovableObject::RevertPosition()
{
	//移動する前の位置に戻す
	m_position = m_prevPosition;
	m_followingPositionExceptY = m_prevPosition;

	m_trigger->SetPosition(&m_position);
}
