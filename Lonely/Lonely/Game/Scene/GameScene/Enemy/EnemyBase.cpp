/**
* @file EnemyBase.cpp
* @brief EnemyBaseクラスのソースファイル
* @author shion-sagawa
*/

#include "EnemyBase.h"

#include <d3dx9math.h>

#include "GameLib.h"

EnemyBase::EnemyBase()
	: m_pCollisionManager(GameLib::Instance.GetCollisionManager())
{
}

EnemyBase::~EnemyBase()
{
}

bool EnemyBase::Initialize()
{
	return true;
}

void EnemyBase::Finalize()
{
}
