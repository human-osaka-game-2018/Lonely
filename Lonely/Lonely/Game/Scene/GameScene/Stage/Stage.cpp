/**
* @file Stage.cpp
* @brief Stageクラスのソースファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

#include "Stage.h"
#include "../../../../GameLib/GameLib.h"

Stage::Stage()
	:m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
{
	Initialize();
}

Stage::~Stage()
{
	Finalize();
}

bool Stage::Initialize()
{
	m_fbxModel.Load("../Graphics/fbxModel/stage207.fbx");
	m_pSharedInformation->SetStageFbx(&m_fbxModel);

	m_position = { 0.f, 0.f, 0.f };
	m_radius = 0.2f;
	//m_radius = 1.f;
	m_direction = 0.f;

	return true;
}

void Stage::Finalize()
{
	m_fbxModel.Finalize();
}

void Stage::Update()
{
	// モデルの行列を算出
	D3DXMATRIX rot, trans, scale;
	D3DXMatrixScaling(&scale, m_radius, m_radius, m_radius);
	D3DXMatrixRotationY(&rot, (m_direction));
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	D3DXMatrixMultiply(m_shpere.GetWorld(), &scale, &rot);
	D3DXMatrixMultiply(m_shpere.GetWorld(), m_shpere.GetWorld(), &trans);

	*m_fbxModel.GetWorld() = *m_shpere.GetWorld();
}

void Stage::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// 通常書き込みモードに設定
	pDirectX->SetRenderMode(DirectX::Normal, false);

	// Zテストの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// モデルの描画
	m_fbxModel.Render();
}

//if (typeA == STAGE)
//{
//	Stage* stage = dynamic_cast<Stage*>(this->GetOwner());
//	FbxModel* stageModel = stage->GetFbxModel();
//
//	if (typeB == PLAYER)
//	{
//		Sumahoneko* sumahoneko = dynamic_cast<Sumahoneko*>(collider->GetOwner());
//		D3DXVECTOR3 position(0.f, 0.f, 0.f);
//		float dist = 10.f;
//
//		//スマホ猫や、ボールなどが下に重力があるなら
//		if (sumahoneko->Falls())
//		{
//			//sumahonekoにかかっている重力分だけレイを飛ばす
//			if (stageModel->RayPick(&position, &position, &dist, &position) != -1)
//			{
//
//			}
//		}
//
//	}
//	else if (typeB == ENEMY)
//	{
//		Pasoken* pasoken = dynamic_cast<Pasoken*>(collider->GetOwner());
//	}
//	else if (typeB == STAGE_OBJECT)
//	{
//
//	}
//	else if (typeB == TRIGGER)
//	{
//
//	}
//}
