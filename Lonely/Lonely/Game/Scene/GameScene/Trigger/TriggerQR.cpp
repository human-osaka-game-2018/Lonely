/**
* @file TriggerQR.cpp
* @brief TriggerQRクラスのソースファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

#include "TriggerQR.h"
#include "../../../../GameLib/CollisionManager/EnumCollision/Enum_CollisionType.h"
#include "../../../../GameLib/CollisionManager/CollisionBase/CollisionBox.h"
#include "../../../../GameLib/GameLib.h"
#include "../SharedInformation/EnumGameState.h"

TriggerQR::TriggerQR()
{
	Initialize();
}

TriggerQR::~TriggerQR()
{
	Finalize();
}

TriggerQR::TriggerQR(D3DXVECTOR3* position, D3DXVECTOR3* boxLength)
{
	m_position.x = position->x;
	m_position.y = position->y;
	m_position.z = position->z;

	m_prevPosition.x = position->x;
	m_prevPosition.y = position->y;
	m_prevPosition.z = position->z;

	m_triggerType = TRIGGER_QR;
	m_collides = false;
	m_state = IS_NOT_GETTED;
	m_gettingStateCount = 0;
	m_pCollision = new CollisionBox(this, TRIGGER, boxLength);

	Initialize();
}

bool TriggerQR::Initialize()
{
	if (!m_textureQR.Load("../Graphics/Texture/QR_white.png"))
	{
		return false;
	}

	if (!m_textureIconQR.Load("../Graphics/Texture/Icon_QR.png"))
	{
		return false;
	}

	if (!m_textureGettingQR.Load("../Graphics/Texture/gettingQR.png"))
	{
		return false;
	}

	// テクスチャーサイズから画像サイズのUVを取得(画像が2の累乗であれば1.0fになる)
	// テクスチャが2の累乗でないときに効果を発揮する
	float u = static_cast<float>(m_textureGettingQR.GetSrcWidth()) / static_cast<float>(m_textureGettingQR.GetWidth());
	float v = static_cast<float>(m_textureGettingQR.GetSrcHeight()) / static_cast<float>(m_textureGettingQR.GetHeight());

	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromCenterType(m_verticesGettingQR, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 400.f, 250.f, u, v);
	
	return true;
}

void TriggerQR::Finalize()
{
	m_textureQR.Finalize();
	m_textureIconQR.Finalize();
	m_textureGettingQR.Finalize();
	delete m_pCollision;
}

void TriggerQR::Update()
{
	//既にQRが取得されていたら返す
	if (m_state == IS_GETTED)
	{
		return;
	}

	if (m_state == IS_NOT_GETTED)
	{
		if (m_collides == true)
		{
			if(DIRECT_INPUT->KeyboardIsHeld(DIK_RETURN))
			{
				m_state = IS_GETTING;
				//一次停止フラグをオンにする
				m_pSharedInformation->SetGameState(PAUSE);
			}
		}
	}
	
	if (m_state == IS_GETTING)
	{
		if (m_gettingStateCount < 90) 
		{
			++m_gettingStateCount;
		}
		//取得中表示の時間が経過したら
		else if (m_gettingStateCount >= 90)
		{
			if (DIRECT_INPUT->KeyboardIsHeld(DIK_RETURN))
			{
				m_state = IS_GETTED;
				//一次停止フラグをオフにする
				m_pSharedInformation->SetGameState(PLAY);
			}
		}
	}

	//一次停止中なら返す
	if (m_pSharedInformation->GetGameState() == PAUSE)
	{
		return;
	}
	//衝突していたらcollidesはTrueになるので、常にfalseにしておく
	m_collides = false;

	//当たり判定を登録する
	m_pCollisionManager->RegisterCollision(m_pCollision);

}

void TriggerQR::Render()
{
	if (m_state == IS_GETTED)
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

	float m_radius = 0.6f;
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
	pDevice->SetTexture(0, m_textureQR.GetD3DTexture());
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesQR, sizeof(SimpleTexVertex));

	if (m_collides == false)
	{
		return;
	}

	// モデルの行列を算出
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);
	//ビュー逆行列を算出
	D3DXMatrixIdentity(&matView);
	m_radius = 0.25f;
	D3DXMatrixScaling(&scale, m_radius, m_radius, m_radius);
	D3DXMatrixTranslation(&trans, (m_position.x + 1.5f), (m_position.y + 2.0f), m_position.z);
	
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
	pDevice->SetTexture(0, m_textureIconQR.GetD3DTexture());
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesIconQR, sizeof(SimpleTexVertex));
	

	//取得中表示を描画する
	if (m_state == IS_GETTING)
	{
		//頂点に入れるデータを設定
		pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_textureGettingQR.GetD3DTexture());

		//描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesGettingQR, sizeof(Simple2DVertex));
	}
}
