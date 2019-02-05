/**
* @file TriggerCharging.cpp
* @brief TriggerChargingクラスのソースファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

#include "TriggerCharging.h"

TriggerCharging::TriggerCharging()
{
}

TriggerCharging::~TriggerCharging()
{
}

bool TriggerCharging::Initialize()
{
	return true;
}

void TriggerCharging::Finalize()
{
	delete m_pCollision;
}

void TriggerCharging::Update()
{
	m_pCollisionManager->RegisterCollision(m_pCollision);
}

void TriggerCharging::Render()
{
	if (this->m_collides == true)
	{
		//アイコンを描画する
	}
}
