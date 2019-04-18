/**
* @file PlayerBase.cpp
* @brief  PlayerBaseクラスのソースファイル
* @author shion-sagawa
*/

#include "PlayerBase.h"

#include <d3dx9math.h>

#include "GameLib.h"

PlayerBase::PlayerBase()
	: m_pCollisionManager(GameLib::Instance.GetCollisionManager())
{

}

PlayerBase::~PlayerBase()
{
}

bool PlayerBase::Initialize()
{
	return true;
}

void PlayerBase::Finalize()
{
}
