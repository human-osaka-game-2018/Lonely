/**
* @file SceneBase.h
* @brief SceneBase�N���X�̃w�b�_�t�@�C��
* @author ���� �k��
*/

#include "SceneBase.h"
#include "../../GameLib.h"

SceneBase::SceneBase()
	: m_pObjectManager(GameLib::Instance.GetObjectManager())
{
}

SceneBase::~SceneBase()
{
}
