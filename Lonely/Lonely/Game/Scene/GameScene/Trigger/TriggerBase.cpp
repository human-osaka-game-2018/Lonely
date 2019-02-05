/**
* @file TriggerBase.cpp
* @brief TriggerBaseクラスのソースファイル
* @author shion-sagawa
*/

#include <d3dx9math.h>

#include "TriggerBase.h"
#include "../../../../GameLib/GameLib.h"

TriggerBase::TriggerBase()
	:m_pCollisionManager(GameLib::Instance.GetCollisionManager())
	,m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
{
}

TriggerBase::~TriggerBase()
{
}

bool TriggerBase::Initialize()
{
	return true;
}

void TriggerBase::Finalize()
{
}

void TriggerBase::CollidesWithPlayer()
{
	m_collides = true;
}
