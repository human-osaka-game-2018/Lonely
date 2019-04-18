/**
* @file StageObject.cpp
* @brief StageObjectクラスのソースファイル
* @author shion-sagawa
*/

#include "StageObject.h"

#include "GameLib.h"
#include "../SharedInformation/SharedInformation.h"

StageObject::StageObject()
	:m_pCollisionManager(GameLib::Instance.GetCollisionManager())
	,m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
{
}

StageObject::~StageObject()
{
}

bool StageObject::Initialize()
{
	return true;
}

void StageObject::Finalize()
{
}