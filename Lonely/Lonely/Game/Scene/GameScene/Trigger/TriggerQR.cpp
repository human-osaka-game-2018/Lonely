/**
* @file TriggerQR.cpp
* @brief TriggerQRクラスのソースファイル
* @author shion-sagawa
*/

#pragma once

#include "TriggerQR.h"

#include <d3dx9math.h>

#include "GameLib.h"
#include "CollisionManager/EnumCollision/Enum_CollisionType.h"
#include "CollisionManager/CollisionBase/CollisionBox.h"
#include "../SharedInformation/EnumGameState.h"

TriggerQR::TriggerQR()
{
	Initialize();
}

TriggerQR::~TriggerQR()
{
	Finalize();
}

TriggerQR::TriggerQR(D3DXVECTOR3* position, D3DXVECTOR3* boxLength, QRApp* pQrApp)
{
	m_position.x = position->x;
	m_position.y = position->y;
	m_position.z = position->z;

	m_prevPosition.x = position->x;
	m_prevPosition.y = position->y;
	m_prevPosition.z = position->z;

	m_triggerType = TRIGGER_QR;
	m_collides = false;
	m_isGetted = false;
	m_pCollision = new CollisionBox(this, TRIGGER, boxLength);
	m_pQrApp = pQrApp;

	Initialize();
}

bool TriggerQR::Initialize()
{
	m_pTexStorage->CreateTex(_T("QrCord"), _T("../Graphics/Texture/QR_white.png"));
	m_pTexStorage->CreateTex(_T("QrIcon"), _T("../Graphics/Texture/Icon_QR.png"));
	m_pTexStorage->CreateTex(_T("SmartphoneScreen"), _T("../Graphics/Texture/smartphone.png"));


	float WINDOW_WIDTH = static_cast<float>(WINDOW->GetWidth());
	float WINDOW_HEIGHT = static_cast<float>(WINDOW->GetHeight());

	HELPER_2D->SetVerticesFromCenterType(m_verticesGettingQR, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 250.f, 300.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_verticesCallout, 0.f, WINDOW_HEIGHT - 400.f, 300.f, 250.f);
	HELPER_2D->SetVerticesFromLeftTopType(m_verticesQrIcon, 100.f, WINDOW_HEIGHT - 300.f, 100.f, 100.f);

	
	return true;
}

void TriggerQR::Finalize()
{
	delete m_pCollision;
}

void TriggerQR::Update()
{
	if (m_isGetted == true)
	{
		return;
	}

	if (this->m_collides) 
	{
		if (DIRECT_INPUT->KeyboardIsPressed(DIK_RETURN))
		{
			m_pQrApp->Acquire();
			m_isGetted = true;
		}
	}

	//衝突していたらcollidesはTrueになるので、常にfalseにしておく
	m_collides = false;

	//当たり判定を登録する
	m_pCollisionManager->RegisterCollision(m_pCollision);

}

void TriggerQR::Render()
{
	if (m_isGetted == true)
	{
		return;
	}

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	pDirectX->SetRenderMode(DirectX::Normal, false);

	// モデルの行列を算出
	D3DXMATRIX world;
	D3DXMATRIX rot, trans, scale;
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);
	//ビュー逆行列を算出
	D3DXMATRIX matView, matInverseView;
	D3DXMatrixIdentity(&matView);

	float m_radius = 0.6f;
	D3DXMatrixScaling(&scale, m_radius, m_radius, m_radius);
	D3DXMatrixTranslation(&trans, m_position.x, (m_position.y + 0.75f), m_position.z);

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
	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("QrCord")));
	//描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesQR, sizeof(SimpleTexVertex));

	if (m_collides == false)
	{
		return;
	}

	pDirectX->SetRenderMode(DirectX::Normal, true);

	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);
	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("Callout")));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesCallout, sizeof(Simple2DVertex));

	pDevice->SetTexture(0, m_pTexStorage->GetTex(_T("QrIcon")));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_verticesQrIcon, sizeof(Simple2DVertex));


	char hukidasiString[50];
	sprintf_s(hukidasiString, 50, " ENTERキー\n");

	DEBUGFONT->DrawText(30, WINDOW->GetHeight() - 350, 0xff000000, hukidasiString);
}
