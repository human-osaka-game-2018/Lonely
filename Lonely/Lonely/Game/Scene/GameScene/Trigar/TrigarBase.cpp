/**
* @file TrigarBase.cpp
* @brief TrigarBaseクラスのソースファイル
* @author shion-sagawa
*/

#include <d3dx9math.h>

#include "TrigarBase.h"
#include "../../../../GameLib/GameLib.h"

TrigarBase::TrigarBase()
	:m_pCollisionManager(GameLib::Instance.GetCollisionManager())
	,m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
{
}

TrigarBase::~TrigarBase()
{
}

bool TrigarBase::Initialize()
{
	return true;
}

void TrigarBase::Finalize()
{
}

void TrigarBase::CollidesWithPlayer()
{
	m_collides = true;
}
