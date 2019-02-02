/**
* @file TrigarCharging.cpp
* @brief TrigarChargingクラスのソースファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

#include "TrigarCharging.h"

TrigarCharging::TrigarCharging()
{
}

TrigarCharging::~TrigarCharging()
{
}

bool TrigarCharging::Initialize()
{
	return true;
}

void TrigarCharging::Finalize()
{
	delete m_pCollision;
}

void TrigarCharging::Update()
{
	m_pCollisionManager->RegisterCollision(m_pCollision);
}

void TrigarCharging::Render()
{
	if (this->m_collides == true)
	{
		//アイコンを描画する
	}
}
