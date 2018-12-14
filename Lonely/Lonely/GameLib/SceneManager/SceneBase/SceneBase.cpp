/**
* @file SceneBase.cpp
* @brief SceneBase�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "SceneBase.h"
#include "../../GameLib.h"

SceneBase::SceneBase()
	: m_pObjectManager(GameLib::Instance.GetObjectManager())
	, m_pCameraManager(GameLib::Instance.GetCameraManager())
{
}

SceneBase::~SceneBase()
{
}
