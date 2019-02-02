/**
* @file PlayerBase.cpp
* @brief  PlayerBaseクラスのソースファイル
* @author shion-sagawa
*/

#include <d3dx9math.h>

#include "../../../../GameLib/GameLib.h"
#include "PlayerBase.h"

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
