/**
* @file EnemyBase.cpp
* @brief EnemyBaseクラスのソースファイル
* @author shion-sagawa
*/

#include <d3dx9math.h>

#include "../../../../GameLib/GameLib.h"
#include "EnemyBase.h"

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
